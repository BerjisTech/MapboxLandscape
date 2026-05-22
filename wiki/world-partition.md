# World Partition streaming

What the conversion step actually does, when to skip it, how to run it manually.

## What it does

After all chunks finish importing as standalone `ALandscape` actors, the conversion calls `FLandscapeConfigHelper::PartitionLandscape` on each. That's the same C++ entry point the editor's `Build > World Partition > Convert Landscape` menu item invokes. For each `ALandscape`, it:

1. Spawns one or more `ALandscapeStreamingProxy` actors organized by WP grid cells
2. Moves the landscape's components into those proxies (via `MoveComponentsToProxy` / `SplitHeightmap`)
3. Each proxy is **spatially loaded** — WP loads/unloads them based on camera distance
4. The original `ALandscape` stays as a lightweight parent (components moved out)

After conversion, the outliner shows:
- N `MapboxLandscape_C{x}_{y}` actors (parents, always loaded, ~5 MB each)
- N (or N×4 depending on grid size) `LandscapeStreamingProxy_*` actors (spatially loaded)

WP then decides which proxies are "in range" of the editor camera and unloads the rest from RAM. **This is the entire point** — it's why a 30 km region can sit on a 14 GB-RAM machine after fetch even though the imported data totals ~12 GB.

## Why it's not its own actor (no parent/child outliner hierarchy)

We tried. The engine forbids it three different ways:

1. `ALandscape::CanChangeIsSpatiallyLoadedFlag()` returns `false` — you can't mark a parent `ALandscape` itself as spatially loaded.
2. `ALandscapeStreamingProxy::Import` direct path hits an assertion in `FLandscapeGroup::RegisterComponent` when multiple components share a heightmap texture, which the engine's Import always produces (it packs up to 8 components per texture for storage efficiency).
3. The only engine-blessed path to actually move components into streaming proxies is `SplitHeightmap`, which gives every component its own dedicated heightmap texture. That's expensive but unavoidable.

So we run conversion after import as a post-processing step.

## When to skip it

Turn off `bConvertToWorldPartitionStreaming` in the importer panel when:

- **You're iterating** on classification, layer colors, satellite mode, etc. and re-fetching often. Convert at the end of your iteration cycle.
- **You don't need streaming** for the current radius. 5–10 km regions fit comfortably as standalone landscapes on a normal-sized machine.
- **You want to verify the import** before spending hours converting. Save the level, look around, then convert if everything's right.

Don't skip if:

- **You're past 15 km** on a non-WP-savvy machine. Without streaming, every chunk stays resident forever.
- **You're shipping** the level. Streaming is what makes the runtime memory footprint sane.

## Running conversion manually

In the importer panel, click `Convert Generated Landscapes To Streaming`. It:

1. Scans the world for actors whose label or name starts with `MapboxLandscape_` (so it works after editor restart, when the in-memory `GeneratedLandscapes` list is gone)
2. Partitions them in batches of `PartitionBatchSize` (default 8)
3. Between batches, drains the BC7 texture compile queue and runs garbage collection
4. Shows an `FScopedSlowTask` progress dialog while it runs

You can run this any time you have a `MapboxLandscape_*` actor in the level, even if you didn't fetch in this editor session. Useful workflow: fetch with conversion off, save, restart editor, click convert.

## What conversion *doesn't* do

- **It doesn't move HISMs.** PCG components and HISM scatter actors attached to the original `ALandscape` stay there. They render fine because the parent's transform doesn't change.
- **It doesn't migrate satellite material instances.** The per-chunk `M_MapboxLandscape_Inst` MICs get inherited by the streaming proxies (proxies' default material follows the parent's). If the satellite UVs look wrong after conversion, click `Fix Existing Landscape Materials`.
- **It doesn't change physical materials.** The `ULandscapeLayerInfoObject`s with their physical-material assignments carry through.

## Picking `WorldPartitionGridSizeInComponents`

This is "how many landscape components fit in one WP streaming cell". Smaller = finer streaming.

At our default `TilesPerLandscapeSide = 4`, each chunk has 16×16 = 256 components.

| Value | Cells per chunk | Total proxies (30 km) | Cell size | Use when |
|---|---|---|---|---|
| 8 | 4 (2×2) | 676 | ~2 km | Ground/walking gameplay |
| 16 | 1 (1×1) | 169 | ~4 km | **Flight, default** |
| 32 | 1 (still 1) | 169 | ~4 km (clamped) | Doesn't help vs 16 |

For Airmuseum's flight-sim context: **16** is correct. Aircraft cross 2 km cells in seconds, generating WP load/unload churn. 4 km cells are loaded long enough for the WP load to amortize.

## Common conversion problems

### "Conversion is slow"

It is. See [Why is fetching slow?](why-slow.md). Each chunk triggers ~256 `SplitHeightmap` calls × ~43k textures total × BC7 compilation. This is engine-level cost we can't reduce.

### "Memory pressure during conversion"

The BC7 compile queue piles up if `PartitionBatchSize` is too large. Drop it to 4 or 2.

### "I converted but the proxies aren't unloading"

Check that:
- The level is actually WP (`World->GetWorldPartition()` should be non-null — verifiable via `Build > World Partition > Editor > Disable Loading`)
- Editor loading range is reasonable (Project Settings → World Partition → defaults are usually fine)
- The proxies show `Spatially Loaded = true` in their details panel

If proxies show `Spatially Loaded = false`, conversion didn't actually run on them.

### "Conversion crashed mid-way"

The most likely cause is OOM during BC7 compilation. Restart the editor, lower `PartitionBatchSize` to 2, run the manual `Convert Generated Landscapes To Streaming` action again. It picks up any remaining unconverted `MapboxLandscape_*` actors.

## Saving after conversion

Always save the level after conversion completes. WP needs the proxy actors persisted to disk to do its load/unload dance properly. Without a save, the proxies exist only in memory and any editor restart loses them.

External actors (`*.uasset` files under `__ExternalActors__/`) are where WP stores spatially-loaded actors. A 30 km converted region produces hundreds to thousands of these.
