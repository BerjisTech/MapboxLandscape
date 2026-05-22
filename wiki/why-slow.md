# Why is fetching slow?

A fetch has four phases. The first two are linear and predictable. The last two get expensive at scale and are where you wait.

## Phase 1: HTTP downloads (~17 min for 30 km)

The plugin pulls 4 tile kinds per Mapbox tile (height, metadata, satellite, optionally vector). At 30 km radius / zoom 15 that's:
- 2,500 sat tiles × 4 kinds = ~10,000 HTTP requests

Mapbox rate-limits free-tier users to ~600 requests/min. So:
- 10,000 / 600 = **~17 minutes**, hard floor regardless of your machine

This is fine. You can't speed it up without paying for higher rate limits or fetching fewer tiles (smaller radius or higher `TilesPerLandscapeSide`).

## Phase 2: Per-chunk processing (~5–30 sec/chunk)

For each chunk the plugin:
- Decodes 16 height tiles → resamples (bicubic Catmull-Rom) → packed `uint16` heightmap
- Decodes 16 metadata tiles → classifies pixels → per-layer weight maps
- Decodes 16 satellite tiles → resamples to 512×512 BC7 texture asset
- Optionally rasterizes vector tiles into layer masks

This is bounded CPU work, scales linearly with chunk count, runs single-threaded today. **Not the bottleneck.**

## Phase 3: `ALandscape::Import` per chunk (~5–10 sec/chunk)

`Import` creates ~256 `ULandscapeComponent`s and ~32 heightmap textures + ~32 weightmap textures per chunk. The engine handles this synchronously; you'll see it as "Importing Landscape" slow tasks flashing through.

At 169 chunks: ~15–30 minutes total. This is what the early "30 mins, no streaming" fetch was measuring.

## Phase 4: World Partition conversion (the long one — **hours**)

This is where overnight runs come from. Converting one `ALandscape` into streaming proxies calls `ALandscape::SplitHeightmap` once **per component** (so 256 times per chunk).

Each `SplitHeightmap` call:
1. Reads the old packed heightmap texture (`LockMip`)
2. Creates a **new** `UTexture2D` for this single component
3. Initializes its mip pyramid
4. Triggers async BC7 compilation (`PostEditChange`)

For 169 chunks: **~43,000 new heightmap textures, ~43,000 BC7 compilations queued**.

Even at 16-thread parallel compilation and ~5 sec/texture average, the math is:
- 43,000 × 5 / 16 ≈ **~3.7 hours of pure texture-compile work**, plus all the per-component splitting overhead

Add the engine's render-state recreation passes, weightmap reshuffling, and per-proxy actor spawn, and you're at the overnight runtime you saw.

## Why we can't make Phase 4 faster

This isn't plugin code — it's engine code, and the texture creation is unavoidable in the WP-streaming model. Each streaming proxy must own dedicated heightmap textures so it can stream independently of its neighbors. The engine's *only* path to that ownership is `SplitHeightmap`.

What we *can* do:
- **Skip Phase 4** if you don't actually need streaming yet — turn off `bConvertToWorldPartitionStreaming`. The fetch ends after Phase 3.
- **Drain the compile queue periodically** to avoid the queue exploding at the end (memory pressure). This is what `PartitionBatchSize` does.
- **Use a larger `WorldPartitionGridSizeInComponents`** — doesn't reduce the per-component SplitHeightmap count, but reduces proxy actor-spawn cost.

See [Speed knobs & tradeoffs](speed-knobs.md) for how to apply these.

## Sanity check: total time at 30 km on a 7800X3D / 32 GB / RTX 3060

| Phase | Time |
|---|---|
| Download | ~17 min |
| Chunk processing | ~10 min |
| Import | ~20 min |
| WP conversion | ~4 hours |
| **Total with WP convert** | **~5 hours** |
| **Total without WP convert** | **~50 min** |

If you saw "all night", that's roughly consistent with the WP-convert path running uncontended. The new batched conversion (drain compile queue every 8 landscapes) doesn't reduce total time — it bounds memory so it actually finishes instead of OOMing near the end.
