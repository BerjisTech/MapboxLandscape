# Building the sample level

Fab buyers expect a *click-and-it-runs* example map shipped inside the
plugin's `Content/` folder. The reviewers also use it to validate the
plugin without spending 20 minutes configuring a Mapbox key. This guide
takes ~30 minutes from open editor to committed `.umap`.

## What we're building

A small (5–10 km radius) demo level that demonstrates:

- A fetched landscape with satellite imagery
- At least one PCG/HISM scatter layer (grass or trees) populated
- Layer painting visible — water, roads, vegetation — proving the
  classification works
- A camera spawn somewhere scenic so reviewers see a good frame
  immediately on PIE

The location matters less than the visual: pick somewhere that
combines water + buildings + visible terrain. Suggestions:

| Location | Why it demos well |
|---|---|
| **Diani Beach, Kenya** (-4.323, 39.575) | Coast + beach + greenery; aligns with the Tembea project context. |
| **Lake Naivasha, Kenya** (-0.766, 36.353) | Lake + rift hills + farms; varied layer classification. |
| **Salzburg, Austria** (47.797, 13.045) | City + river + low alpine hills; recognisable. |
| **Reykjavík harbour** (64.150, -21.940) | Ocean + island + city; dramatic Z range. |

The current dev landscape is Kisumu, which is fine but the lake
dominates and you lose the layer variety. Diani or Salzburg show off
more of what the plugin does.

## Step-by-step

### 1. Fresh empty level in the plugin Content folder

```
File → New Level → Empty Open World
```

Save as `Content/Sample/Demo_Mapbox.umap` **inside the plugin** (not the
project). You may need to enable *Show Plugin Content* in the Content
Browser's filter to see the path.

### 2. Fetch a small landscape

Open the importer (`Tools → Mapbox Landscape → Open Landscape Importer`).
Accept the Mapbox TOS banner if it's still showing.

Configure:

- **Coordinate Mode**: Center Point & Radius
- **Center Latitude / Longitude**: see the table above
- **Radius Km**: `5` (small enough to fetch in 5–10 minutes, large
  enough to look impressive)
- **Z Exaggeration**: `1.5` (so the demo feels three-dimensional even
  at modest scales)
- **Tiles Per Landscape Side**: `4` (default — gives a grid of small
  proxies that show off the per-chunk architecture)
- **Satellite Mode**: `BlendIntoMaterial`
- Layers: leave defaults

Click **Fetch Landscape**. Wait for completion (no errors in the log).

### 3. Run World Partition conversion

```
Build → World Partition → Convert Level
```

Accept the defaults. This is the slow part — let it finish before
saving.

### 4. Scrub the API key out

Before committing the level, the saved transient assets (sat textures,
material instances) may still reference the user-specific Mapbox key
via baked URLs. Open `Edit → Project Settings → Plugins → Mapbox
Landscape`, **clear the API Key field**, save settings. Then re-save
the level. This ensures the level loads cleanly for reviewers who
haven't pasted their own key yet (the existing materials and textures
have no live network dependency — only further *Fetch* clicks need the
key).

### 5. Add a starter camera / player spawn

```
Place Actors → Player Start
```

Position it ~30m above terrain, facing the most scenic part of the
fetched area. Add a `PostProcessVolume` (unbound) with a mild exposure
clamp so reviewers don't get blown-out skies on first load.

### 6. Save and verify

Save the level (`Ctrl+S`). Close and reopen the project. Open
`Content/Sample/Demo_Mapbox.umap` — confirm it loads with terrain +
imagery + scatter visible, no missing-asset warnings, no Mapbox key
required.

### 7. Commit

The level + its associated generated content (material instances,
satellite textures, PCG graph instances) all live under
`Content/Sample/` and `Content/MapboxLandscape/<level-name>/`. Add
them all and commit:

```bash
cd Plugins/MapboxLandscape
git add Content/
git commit -m "Add Demo_Mapbox sample level (Diani 5km)"
git push
```

Verify by running `RunUAT BuildPlugin` (see CHECKLIST.md) — if the
sample level is properly inside `Content/`, it ends up in the
packaged plugin's `Content/` and ships to Fab buyers as part of the
download.
