# Troubleshooting

Common failure modes and the actual fix. Errors are listed by what you see, not by what's "wrong" internally.

## Pre-flight aborts

### "Mapbox API key is empty"

Open `Project Settings > Plugins > Mapbox Landscape` and paste your token into `Api Key`. Free token from mapbox.com/account.

### "Mapbox: this level is not World Partition"

This is **Info** severity — fetch still works, just no streaming. To enable streaming:
- New level: `File > New Level > Empty Open World`
- Existing level: `Build > World Partition > Convert Level`

### "Mapbox: estimated ~N MB needed; only ~M MB free"

Hard pre-flight abort. See [Memory sizing](memory-sizing.md). Fixes in order:
1. Switch to a WP level
2. Close Chrome/Discord/etc.
3. Raise `Tiles Per Landscape Side` (4 → 8 cuts chunks 4×)
4. Lower `Radius Km`

### "Mapbox: aborting — would create N landscape tiles (limit M)"

Safety cap. The math wants more `ALandscape` actors than `MaxLandscapesTotal` allows. Either:
- Lower `Radius Km`
- Turn off `Auto Zoom` and pick a lower `Zoom Level` (smaller tile count, lower detail)
- Raise `Tiles Per Landscape Side`
- Raise `Max Landscapes Total` past the current count

## Fetch starts but…

### "I clicked Fetch and nothing happens"

Check the editor's output log for `LogMapbox` lines. If you see "fetching N tiles" but no progress toasts, the HTTP requests are queued — the first toast appears at ~5% complete (one per ~200 tiles).

If you see no LogMapbox output at all, the fetch never started. Likely cause: a pre-flight modal popped up behind the editor window. Alt-tab around.

### "X height tile(s) failed to download" warning

Some height tiles returned HTTP errors (most often 404 — Mapbox doesn't serve every tile, or you're at a clamped zoom edge). Affected areas will appear flat at sea level. Usually safe to ignore; if substantial, lower `Zoom Level` to land in a denser tile coverage area.

### Fetch crashes the editor mid-way

Save the crash log. Common patterns:

- **Assertion in `MapboxMvtReader.cpp`**: outdated build, the bug was fixed in May 2026
- **`check(ComponentLayerData != nullptr)` in `LandscapeEdit.cpp:3917`**: outdated build, pre-Import registration order bug (fixed)
- **`check(CanChangeIsSpatiallyLoadedFlag())`**: outdated build, this codepath was removed (engine forbids it)
- **`check(ComponentWorld != ActiveComponentWorld)` in `LandscapeGroup.cpp`**: outdated build, we no longer try to share `LandscapeGuid` across chunks

If you see any of these on a current build, file an issue with the full stack.

## Fetch finished, but…

### "Landscape is completely flat"

The most common cause is **`Zoom Level > 15`** (manual override) or auto-zoom picked above 15. Mapbox terrain-RGB v4 stops serving at z=15; higher zooms 404 every height tile → `SrcHeightsMeters` stays zero-initialized → flat landscape.

Both `ZoomLevel` and `HeightZoomBonus` are clamped so `ResolvedZoom + HZB ≤ 15`. If you're on an older build that didn't have this clamp, update.

Other causes:
- All height tiles failed for some other reason (check output log for HTTP 4xx/5xx)
- The Clear layer is matching everywhere (older bug — fixed by skipping Clear in `ClassifyPixel`)

### "Landscape looks edgy / triangulated on cliffs"

Heightmap resample is bicubic Catmull-Rom now. If cliffs still look facetted, increase `HeightZoomBonus` to 1 (fetches 4× more height samples). Don't go above 1 unless your region is small (<5 km radius).

### "Satellite texture is repeating / tiling wrong"

The per-chunk material instance has the wrong `LandscapeOrigin` or `LandscapeWorldSize` params. Click **`Fix Existing Landscape Materials`** in the importer panel. It re-derives both from the landscape's actor transform.

### "Texture not found at /Game/MapboxLandscape/Textures/..."

