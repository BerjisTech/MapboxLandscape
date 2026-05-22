# Memory sizing & radius limits

Hard numbers for "what radius fits on what machine." Calibrated against a Ryzen 7 7800X3D / 32 GB / RTX 3060 12 GB (~14 GB free at editor startup with browser closed).

## The pre-flight estimator

Every fetch runs a pre-flight budget check that aborts modally if the projected peak exceeds **70% of available physical RAM**, and warns at 50%. The numbers below are what the estimator computes.

### Memory model

Three pools:

1. **Transient downloads:** HTTP tile blobs in memory + one chunk's scratch buffers + saved satellite texture assets. Bounded per-chunk (~80 MB scratch) plus all queued tile blobs (~60 KB × `TotalRequests`).

2. **Landscape resident (WP):**
   - Each chunk's lightweight parent `ALandscape` (~5 MB, components moved out post-conversion)
   - A "loading set" ceiling of ~25 streaming proxies × ~70 MB = 1,750 MB (this is what WP keeps near the camera; everything else is unloaded)

3. **Landscape resident (non-WP):**
   - Every chunk stays as a heavyweight `ALandscape` (~70 MB) forever, sum scales linearly

## Radius limits at default settings (TPLS=4, z=15)

### WP level (`Empty Open World` template)

| Radius | Chunks | Peak during fetch | Resident after fetch + camera moves | OK? |
|---|---|---|---|---|
| 5 km | 9 | ~600 MB | ~250 MB | ✅ anywhere |
| 15 km | 49 | ~2.2 GB | ~700 MB | ✅ comfortable |
| 30 km | 169 | ~3.7 GB | ~2.5 GB | ✅ on 16+ GB free |
| 50 km | 441 | ~5.5 GB | ~3.7 GB | ⚠️ tight on 14 GB free |
| 70 km | 841 | ~8.2 GB | ~6 GB | ⚠️ need 24+ GB free |
| 100 km | 1,681 (auto-zoom drops to z=14) | ~6 GB | ~4 GB | ✅ at z=14 |
| 150 km | 2,500+ | varies | varies | check pre-flight |

**Key insight:** beyond ~50 km, auto-zoom drops you from z=15 to z=14 to keep `MaxLandscapesTotal` under control. That cuts per-km tile count by 4 and resident-set requirements by the same. You lose visible mesh density per km, but the math works out.

### Non-WP level (any other template)

| Radius | Chunks | Resident (forever) | Fits in 14 GB free? |
|---|---|---|---|
| 5 km | 9 | ~630 MB | ✅ |
| 10 km | 25 | ~1.75 GB | ✅ |
| 15 km | 49 | ~3.5 GB | ✅ tight |
| 20 km | 81 | ~5.7 GB | ⚠️ |
| 30 km | 169 | **~12 GB** | ❌ aborts at pre-flight |
| 50 km+ | — | — | ❌ go WP |

On non-WP, your hard ceiling is roughly **(available RAM in MB × 0.7) / 70 = max chunks**. Multiply by chunk km² to get area.

## Why WP turns this around

On WP, the conversion phase converts each chunk to streaming proxies. After the conversion completes **and the editor camera moves**, WP unloads streaming proxies that are out of range. Resident memory drops to roughly:

- Per-chunk parents (always loaded, ~5 MB each)
- + the ~25 nearest proxies (each holds the chunk's actual terrain data, ~70 MB)
- + editor overhead

For 30 km at WP that's `169 × 5 + 25 × 70 ≈ 2.6 GB` — comfortably fits where the non-WP equivalent would need 12 GB.

## When the pre-flight aborts you

If you see the modal `Mapbox: estimated ~N MB needed; only ~M MB free`:

1. **Are you on a WP level?** If not, that's the first move. Either use the `Empty Open World` template for new levels, or `Build > World Partition > Convert Level` on the current one. Re-run.

2. **Close other apps.** Chrome, Discord, Slack, Spotify all bite ~500 MB each. Doubling your free RAM doubles your max radius.

3. **Raise `Tiles Per Landscape Side`.** Going from 4 → 8 cuts chunk count by 4. Same total terrain data, fewer landscape actors, less resident overhead.

4. **Lower `Radius Km`.** Each km² costs roughly proportional memory. Halve it and you halve the resident set.

5. **Lower `Max Landscapes Total`.** Combined with auto-zoom this forces the plugin to pick a lower zoom level (smaller tile count) for the same radius. Resolution drops; coverage stays.

## Memory during the WP conversion phase

This is where the original "all night → memory pressure twice" failure came from. Each chunk's `PartitionLandscape` triggers ~256 `SplitHeightmap` calls, each creating a new `UTexture2D` and queuing a BC7 compile. Without throttling, the compile queue grows unbounded across all 169 chunks → tens of thousands of textures in flight at the end → OOM.

The plugin now drains the compile queue every `PartitionBatchSize` landscapes (default 8). Peak texture-compile memory during conversion: roughly:

```
8 chunks × 256 textures × ~5 MB per BC7 compile working set ≈ 10 GB peak
```

So **conversion itself needs roughly 8–12 GB transient headroom** beyond what the resident set takes. On a 14 GB-free machine, a 30 km WP convert sits right at the edge. If you OOM during conversion:

- Reduce `PartitionBatchSize` to 4 (or even 2) — bounds the queue tighter
- Close other apps before clicking convert
- Save the level frequently during conversion (you can't actually save mid-batch, but between batches GC has a chance to release)

## What about disk?

- Each satellite texture: ~256 KB on disk (BC7 512×512, mips)
- 30 km = 169 satellite textures = ~43 MB
- Plus level data: maybe 200 MB for 30 km area
- Plus WP cell data after conversion: ~1.5 GB for 30 km

Disk is not the bottleneck. RAM is.

## Quick rule of thumb

> **Free RAM ÷ 100 ≈ max radius in km on WP level** (with conversion).
> **Free RAM ÷ 800 ≈ max radius in km on non-WP level.**

14 GB free → ~140 km radius on WP (theoretical, hits auto-zoom drop and Mapbox HTTP limits first), or ~17 km radius non-WP.
