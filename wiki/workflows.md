# Workflow recipes

"I want to do X" → concrete settings and steps. Copy these. Adjust the lat/lng.

## Recipe 1: Quick hero region for screenshots / demo

Goal: 5 km area, max visual quality, fast iteration.

1. Create level: `File > New Level > Empty Open World`
2. Save it (CTRL-S)
3. `Tools > Mapbox Landscape Importer`
4. Settings:
   - `Center Latitude / Longitude`: your spot
   - `Radius Km`: `5`
   - `Tiles Per Landscape Side`: `2` (smaller landscapes for finer streaming)
   - `Height Zoom Bonus`: `1` (sharper terrain — only OK at small radii)
   - `Convert To World Partition Streaming`: leave ON
5. Click `Fetch Landscape`
6. ~5 minutes later: ~16 chunks land, 16 streaming proxies created
7. Fly the camera around. WP auto-loads what's near.

## Recipe 2: Big region, willing to wait

Goal: 30 km of real terrain you'll actually use in-game.

1. Create / open an Empty Open World level
2. Settings:
   - `Radius Km`: `30`
   - `Tiles Per Landscape Side`: `4` (default) or `8` (4× faster conversion, larger landscapes)
   - `Height Zoom Bonus`: `0` (don't add 4× height tile cost at this size)
   - `Convert To World Partition Streaming`: ON
   - `Partition Batch Size`: `4` (gentler memory profile)
3. Fetch and walk away — expect:
   - Downloads: ~17 min
   - Import: ~20 min
   - Conversion: ~3–4 hours at TPLS=4, ~1 hour at TPLS=8
4. **Save the level immediately after fetch completes.**

## Recipe 3: Big region, fast fetch, convert later

Goal: validate the import quickly, convert overnight.

1. Empty Open World level
2. Settings:
   - `Radius Km`: `30`
   - `Convert To World Partition Streaming`: **OFF**
3. Fetch. Done in ~50 minutes.
4. Look around — check that terrain, satellite, layers look right.
5. **Save the level.**
6. When you're satisfied, in the importer panel click `Convert Generated Landscapes To Streaming`
7. Walk away. Conversion runs as a single slow-task.
8. Save again when done.

This is the recommended workflow if you're not 100% sure your settings are right. Re-fetching is fast; re-converting is not.

## Recipe 4: Iterating on layer / classification settings

Goal: dial in colors and priorities without paying conversion cost every cycle.

1. Empty Open World level, pick a small area (5–10 km)
2. `Convert To World Partition Streaming`: OFF
3. Fetch, inspect, adjust `Mapbox Layers` settings
4. Click `Clear Generated Landscapes` (destroys the actors so re-fetch isn't additive)
5. Re-fetch with new settings
6. Repeat until happy
7. Final fetch with your real radius and conversion ON

## Recipe 5: Recover from a crash mid-conversion

The editor died during WP conversion. You have a partly-converted level.

1. Reopen the level. Unconverted chunks appear as `MapboxLandscape_*` `ALandscape` actors; converted ones appear as parents + `LandscapeStreamingProxy_*` children.
2. Click `Convert Generated Landscapes To Streaming`. The action scans for `MapboxLandscape_*` named actors regardless of memory state, so already-converted ones get skipped (their components are already moved).
3. Lower `Partition Batch Size` to `2` to be safer about memory.
4. Walk away again.

## Recipe 6: Add to an existing level

Goal: add a Mapbox region to a level that already has hand-built content.

1. Open the existing level. **Make sure it's WP** (`Build > World Partition` menu should be available).
2. Set `Import Origin` (in the importer panel) to wherever you want the imported area to land in world space. Default is `(0,0,0)`.
3. Set `Radius Km` to cover the area you need.
4. Fetch.
5. Move / rotate the imported `ALandscape` actors to fit your existing geometry. Then click `Fix Existing Landscape Materials` to re-derive the per-chunk UV params from the new transforms.

## Recipe 7: Carve out areas you don't want terrain in

Goal: erase the terrain under a hand-built airfield/town.

1. Fetch as normal, conversion either ON or OFF.
2. Open Landscape Paint mode (`Modes > Landscape > Paint`).
3. Select the `Clear` layer.
4. Paint where you want the terrain to disappear. Weight ≥ 50%:
   - Carves the heightmap to baseline (sea level / rebase point)
   - Renders the material fully transparent (because `M_MapboxLandscape` is `BLEND_Masked` with Clear weight routed to `OpacityMask`)
5. Place your hand-built geometry into the carved area.

## Recipe 8: I want streaming proxies but my level was made before this feature

You have `MapboxLandscape_*` actors from an older fetch, all as standalone `ALandscape`. You want them converted now.

1. Open the level on a current build. Confirm it's WP.
2. In the importer panel:
   - `World Partition Grid Size In Components`: 16 (or 8 for ground gameplay)
   - `Partition Batch Size`: 4
3. Click `Convert Generated Landscapes To Streaming`
4. The action scans the world for `MapboxLandscape_*` actors and converts them all. No need to re-fetch.
5. Save.

## Recipe 9: Maximum coverage, smallest detail

Goal: 100+ km radius, willing to accept coarser per-km mesh density.

1. Empty Open World, WP level
2. Settings:
   - `Radius Km`: `100`
   - `Auto Zoom`: ON — will pick z=14 (auto-clamps based on `Max Landscapes Total`)
   - `Tiles Per Landscape Side`: `8`
   - `Convert To World Partition Streaming`: ON
3. Fetch. Expect many hours. Final result: ~120 chunks × 8×8 tile area each, ~10 m/quad mesh density.

This is the "match the paid plugin's 70 km Luo Nyanza demo" path. The paid plugin uses similar tradeoffs internally.

## Recipe 10: Use a custom master material

Goal: replace `M_MapboxLandscape` with your own shader.

1. Author your master material. Expose these parameters for full plugin integration:
   - `SatelliteTexture` (Texture2D) — per-chunk satellite override
   - `LandscapeOrigin` (Vector) — chunk origin in world cm, for satellite UV math
   - `LandscapeWorldSize` (Vector or Scalar) — chunk size in cm
   - For each `MapboxLayers` entry, a `UMaterialExpressionLandscapeLayerWeight` with the layer's `LayerName` as parameter name
2. In the importer panel, set `Landscape Master Material` to your material.
3. Set `Auto Generate Default Assets` = OFF (otherwise the plugin tries to recreate `M_MapboxLandscape`)
4. Fetch normally. Per-chunk `M_MapboxLandscape_Inst` MICs derive from your material instead.

If your material doesn't expose `SatelliteTexture`, no error — the plugin just won't inject the satellite texture. The chunk still gets a MIC with whatever defaults your material has.
