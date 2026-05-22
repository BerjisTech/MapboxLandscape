# Speed knobs & tradeoffs

Settings that materially affect fetch time, listed by impact. All live in the Mapbox Landscape Importer panel unless noted.

## The single biggest win: `Convert To World Partition Streaming`

**Default: ON.** Turn it **OFF** when you want a fast fetch and will convert later (or never).

- **OFF:** Fetch ends after `Import`. 30 km Kisumu finishes in ~50 minutes instead of overnight. Landscapes are normal `ALandscape` actors, no streaming.
- **ON:** Phase 4 runs at end of fetch and bumps total time by **~4×** for a 30 km region. WP unloads distant proxies after fetch, so resident memory drops dramatically.

### Recommended workflow if streaming matters but you want speed

1. Fetch with `bConvertToWorldPartitionStreaming = false`. Confirm the terrain looks right.
2. **Save the level.** This commits the imported landscapes to disk so the conversion can pick up where you left off even after editor restart.
3. Click the `Convert Generated Landscapes To Streaming` action button in the panel.
4. Walk away. Conversion runs as a single slow-task with a progress dialog.

This separates "did the fetch work?" (quick to answer) from "did the conversion work?" (slow to answer), so you can iterate on layer settings, satellite mode, etc. without paying conversion cost every time.

## `Partition Batch Size`

**Default: 8.** Only matters when WP conversion runs.

How many landscapes the plugin partitions before pausing to drain the BC7 texture compile queue (`FAssetCompilingManager::Get().FinishAllCompilation()`) and run a GC pass.

- **Smaller (e.g. 4):** Lower peak memory during conversion. Recommended on 16–32 GB machines. Slightly slower total runtime (more compile-flush sync points).
- **Larger (e.g. 16):** Higher peak memory during conversion. The texture compile queue grows further before draining. Risks the same memory-pressure crash that motivated this whole batching system.
- **Don't go above 16** unless you have 64+ GB RAM and want to gamble.

## `World Partition Grid Size In Components`

**Default: 16.** Only matters when WP conversion runs.

How many landscape components fit in one WP streaming cell. Smaller = finer streaming granularity.

| Value | Cells per chunk (default 16×16 chunk) | Proxy actors at 30 km | WP cell size (default 1 km/tile, z=15) |
|---|---|---|---|
| 8 | 4 (2×2) | 676 | ~2 km |
| 16 | 1 (1×1) | 169 | ~4 km |
| 32 | 1 (1×1, but cell sized larger) | 169 | ~4 km (clamped by chunk) |

For **flight sim** content (this project): **16** is right. Aircraft cover 4 km in seconds; loading proxies at 2 km granularity just thrashes WP without visible benefit.

For **first-person/ground** content: **8** is better. Cells stay loaded for longer because you traverse them slower.

Reducing grid size doesn't speed up conversion (SplitHeightmap still runs once per component); it makes the conversion *spawn more proxy actors*, which is moderately expensive. So `16` is also faster than `8` if you don't need the granularity.

## `Tiles Per Landscape Side`

**Default: 4.** Sets chunk size. One chunk = `TilesPerLandscapeSide × TilesPerLandscapeSide` Mapbox tiles → one `ALandscape`.

- **Larger (8 or 16):** Fewer, larger landscapes. Each landscape has more components (e.g. 64×64 = 4,096 components at TPLS=16). Way fewer SplitHeightmap calls *total* because the per-chunk count is the same but you have fewer chunks. Trade-off: each chunk's `Import` is heavier and harder to garbage-collect between chunks.
- **Smaller (1 or 2):** More, smaller landscapes. Finer streaming if you skip WP convert (each ALandscape can unload independently — but on WP that's already what conversion does). Mostly harmful.

For 30 km at TPLS=8 vs default 4: chunk count drops from 169 to ~50. WP conversion total time drops from ~4 hours to ~1 hour (very roughly), at the cost of slightly heavier per-chunk processing.

**Try TPLS=8** if you're doing 30+ km regions regularly.

## `Height Zoom Bonus`

**Default: 0.** Controls cliff smoothness, not partition speed.

`HeightZoomBonus = N` fetches height tiles at zoom+N. Each step quadruples height tile count:
- `0`: baseline
- `1`: 4× height tiles (sharper cliffs, ~2× total HTTP requests for small fetches)
- `2`: 16× height tiles (don't use above ~5 km radius)

The engine clamps `ResolvedZoom + HeightZoomBonus ≤ 15` because Mapbox terrain-RGB v4 stops serving above z15.

Helps quality at small radii where the per-pixel height resolution looks coarse. At 30+ km you won't see the difference because the landscape's own vertex spacing is coarser than the height samples already.

## `Max Concurrent Requests`

**Default: 16.** How many HTTP requests run in parallel.

Higher gets you to the 600/min rate-limit ceiling faster, but Mapbox returns HTTP 429 if you exceed it. 16 is safe; 32 risks 429s on slower connections.

## `Auto Generate Default Assets`

**Default: ON.** If off, the plugin won't auto-create `M_MapboxLandscape`, the PCG graph, or the decal material on first fetch.

Turn off if you've authored your own assets and want the plugin to use only those. No performance impact.

## `Spawn PCG Components`

**Default: OFF (per project settings).** Adds a `UPCGComponent` to each spawned landscape running the scatter graph.

PCG scattering is expensive. Leave off until you specifically need it. The plugin's built-in HISM scatter (heightmap-sampled, no line traces) still runs per layer's `ScatterMeshes`.

## Don't bother tuning these

- `Z Exaggeration`: visual only, no perf impact
- `Rebase To Sea Level`: visual only
- `Metadata Style Id`: same total bytes downloaded regardless of style
- `Satellite Mode`: `BlendIntoMaterial` and `OverlayDecal` cost essentially the same; `None` saves the satellite-texture asset save (small win)

## Concrete recipes

### "30 km, fast iteration"
```
bConvertToWorldPartitionStreaming = false
TilesPerLandscapeSide = 4
HeightZoomBonus = 0
```
Result: ~50 min total. Manually convert later via the action button.

### "70 km, willing to wait, want streaming"
```
bConvertToWorldPartitionStreaming = true
TilesPerLandscapeSide = 8
WorldPartitionGridSizeInComponents = 16
PartitionBatchSize = 4
```
Result: many hours but should finish without memory pressure.

### "5 km hero region, max quality"
```
HeightZoomBonus = 1
TilesPerLandscapeSide = 2
bSpawnPCGComponents = true
```
Result: fast fetch, sharpest possible terrain, scatter populated.