The per-level texture folder doesn't match. The plugin saves satellite textures to `/Game/MapboxLandscape/Textures/{level_name}/T_MapboxSat_*`. If you renamed the level after fetching, the old textures still work but `Fix Existing Landscape Materials` won't find them. Either:
- Move the textures into the new level's folder
- Re-run fetch (uses the current level name)

### "PCG scatter is missing / nothing scattered"

Check `Mapbox > PCG > Spawn PCG Components`. Default is OFF. If you want scatter, turn on and refetch — or attach a `UPCGComponent` to existing landscapes manually.

The plugin's built-in HISM scatter (independent of PCG) only runs on layers with `bScatterEnabled = true` and `ScatterMeshes` populated. None of the default 20 layers ship with meshes — you have to assign them yourself.

## World Partition conversion problems

### "Conversion runs forever"

It can. At 30 km / TPLS=4 / 169 chunks, expect ~4 hours. See [Why slow](why-slow.md) for the math.

Speed it up by:
- Raising `Tiles Per Landscape Side` to 8 (4× fewer chunks → ~1 hour conversion)
- Skipping conversion (`bConvertToWorldPartitionStreaming = false`) and doing it manually later

### "Memory pressure warning twice during conversion"

The BC7 texture compile queue grew past what RAM can buffer. Drop `PartitionBatchSize` from 8 to 4 or 2. The plugin drains the compile queue between batches; smaller batches drain more often.

### "Proxies aren't unloading after conversion"

Check:
1. The level is actually WP — `Build > World Partition > Editor > Disable Loading` should be available in the menu
2. The proxies show `Spatially Loaded = true` in their details panel
3. WP loading range (Project Settings → World Partition) isn't set to "Infinite"

If proxies show `Spatially Loaded = false`, the conversion ran but didn't produce streaming proxies — usually because `WorldPartitionGridSizeInComponents` was misconfigured. Re-run conversion with the default value (16).

### "Outliner is full of `LandscapeStreamingProxy_X` actors and it's slow"

That's expected at 30+ km. UE5's outliner doesn't love thousands of actors. Use the search bar (`MapboxLandscape_*` to find parents, `LandscapeStreamingProxy_*` for children). Or enable `Filter > By Type > Custom > Hide Spatially Loaded` to hide unloaded proxies.

## Editor / IDE problems

### "Build failed: cannot open UnrealEditor-MapboxLandscape.dll"

The editor (or its crash reporter) is holding the DLL. Quit the editor and any open `CrashReportClient*` processes, then retry build.

### "Unable to build while Live Coding is active"

Either close the editor entirely, or press **Ctrl+Alt+F11** in the editor to trigger Live Coding compile (picks up changes without an editor restart, but only for source-level changes — header changes need a full rebuild).

### "Plugin module fails to load"

Check `MapboxLandscape.Build.cs` against the engine version. The current build targets UE5.7 and depends on:
- `WorldPartitionEditor` (for the WP partition call)
- `LandscapeEditor` (for `FLandscapeConfigHelper`)
- `Landscape` (for `ALandscape`, `ULandscapeInfo`, etc.)

If you're on UE5.5 or earlier, some of those module names changed. File an issue if you need older-engine support.

## "It looks worse than the paid plugin"

The paid plugin (Mapbox Landscape, Ludic Drive) has been worked on for years; we're still catching up. Specific deltas to look at:

- **Smoother heights at zoom 15:** they may be using higher-res DEM sources (SRTM/AW3D) instead of terrain-RGB. We can add that as an alternate height source.
- **Better road masks:** they have more granular vector parsing for road classes. The 20-layer default in this plugin is a good start but doesn't cover everything.
- **Faster fetch:** they may use threaded chunk processing. We're single-threaded for chunk decode/raster; could go async with `Async(EAsyncExecution::TaskGraph, ...)`. Not done yet because it'd add complexity without changing the dominant cost (WP conversion, which is engine code).

If a specific quality gap is blocking you, file an issue with screenshots side-by-side.
