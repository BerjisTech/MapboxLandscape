# Architecture & internals

High-level layout for anyone who wants to read the code or extend the plugin.

## Module layout

```
MapboxLandscape/
  Source/MapboxLandscape/
    Public/
      MapboxImporterConfig.h        ← UObject that owns all importer state + actions
      MapboxLandscapeSettings.h     ← UDeveloperSettings (Project Settings)
      MapboxLayerDef.h              ← FMapboxLayerDef struct (one per classification layer)
      MapboxAssetGenerator.h        ← Static helpers for creating M_MapboxLandscape, PCG graph, decal material
    Private/
      MapboxImporterConfig.cpp      ← The actual pipeline (this is where ~90% of the code lives)
      MapboxImporterEditorSubsystem.cpp  ← Wraps Config in an editor subsystem so it persists per session
      MapboxImporterPanel.cpp       ← The Slate panel under Tools > Mapbox Landscape Importer
      MapboxLandscape.cpp           ← Module init / menu registration
      MapboxLandscapeSettings.cpp   ← Default layer set definition
      MapboxMvtReader.cpp           ← Mapbox Vector Tile (protobuf) decoder
      MapboxAssetGenerator.cpp      ← Master material + PCG graph generation
  wiki/                             ← You are here
  MapboxLandscape.uplugin
```

## The fetch pipeline

All in `MapboxImporterConfig.cpp`. Top-down call order:

1. **`FetchLandscape`** (CallInEditor action button)
   - Validates: API key, bounding box, world exists, WP-status notice
   - Pre-flight memory budget check
   - `EnumerateTiles` → builds `PendingDownloadQueue` and `Chunks` arrays
   - `StartNextDownloads` → fires HTTP requests up to `MaxConcurrentRequests`

2. **`OnTileResponse`** (HTTP callback, one per tile)
   - Stores the blob in `CompletedBlobs`
   - Updates progress counters, emits toast every ~5%
   - When all done: `OnAllTilesDownloaded`
   - Otherwise: `StartNextDownloads` to issue the next batch

3. **`OnAllTilesDownloaded`** (~1000 lines of the heavy lifting)
   - **Pass A (min/max scan):** decode each height tile, accumulate global min/max, drop the blob
   - **Pass B (chunk loop), per chunk:**
     - Decode this chunk's tiles directly into scratch buffers, drop blobs as consumed
     - Resample heights to landscape resolution (bicubic Catmull-Rom)
     - Classify metadata + vector pixels into `WinnerLayer` array
     - Build per-layer weight maps (skip empty layers)
     - Apply Clear-layer carve to baseline
     - Resample satellite to 512×512, save as BC7 asset
     - `SpawnLandscapeForChunk` → `ALandscape::Import`
     - `SpawnPCGForLandscape` → HISM scatter using heightmap (no line traces)
     - `SpawnSatelliteDecal` (optional, only if `SatelliteMode = OverlayDecal`)
     - `Heightmap.Empty()`, `LayerWeights.Empty()`, etc.
     - `CollectGarbage` every 4 chunks
   - After chunk loop:
     - If WP and `bConvertToWorldPartitionStreaming`: `ConvertGeneratedLandscapesToStreaming`
   - `FinishFetch` (resets transient state)

