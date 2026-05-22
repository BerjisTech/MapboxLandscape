# World features (roads, paths, railways)

Procedural worldbuilding from OSM data, **run as a separate step after the landscape fetch**. Same idea as Blosm's "Import roads and paths" + "Import railways" checkboxes, but UE-native: output goes into Epic's built-in landscape spline system.

> **Important:** World features used to auto-run during fetch. They don't anymore — fetches are heavy enough without piling more work on top, and you usually want to verify the terrain looks right before spending more time. Now there's a dedicated `Populate World Features` action button.

## Workflow

1. Fetch the landscape normally (`Fetch Landscape` button). World features are skipped.
2. After fetch completes, the landscape actors exist in the level. Save the level.
3. In the importer panel, scroll to `Mapbox > World Features`:
   - Tick `Populate Roads`
   - Assign meshes to the `Road Classes` you care about
4. Click the `Populate World Features` action button.
5. The plugin re-fetches just the Mapbox vector tiles (~half the HTTP requests of the original fetch — no height/metadata/satellite) and drops landscape splines onto each existing `MapboxLandscape_*` actor.

The populate is much faster than the original fetch because:
- Only vector tiles get re-downloaded (~1 KB/tile each)
- No landscape components, no heightmap textures, no BC7 compilation
- No World Partition conversion

Typical timing: ~5 minutes total for a 30 km region's road populate vs. 8+ hours for the original landscape fetch.

## Why the split?

Original design had world features inline with fetch. Two problems:

1. **Fetch is already overnight territory at large radii.** Adding splines made an already-heavy step heavier.
2. **You can't tell if the road settings are right until you see them.** With inline generation, you commit hours of fetch before knowing whether your road mesh + paint layer choices produce the look you want. Decoupled populate lets you iterate in minutes.

The populate can also be re-run any time. Want to try different road meshes? Clear the splines via Landscape Mode → Spline → Select All → Delete, change the settings, click `Populate World Features` again.

## Per-class settings

Each `FMapboxRoadClassSettings` entry has:

| Field | What it controls |
|---|---|
| `Class` | **Dropdown.** Pick one of the standard OSM road classes (Motorway, Trunk, Primary, Secondary, Tertiary, Residential, Service, Pedestrian, Path, Footway, Track, Cycleway, Steps, Major Rail, Minor Rail). The plugin handles the `_link` variants automatically. Pick `Custom` if you want to match an unusual combination via `MvtClassMatches` |
| `Enabled` | Per-class on/off without deleting the entry |
| `Spline Mesh` | Mesh swept along the spline. Local +X should be the forward direction. Compatible with Brushify, Epic spline meshes, or any axis-aligned road mesh |
| `Spline Width (Meters)` | Mesh footprint width — should match what your road mesh expects |
| `Paint Layer` | Landscape weight layer to paint along the road. e.g. `Sand` for Brushify-style dust. `NAME_None` = no paint |
| `Paint Width (Meters)` | Width of paint deformation. Usually wider than `SplineWidthMeters` so the paint overlaps the road shoulder |
| `Raise Above Terrain (Cm)` | Lifts the spline above the heightmap to prevent z-fighting (default 5 cm) |
| `Max Segment Length (Meters)` | If a source MVT polyline segment exceeds this, it gets subdivided. Default 100 m. Raise to 200+ if editor performance is bad |
| **Advanced:** `Mvt Layer` | Which Mapbox Streets v8 layer to read from. Default `road`; you rarely change this |
| **Advanced:** `Mvt Class Matches` | Override the OSM class strings the `Class` dropdown would match. Leave empty unless you set `Class = Custom` or you specifically want different matching |

## The "Brushify road dust" recipe

Brushify road kits look great when there's a sandy shoulder transitioning into the surrounding terrain. To replicate:

1. Make sure your `MapboxLayers` config includes a `Sand` layer with a Sand-colored material/texture.
2. Set the road class's `Paint Layer = "Sand"` and `Paint Width Meters` ≈ 1.5× the road width.
3. Assign your Brushify road mesh to `Spline Mesh`.
4. Click `Populate World Features`.

Result: every road sits on a sand-painted strip wider than the road itself, blending into surrounding grass/dirt/etc. via the landscape material's layer blending.

You can do the same with any layer you have — `DrySoil` for dirt-road shoulders, `Mud` for swampy environments, `Rock` for mountain switchbacks, etc.

## Editor sprite icons (the "mountain icons everywhere" problem)

The first version of this feature produced ~50 control points per km of road, each with a small mountain-shaped editor sprite icon. At city density that filled the viewport with sprite icons and made the editor unusable.

