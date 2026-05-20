# Mapbox Landscape

Real-world Unreal Engine 5 landscapes built from Mapbox terrain, satellite, vector, and style tiles. Pick a center point and radius (or a bounding box), click Fetch, get a grid of `ALandscape` actors with correct heights, satellite imagery, and per-pixel land-use classification ready for PCG scatter.

Tested on UE 5.7.

## Install

1. Drop the `MapboxLandscape` folder into your project's `Plugins/` directory.
2. Launch the editor — it will offer to compile the module on first run.
3. **Edit → Project Settings → Plugins → Mapbox Landscape**, paste your Mapbox access token into `API Key`. (Get one free at https://account.mapbox.com)

## Use it

**Tools → Mapbox Landscape → Open Landscape Importer**

The Importer is a dockable panel — drag it anywhere. There's no actor to place in the level.

1. Pick a `Coordinate Mode`:
   - **Center Point & Radius** (recommended) — enter `Center Latitude`, `Center Longitude`, `Radius Km`.
   - **Bounding Box** — explicit N/S/E/W.
   - **Tool String** — paste comma-separated lat/lng pairs from any GIS tool.
2. (Optional) Adjust:
   - `Z Exaggeration` — 1.0 = real-world heights, 2.0 = dramatized mountains.
   - `Tiles Per Landscape Side` — 4 (default) puts 16 Mapbox tiles into each `ALandscape`. 8 = fewer, larger actors.
   - `Auto Zoom` — leave on for sensible defaults, turn off to force a specific Mapbox zoom.
3. Click **Fetch Landscape**.

Every field has a tooltip. Hover for details and units.

## Layers — what the plugin classifies and how

Each `FMapboxLayerDef` defines one landscape weight-map channel. Each one has a `MatchMode`:

- **Color** — matches pixel color in the Mapbox style tile (raster). Tolerant to brightness variation in HSV space.
- **Vector** — matches semantic features in Mapbox Streets v8 vector tiles (`class=motorway`, `class=major_rail`, `class=runway`, etc.). Much more precise.
- **Both** — pixel matches if either rule does.

Defaults (priority-ordered, highest wins per pixel):

| Layer | Source | Priority | Notes |
|---|---|---|---|
| Water | water polygons | 90 | |
| Buildings | building polygons | 80 | |
| Runway | aeroway/runway, 45m | 75 | |
| Taxiway | aeroway/taxiway, 18m | 72 | |
| Highway | road/motorway+trunk, 15m | 60 | |
| PrimaryRoad | road/primary+secondary, 10m | 55 | |
| Railway | road/*_rail, 4m | 52 | |
| TertiaryRoad | road/tertiary+street, 7m | 50 | |
| ResidentialRoad | road/street_limited+service, 5m | 45 | |
| Path | road/path+footway, 2m | 40 | |
| Forest | landuse/wood+forest polygons | 30 | scatters trees |
| Park | landuse/park polygons | 28 | scatters grass |
| Industrial | landuse/industrial polygons | 25 | |
| Grass | color fallback (greens) | 10 | scatters grass |

Each layer also holds:
- `ScatterMeshes` — static meshes the HISM/PCG scatter picks from.
- `ScatterDensity` — meshes per 100 m².
- `MaterialTint` — color passed as `<LayerName>_Tint` parameter (for custom master materials).
- `PhysicalMaterial` — applied where this layer's weight is dominant (footstep sounds, friction).

Click **Reset Layers To Defaults** to restore the table.

## Heights and altitude

Mapbox Terrain-RGB delivers sub-decimeter elevation precision. The plugin:

1. Decodes every height tile to meters.
2. Computes the global min/max across the dataset.
3. Picks a landscape Z scale so the elevation range fits in the 16-bit heightmap without clipping.
4. Encodes `(meters − baseline) × ZExaggeration × scale + 32768`.
5. Sets the spawned landscape's actor `Z` scale to match.

Toggle `Rebase To Sea Level` to flatten the lowest sample to world Z=0 (good for areas at high altitude like Nairobi or Denver — keeps the map sitting on the world grid).

## Satellite and materials

`Satellite Mode` controls how the imagery is applied:

- **None** — no satellite; you pick your own master material.
- **Blend Into Material** (default) — per-chunk `UMaterialInstanceConstant` is created with the satellite texture and proper UV mapping. The auto-generated `M_MapboxLandscape` maps the texture once across each chunk's world footprint (no tiling).
- **Overlay Decal** — spawns an `ADecalActor` per landscape projecting the satellite imagery from above. Lets you keep a separate base material.

If you delete the auto-generated `M_MapboxLandscape` or the per-chunk MICs end up misconfigured, click **Fix Existing Landscape Materials** — it rebuilds the master, regenerates each MIC with the correct origin/size parameters, and reassigns it. Works even after editor restart (scans the level for `MapboxLandscape_C*` actors).

## Generated assets — where they live

```
F:\YourProject\Content\MapboxLandscape\
├── Textures\
│   └── T_MapboxSat_C{X}_{Y}_Z{Z}.uasset      ← satellite imagery per chunk
├── MaterialInstances\
│   └── MI_MapboxLandscape_C{X}_{Y}.uasset    ← per-chunk MIC
├── Materials\
│   ├── M_MapboxLandscape.uasset              ← shared master (auto-generated)
│   └── M_MapboxSatelliteDecal.uasset         ← decal master
└── PCG\
    └── PCG_MapboxScatter.uasset              ← scatter graph (placeholder)
```

Delete the whole `MapboxLandscape` folder + re-fetch for a clean nuke.

## Common issues

| Symptom | Cause / fix |
|---|---|
| Toast: "API key is empty" | Project Settings → Plugins → Mapbox Landscape → API Key |
| Toast: "would create N landscapes (limit M)" | Reduce radius, raise `Tiles Per Landscape Side`, or bump `Max Landscapes Total` |
| Editor freezes at 92% on level open | Your map has too many streamed landscape tiles. Either reduce the area for that map, or open a fresh empty Open World level and re-fetch smaller |
| Satellite texture repeats across a tile | Click **Fix Existing Landscape Materials**. Future fetches use the corrected master automatically |
| Landscape stays grey/black | Either the auto-generated material got into a bad state (Fix Existing) or no satellite texture was saved (check `SatelliteMode` wasn't `None` at fetch time) |
| HTTP 401 in Output Log | Token is invalid or missing the `styles:tiles` / `tiles:read` scopes |
| HTTP 429 | Mapbox rate limit. Reduce `Max Concurrent Requests` to 8 |

## Project Settings

**Edit → Project Settings → Plugins → Mapbox Landscape**

| Field | Purpose |
|---|---|
| API Key | Mapbox access token (stored in `DefaultMapboxLandscape.ini`) |
| Default* (all the per-importer fields) | Seeds new importer sessions with your preferred values |
| Default Layers | The layer set the importer's `Reset Layers To Defaults` button installs |

## Plugin architecture (for contributors)

- `UMapboxImporterConfig` — UObject (NOT an actor) holding all import state. Lives in `UMapboxImporterEditorSubsystem`.
- `SMapboxImporterPanel` — Slate panel with an `IDetailsView` bound to the config.
- `UMapboxLandscapeSettings` — `UDeveloperSettings` for project-level defaults and the API key.
- `MapboxAssetGenerator` — namespace creating the master material, decal material, and PCG graph.
- `MapboxMvtReader` — minimal Mapbox Vector Tile protobuf parser (LineString + Polygon).
- Auto-spawned `ALandscape` actors are real game content. The importer config itself is editor-only and is stripped from packaged builds.

## License

Same as your project. Mapbox API usage is governed by Mapbox's terms.