4. **`ConvertGeneratedLandscapesToStreaming`** (CallInEditor action button, also called from #3)
   - Collects target landscapes (in-memory or world scan)
   - For each batch of `PartitionBatchSize` landscapes:
     - `PartitionSingleLandscape` per landscape → calls `FLandscapeConfigHelper::PartitionLandscape` (engine)
   - Between batches: `FAssetCompilingManager::Get().FinishAllCompilation()` + `CollectGarbage`

## Why this shape

The original `ALandscape::Import` flow had an obvious-but-wrong structure: spawn all landscapes, then convert all to WP. That blew out RAM at 15 km because every chunk's working buffers stayed alive simultaneously. The current shape (per-chunk processing + chunk-by-chunk GC + batched WP conversion at end) was driven by hitting that memory cliff.

Key design decisions:

- **Per-chunk processing** instead of monolithic decode+spawn. Buffers freed between chunks; only one chunk's working memory live at a time.
- **Drop tile blobs as consumed.** Pass A scans heights then `CompletedBlobs.Remove(key)`. By the time Pass B is on chunk N, chunks 0..N-1's blobs are gone.
- **Skip empty layers.** `ActiveLayerIndices` built from `WinnerLayer`. Layers with zero winning pixels don't get a `ULandscapeLayerInfoObject` or a weightmap allocation.
- **Defer WP partition.** Conversion happens after all chunks. Lets compile queue drain between batches instead of growing unbounded.
- **Per-chunk standalone `ALandscape`** instead of shared-`LandscapeGuid` parent/proxy. The engine forbids the latter (see [World Partition](world-partition.md) for the engine-constraint detail).

## File breakdown

### `MapboxImporterConfig.cpp` (the big one)

By line count, roughly:
- 0–500: includes, types, helpers, ResetLayersToDefaults, ClearGeneratedLandscapes, RegenerateDefaultAssets, FixExistingLandscapeMaterials
- 500–700: `FetchLandscape`, `CancelFetch`, pre-flight memory budget
- 700–900: HTTP request management — `StartNextDownloads`, `StartRequest`, `OnTileResponse`
- 900–1100: tile decode helpers, `ResampleHeights` (bicubic), `ResampleColors`, `ResampleMask`
- 1100–1850: `OnAllTilesDownloaded` (the main chunk loop)
- 1850–2050: `SpawnLandscapeForChunk`, `SpawnPCGForLandscape`, `SpawnSatelliteDecal`
- 2050–2200: WP conversion — `PartitionSingleLandscape`, `ConvertGeneratedLandscapesToStreaming`
- 2200–end: `FinishFetch`

### `MapboxMvtReader.cpp`

Parses Mapbox Vector Tile protobufs into 2D polylines for vector-mode layer classification. Roughly:
- Protobuf varint/zigzag decoding
- MVT command parsing (MoveTo, LineTo, ClosePath)
- Output: `TArray<TArray<FVector2D>>` polygons + classification metadata

Don't touch this unless Mapbox changes their MVT format.

### `MapboxAssetGenerator.cpp`

Builds:
- `M_MapboxLandscape` master material — per-layer color blending + satellite texture sampling + Clear opacity routing
- `PCG_MapboxScatter` graph — empty default
- `M_MapboxSatDecal` decal material

Each helper bumps a `*Version` counter when its output should be regenerated (e.g., adding the Clear layer bumped `MasterMaterialVersion` from 2 → 3). On fetch, version mismatch triggers regeneration.

## Extension points

### Adding a new tile kind

E.g., adding `building-height` raster data:

1. Add to `ETileKind` enum in `MapboxImporterConfig.h`
2. Handle in `StartRequest` (URL construction)
3. Decode in `OnAllTilesDownloaded` Pass B
4. Use the decoded data wherever it's needed (probably classification or material)

### Adding a new height source (e.g., SRTM)

Currently the plugin assumes Mapbox terrain-RGB v4 (capped at z15). To support SRTM:

1. Add `HeightSource` enum to `MapboxImporterConfig` (TerrainRGB | SRTM)
2. Branch in `StartRequest` for height tiles
3. Update `DecodeHeight` to handle SRTM's `int16` raw encoding instead of RGB packing
4. Update pre-flight estimator and zoom clamping (SRTM has its own resolution constraints)

### Adding a new classification mode

Currently `Color` and `Vector`. To add e.g. `Heightmap` (classify by elevation):

1. Add to `EMapboxMatchMode` enum
2. Add the match parameters to `FMapboxLayerDef`
3. Handle in `ClassifyPixel` — note this runs per-pixel so it must be fast

## Performance hotspots (where to look if profiling)

In rough cost order, top first:

1. **`FLandscapeConfigHelper::PartitionLandscape`** (engine code, but called by us) — texture compilation
2. **`ALandscape::Import`** (engine) — heightmap/weightmap texture creation
3. **`ResampleHeights` bicubic** — ~10ms per chunk at default resolution
4. **`ClassifyPixel`** — 1M+ calls per chunk, runs the layer match loop each time
5. **MVT polygon-in-pixel rasterization** — `RasterLine` in tight loops

If you need to make decoding faster, parallelize the chunk loop with `Async(EAsyncExecution::TaskGraph, ...)`. We're single-threaded today because correctness mattered more than speed; on 7800X3D's 16 threads there's ~16× headroom.

## Engine version targeting

Plugin targets **UE5.7**. Module dependencies that may not exist on older versions:

- `WorldPartitionEditor` (renamed/refactored between 5.4 and 5.5)
- `FLandscapeConfigHelper::PartitionLandscape` (signature stable from 5.3 onward)
- `FAssetCompilingManager` (since 5.0)
- `LandscapeStreamingProxy::SetLandscapeActor` (rename in 5.7 — was assigned directly via `LandscapeActor` field in earlier versions)

If you port to 5.5 or 5.6, mostly works; the `SetLandscapeActor` call may need to revert to direct field assignment.

## Testing

There's no automated test harness yet. Manual test plan:
1. Open the included demo level (none ships — set up your own)
2. Fetch a small area (5 km radius)
3. Verify the chunks land in the right world position (drop a marker at the center lat/lng, fly there)
4. Test layer painting (Paint mode in Landscape editor)
5. Test scatter (assign a `ScatterMeshes` mesh to Grass, refetch with `bSpawnPCGComponents = true`)
6. Test WP conversion (verify proxies appear; fly camera away and watch them unload via the Outliner's "show only loaded" filter)
