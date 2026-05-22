# World features (roads, paths, railways)

Procedural worldbuilding from OSM data, generated alongside the landscape fetch. Like Blosm's "Import roads and paths" + "Import railways" checkboxes but using Epic's built-in landscape spline system as the output.

## What gets generated

For each road/path/railway in the fetched area, the plugin creates:

- One `ULandscapeSplineControlPoint` per ~20 m along the polyline (configurable)
- `ULandscapeSplineSegment`s connecting them, with a user-assigned static mesh swept along
- Optional landscape paint deformation (e.g. paint a Sand layer along the road for Brushify-style dust shoulders)

These live on each spawned `ALandscape`'s `ULandscapeSplinesComponent` — the same system Epic's built-in landscape spline tools use. So everything that works for hand-authored splines (terrain deformation, mesh tiling, painting) works here too. You can also edit, extend, or delete them after the fact in the standard Landscape Spline Mode.

## Enable it

In the importer panel:

1. Tick `Mapbox > World Features > Roads > Generate Road Splines`
2. Click `Reset Road Classes To Defaults` to populate the default set (motorway, primary, secondary, tertiary, residential, path, rail)
3. For each road class you actually want, assign a `Spline Mesh` (asset reference). Without a mesh, the class still creates spline control points + paint deformation but no visible mesh.
4. Fetch as normal — roads get generated chunk-by-chunk during the fetch.

## Per-class settings

Each `FMapboxRoadClassSettings` entry has:

| Field | What it controls |
|---|---|
| `Class Name` | Display label, doesn't affect generation |
| `Enabled` | Per-class on/off without deleting the entry |
| `Mvt Layer` | Which Mapbox vector layer to read from. Almost always `road` (handles roads, paths, AND rails) |
| `Mvt Class Matches` | OSM `class` property values this entry matches. e.g. `['motorway']`, `['major_rail', 'minor_rail']`, `['path', 'pedestrian', 'track']` |
| `Spline Mesh` | Mesh swept along the spline. Local +X should be the forward direction. Compatible with Brushify, Epic spline meshes, or any axis-aligned road mesh |
| `Spline Width (Meters)` | Mesh footprint width — should match what your road mesh expects |
| `Paint Layer` | Landscape weight layer to paint along the road. e.g. `Sand` for Brushify-style dust. `NAME_None` = no paint |
| `Paint Width (Meters)` | Width of paint deformation. Usually wider than `SplineWidthMeters` so the paint overlaps the road shoulder |
| `Raise Above Terrain (Cm)` | Lifts the spline above the heightmap to prevent z-fighting (default 5 cm) |
| `Control Point Spacing (Meters)` | How dense the control points are. 20 m is fine for most roads; 5 m for tight switchbacks |

## The "Brushify road dust" recipe

Brushify road kits look great when there's a sandy shoulder transitioning into the surrounding terrain. To replicate:

1. Make sure your `MapboxLayers` config includes a `Sand` layer with a Sand-colored material/texture.
2. Set the road class's `Paint Layer = "Sand"` and `Paint Width Meters` ≈ 1.5× the road width.
3. Assign your Brushify road mesh to `Spline Mesh`.
4. Fetch.

Result: every road sits on a sand-painted strip wider than the road itself, blending into surrounding grass/dirt/etc. via the landscape material's layer blending.

You can do the same with any layer you have — `DrySoil` for dirt-road shoulders, `Mud` for swampy environments, `Rock` for mountain switchbacks, etc.

## Common config: typical Brushify-style assignments

| Class | Match | Width m | Paint Width m | Paint Layer |
|---|---|---|---|---|
| Motorway | `motorway` | 18 | 24 | Sand |
| Primary | `primary, trunk` | 12 | 16 | Sand |
| Secondary | `secondary` | 9 | 12 | Sand |
| Tertiary | `tertiary` | 7 | 10 | DrySoil |
| Residential | `residential, service` | 6 | 8 | DrySoil |
| Path | `path, pedestrian, track, footway` | 2 | 3 | DrySoil |
| Railway | `major_rail, minor_rail` | 4 | 6 | *(none — sleepers handle it)* |

(`Reset Road Classes To Defaults` populates exactly this — only the `Spline Mesh` references are left empty for you to assign.)

## Caveats

### Chunk boundaries

Each chunk's roads live on its own landscape's spline component. A road that crosses two chunks is generated as two separate spline runs (one per chunk), each ending at the chunk boundary. Visually they should butt up cleanly because both runs are sourced from the same OSM polyline and use the same mesh. If you see a visible seam, check that your road mesh tiles seamlessly along its forward axis.

### Cross-class roads

OSM tags can disagree with our defaults (e.g. an OSM "primary" that locals would call residential, or vice versa). If you want finer control, edit `Mvt Class Matches` per class. The match is on the `class` property of each OSM feature in the `road` vector layer.

### "Roads are floating above the ground" or "in the ground"

Tune `Raise Above Terrain Cm` (default 5). Negative isn't supported; if you need to sink roads, edit their `Z` after generation in Landscape Spline Mode.

### "Mesh stretches/squashes wrong"

Spline mesh tiling along the spline depends on the mesh's local +X length. Set `Center Adjust` in the `FLandscapeSplineMeshEntry` (the plugin sets `bCenterH = true` by default) if it's off-center. If the mesh is tiled too tightly, increase `Control Point Spacing Meters` — fewer control points = longer segments = the mesh stretches over a longer span.

### "I want to edit the generated roads"

Select the landscape, switch to `Landscape Mode > Manage > Spline`. All the generated control points and segments appear in the standard spline editor and behave like hand-authored ones.

### "Performance impact"

Spline mesh components are real instanced static meshes. Each segment becomes one `USplineMeshComponent`. For dense urban areas with many short roads, this can add up — expect 100s to 1000s of spline-mesh components per chunk. World Partition still streams them with their parent landscape, so distant chunks unload normally.

### "Roads aren't getting WP-streamed"

`USplineMeshComponent`s attached to a streaming proxy via the `bPlaceSplineMeshesInStreamingLevels` flag (default true on segments) will stream with their proxy. If you're seeing roads stay loaded when distant, check that flag is true on a sample segment.

## What's NOT in this feature yet

This is the roads/paths/railways implementation. Coming separately:

- **Buildings** — extruded polygon footprints with Blosm-style storey-distribution heights
- **Water objects** — flat plane meshes for water polygons
- **Forests + vegetation** — polygon-bounded HISM scatter (current scatter is per-landscape-layer)

See the README for the full plan.
