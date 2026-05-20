# Mapbox Landscape Plugin (v2)

Generates real-world UE5 landscapes from Mapbox terrain, satellite, and style tiles. Supports large
areas by splitting them into a grid of `ALandscape` actors and exposes a user-configurable layer
classification system that drives both the landscape material and per-layer mesh scatter.

## What's new in v2

- **Heights actually apply** — fixed the GUID/encoding bug that produced flat landscapes.
- **Auto Z scale + baseline** — the plugin scans the elevation range and picks a landscape Z scale
  so altitude is preserved without clipping. Add `Z Exaggeration` to emphasize relief.
- **Large areas** — instead of one giant landscape, the area is split into a grid of `ALandscape`
  actors (`Tiles Per Landscape Side` controls the chunk size). Set `Max Landscapes Total` to cap
  pathological requests.
- **Auto zoom** — leave `Auto Zoom` on and the plugin picks a Mapbox zoom that fits inside your
  landscape budget. Turn it off to force a specific zoom.
- **User-defined layers** — drop in a `Layers` array (default Forest / Grass / Urban / Road / Water)
  and tune each layer's color match, tint, scatter meshes, and density.
- **Real satellite textures** — satellite tiles are saved as proper `UTexture2D` assets under
  `/Game/MapboxLandscape/Textures/` so they survive editor restarts.
- **Generated assets** — `M_MapboxLandscape` (layer blend + satellite tint) and `PCG_MapboxScatter`
  (placeholder graph) are auto-generated under the plugin's content folder on the first fetch.
- **Scatter fallback** — if no PCG graph is assigned, the plugin spawns `HISM` components per layer
  using the configured mesh array so you get visible scatter immediately.

## Quick start

1. Drop a `MapboxLandscapeActor` into the level.
2. Paste your Mapbox token into `Api Key`.
3. Pick a `Coordinate Mode`:
   - **Center Point & Radius** (default) — enter `Center Latitude`, `Center Longitude`, `Radius Km`.
   - **Bounding Box** — enter N/S/E/W.
   - **Tool String** — paste any comma-separated list of lat/lng pairs.
4. (Optional) Tune `Tiles Per Landscape Side` (4 = ~1km landscapes at zoom 14) and the layer rules.
5. Click **Fetch Landscape**.

## How layers work

Each `FMapboxLayerDef` describes one classification bucket:

| Field             | Purpose                                                                 |
|-------------------|-------------------------------------------------------------------------|
| `LayerName`       | Landscape layer name (also the material parameter prefix)               |
| `TargetColor`     | Color in the metadata style tile that this layer matches                |
| `ColorSpace`      | HSV (hue-aware, default) or RGB linear distance                         |
| `Hue/Sat/Val Tolerance` | Per-channel tolerance in HSV mode                                |
| `Priority`        | Higher priority wins when multiple layers match a pixel                 |
| `MaterialTint`    | Tint passed to the `M_MapboxLandscape` material (`<LayerName>_Tint`)    |
| `ScatterMeshes`   | Static mesh array; randomly picked per instance                         |
| `ScatterDensity`  | Higher = more instances per area                                        |
| `ScatterMin/MaxScale` | Random scale range per instance                                     |
| `bAlignToLandscapeNormal` | Orient instances to terrain normal                              |

Leave `ScatterMeshes` empty (or untick `bScatterEnabled`) to use the layer purely for material
blending without spawning anything.

## Material

The default `M_MapboxLandscape` exposes:
- `SatelliteTexture` (Texture2D) — per-chunk satellite imagery
- `SatelliteStrength` (Scalar) — 0 to fully use layer tints, 1 to use satellite only
- `<LayerName>_Tint` (Vector) — one per defined layer

The plugin sets these per landscape via a `UMaterialInstanceDynamic`. To customise, point
`LandscapeMasterMaterial` at your own master material — keep the parameter names the same and
everything still wires up.

## PCG vs HISM fallback

If `ScatterPCGGraph` is set (or auto-generated), the plugin spawns a `UPCGComponent` on each
landscape and triggers generation. Author the graph to read the landscape's layer weights and
spawn from the per-layer mesh arrays.

If no PCG graph is available, the plugin falls back to deterministic `HISM` scatter using the first
mesh in each enabled layer's array, distributed across the landscape extents with line-traces to
the surface. This is sufficient for previewing the area; switch to PCG for proper per-layer
filtering.

## Tiling math reference

- Mapbox tile = 256x256 px, world width ≈ `40075016.686 * cos(lat) / 2^zoom` meters.
- `Tiles Per Landscape Side = 4` at zoom 14 → ~5 km per landscape side.
- `Verts per landscape = round((tiles * 256 - 1) / 63) * 63 + 1` (snapped to valid UE landscape size).

## Heights and altitude

Mapbox Terrain-RGB encodes meters with sub-decimeter precision. The plugin:

1. Decodes all tiles to floats.
2. Computes global `min`/`max` across the dataset.
3. Picks a landscape Z scale such that `(max - baseline) * ZExaggeration` covers the
   ±256m * (ZScale/100) range of a 16-bit heightmap.
4. Encodes each sample as `(meters - baseline) * 128 * 100 / ZScale + 32768`.
5. Sets the spawned landscape's actor `Z` scale to the chosen value.

Toggle `Rebase To Sea Level` to keep absolute altitude (baseline=0) vs. flattening the lowest
sample to world Z=0 (baseline=min).

## Troubleshooting

- **All landscapes still flat** — check the log for `chosen landscape Z scale = X` and the
  detected `min/max`. If max ≈ min the source area really is flat or tiles failed to download.
- **HTTP 401** — Mapbox token doesn't have access to the requested style or sources.
- **Too many landscapes** — increase `Tiles Per Landscape Side`, lower the radius, or raise
  `Max Landscapes Total`.
- **Material doesn't blend properly** — `M_MapboxLandscape` is auto-generated; once created you
  may want to edit it manually to add normals, roughness, world position offset, etc.

## Build dependencies

`Landscape`, `LandscapeEditor`, `HTTP`, `ImageWrapper`, `PCG`, `Foliage`, `UnrealEd`,
`AssetTools`, `AssetRegistry`, `Projects`, `RenderCore`, `RHI`.