Two fixes:

1. **Source-vertex spacing instead of fixed resampling.** Mapbox already simplifies polylines for the target zoom (typically a vertex every 50–300 m). We now use those source vertices directly, only subdividing if a segment exceeds `Max Segment Length Meters` (default 100 m). For typical OSM data this produces 5-10× fewer control points than the old algorithm.

2. **Sprite icons hidden by default.** A new `Hide Spline Editor Sprites` checkbox (default ON) sets the spline component's `ControlPointSprite` to nullptr after population. The splines still work — you can still select and edit control points via Landscape Mode → Spline → wireframe + box-select — but the viewport stops drowning in icons.

If you want the icons back for editing:
- Untick `Hide Spline Editor Sprites` before populating, or
- Re-set `ControlPointSprite` on the spline component manually in details

## Default-table cheat sheet

| Class | OSM `class` matched | Width m | Paint Width m | Paint Layer |
|---|---|---|---|---|
| Motorway | `motorway`, `motorway_link` | 18 | 24 | Sand |
| Trunk | `trunk`, `trunk_link` | 14 | 18 | Sand |
| Primary | `primary`, `primary_link` | 12 | 16 | Sand |
| Secondary | `secondary`, `secondary_link` | 9 | 12 | Sand |
| Tertiary | `tertiary`, `tertiary_link` | 7 | 10 | DrySoil |
| Residential | `residential` | 6 | 8 | DrySoil |
| Service | `service` | 4 | 6 | DrySoil |
| Path | `path` | 2 | 3 | DrySoil |
| Footway | `footway` | 1.5 | 2.5 | DrySoil |
| Track | `track` | 3 | 5 | DrySoil |
| Major Rail | `major_rail` | 4 | 6 | *(none)* |
| Minor Rail | `minor_rail` | 3 | 5 | *(none)* |

(`Reset Road Classes To Defaults` populates exactly this — only the `Spline Mesh` references are left empty for you to assign.)

## Caveats

### Chunk boundaries

Each chunk's roads live on its own landscape's spline component. A road that crosses two chunks is generated as two separate spline runs (one per chunk), each ending at the chunk boundary. Visually they should butt up cleanly because both runs come from the same OSM polyline and use the same mesh. If you see a visible seam, check that your road mesh tiles seamlessly along its forward axis.

### Heights come from line traces

Populate doesn't have the heightmap in memory anymore. Each control point's Z is sampled via a world-space line trace down against the landscape collision. This means:

- Landscape collision must be loaded. For most populate runs this Just Works because either the landscape is freshly fetched (collision loads on Import) or you're populating after editor restart (collision loads with the level).
- For World-Partition-converted regions, **proxies near the populate area need to be loaded**. WP usually loads them within the editor's loading range, but if you've moved the camera far away you might need to fly back into the area before populating.
- If the line trace misses (no collision at that XY), the control point falls back to the landscape actor's Z. Result: a flat patch of road at the wrong height. Fix by reloading the missing proxy and re-populating.

### "Settings must match the original fetch"

The populate uses your current `Center Lat/Lng/Radius/Zoom` to know which Mapbox tiles to fetch. **Those must match the fetch that produced the landscapes you're decorating.** If you changed the lat/lng after fetching, the populate fetches the wrong tiles, no landscapes match, and nothing happens.

A future version will save fetch metadata into a per-level data asset so this can't desync.

### Cross-class roads

OSM tags can disagree with our defaults (e.g. an OSM "primary" that locals would call residential). If you want finer control, edit `Mvt Class Matches` per class. The match is on the `class` property of each OSM feature in the `road` vector layer.

### "I want to edit the generated roads"

Select the landscape, switch to `Landscape Mode > Manage > Spline`. All the generated control points and segments appear in the standard spline editor. You can drag, delete, add segments, change widths, etc.

### Performance impact at runtime

Spline mesh components are real instanced static meshes. Each segment becomes one `USplineMeshComponent`. Roads in a dense urban area can produce hundreds per chunk, but WP streams them with their parent landscape so distant chunks unload.

## What's NOT in this feature yet

This is the roads/paths/railways implementation. Coming separately:

- **Buildings** — extruded polygon footprints with Blosm-style storey-distribution heights
- **Water objects** — flat plane meshes for water polygons
- **Forests + vegetation** — polygon-bounded HISM scatter (current scatter is per-landscape-layer)

Each will get its own checkbox in `Mapbox > World Features` and slot into the same `Populate World Features` button.
