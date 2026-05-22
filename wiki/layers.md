# Layer system

The plugin's classification maps Mapbox tile pixels to landscape layers. Each layer ends up as a weightmap painted onto the landscape, sampled by the master material.

## The default 20-layer set

| Layer | Priority | Source | Notes |
|---|---|---|---|
| **Clear** | 100 | hand-paint only | Special — see below |
| Water | 90 | water polygons (vector) | |
| Buildings | 80 | building polygons (vector) | |
| Runway | 75 | aeroway=runway (vector) | |
| Taxiway | 72 | aeroway=taxiway (vector) | |
| Rock | 70 | landuse=bare_rock + grey color match | |
| Highway | 60 | road class=highway | |
| PrimaryRoad | 55 | road class=primary | |
| Railway | 50 | road class=rail | |
| TertiaryRoad | 45 | road class=tertiary | |
| ResidentialRoad | 42 | road class=residential | |
| Path | 40 | road class=path/footway | |
| Forest | 35 | landuse=wood/forest + green color | |
| Farmland | 32 | landuse=farmland + brownish color | |
| Park | 28 | landuse=park/garden/pitch | |
| Industrial | 25 | landuse=industrial/commercial | |
| Mud | 22 | landuse=wetland | |
| Sand | 20 | natural=sand + landuse=beach | |
| DrySoil | 18 | tan/brown color fallback | |
| Grass | 10 | green color fallback | Default layer for un-classified pixels |

Priorities determine which layer wins when multiple match a pixel. Highest priority wins.

## The Clear layer (the special one)

`Clear` is hand-paint only. Its `Priority = 100` is high so it dominates any auto-classification, but **`ClassifyPixel` explicitly skips it** — it never auto-matches. You paint it in the landscape editor's Paint mode where you want terrain to disappear.

Two effects when Clear has weight ≥ 50%:

1. **Heightmap carved to baseline.** During `OnAllTilesDownloaded`, any pixel whose winning layer is Clear gets its height forced to the baseline encoding (32768 = sea level after rebase). Cliffs and hills flatten in carved areas.

2. **Material opacity zeroed.** The auto-generated `M_MapboxLandscape` master material has `BlendMode = Masked` and routes a `Clear` layer-weight sample to `OpacityMask`. Pixels with Clear weight > 0.5 render fully transparent.

Use it to:
- Cut runways into hills (the paid plugin has a similar feature)
- Erase the terrain over a hand-built area you want to replace with custom geometry
- Make holes for tunnels, basements, etc.

If your Clear-painted area renders as plain green or black, the master material wasn't regenerated. Click `Regenerate Default Assets` in the importer panel, then `Fix Existing Landscape Materials`.

## How classification picks a winner per pixel

For each pixel in metadata/satellite/vector data, the plugin runs `ClassifyPixel`:

1. **Vector layers (highest priority first):** if the pixel falls inside a vector polygon for this layer, it wins immediately.
2. **Color layers:** if the pixel color (in HSV-tolerance space) matches the layer's `MatchColor`, it wins.
3. **Grass fallback:** if nothing matched, the lowest-priority Grass layer wins.

Vector layers always beat color layers at the same priority because the loop processes vector matches before color matches.

## Customizing layers

In the importer panel, scroll to `Mapbox > Layers`. Each entry has:

- `Layer Name` (`FName`) — must be unique; used as the landscape layer name
- `Match Mode`: `Color` or `Vector`
- `Match Color` / `Color Tolerance` (HSV) — for color mode
- `Vector Source Class` (e.g. `road`, `landuse`) and `Vector Subclass Filter` — for vector mode
- `Priority` (int) — higher wins
- `Physical Material` (soft ptr) — assigned to the layer's `ULandscapeLayerInfoObject`
- `Scatter Meshes` + density / spacing / scale — HISM scatter targets
- `Scatter Min Spacing Meters` (default 3) — minimum sample stride for HISM scatter
- `Scatter Max Instances Per Landscape` (default 50,000) — cap to prevent runaway scatter

Click `Reset Layers To Defaults` to restore the 20-layer set (wipes your customizations).

## What layers look like in the output

After fetch, each chunk's `ALandscape` has one `ULandscapeLayerInfoObject` per active layer (layers with zero weighted pixels in a chunk get skipped to save memory). Open the landscape's Paint mode in the editor and you'll see the layer list match your `MapboxLayers` config.

The auto-generated `M_MapboxLandscape` master material samples each layer's weight through a `UMaterialExpressionLandscapeLayerWeight` node and blends per-layer base colors. It also exposes:
- `SatelliteTexture` (per-chunk MIC override) — the satellite imagery as base color, blended in
- `LandscapeWorldSize` (cm) and `LandscapeOrigin` (cm) — used for UV math so the satellite tiles correctly across a chunk

If you want a custom material, expose a parameter named `SatelliteTexture` and the plugin will inject the per-chunk texture automatically.

## Adding a new layer

1. Add an entry to `Mapbox > Layers`.
2. For vector: set `Match Mode = Vector`, `Vector Source Class = landuse` (or similar), `Vector Subclass Filter` to a comma-separated list of values.
3. For color: set `Match Mode = Color`, `Match Color` to the metadata-style pixel color you want to catch, tweak `Color Tolerance`.
4. Re-fetch (the master material gets regenerated to include the new layer's weight node).

The plugin auto-creates a base color for new layers (deterministic from layer name hash) so the rendered result has at least some visual differentiation. Override `OverrideBaseColor` in the layer def to set a specific color.

## Common layer issues

- **"My new layer never wins":** check its priority vs. neighbors. Vector layers at priority X beat color layers at priority X+1 sometimes because of match-order. Easy fix: bump the priority higher.
- **"Everything turned to one color after fetch":** master material is stale. Click `Regenerate Default Assets` then `Fix Existing Landscape Materials`. The plugin tracks a `MasterMaterialVersion` int and bumps it when the auto-generated material needs to change — version mismatch triggers regeneration on next fetch.
- **"Layer weights look noisy":** Mapbox metadata tiles don't have anti-aliasing, so per-pixel classification produces speckled boundaries. Increase your `Color Tolerance` to smooth, or switch to vector mode where possible.
