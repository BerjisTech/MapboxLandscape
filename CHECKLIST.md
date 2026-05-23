# Fab Submission Checklist

Audit performed 2026-05-23. Decisions locked in: Fab Content License only, Win64 only, all URLs point at the GitHub repo.

## Hard blockers

- [x] **Mapbox TOS handling.** Now in code + docs:
  - [x] README "Before you start" section covers what can ship (geometry yes, baked satellite needs commercial license, attribution required).
  - [x] First-run acknowledgement banner in the Importer panel — visible until the user clicks *I understand*, which persists `bAcceptedMapboxTerms` to `DefaultMapboxLandscape.ini`. Banner also links to the live Mapbox TOS.
  - [x] Attribution string stamped on every spawned landscape as the `MapboxLandscape:Attribution=© Mapbox © OpenStreetMap` actor tag — survives in saved levels so a build step can scrape it.
- [ ] **`Resources/Icon128.png`** — 128×128 PNG required by Fab. Folder scaffolded; `Resources/README.md` contains a Gemini-ready prompt and validation steps. Drop the PNG in and it's picked up automatically.
- [x] **Filled empty metadata fields in `MapboxLandscape.uplugin`:**
  - [x] `CreatedByURL` → `https://github.com/BerjisTech`
  - [x] `DocsURL` → `https://github.com/BerjisTech/MapboxLandscape/tree/master/wiki`
  - [x] `SupportURL` → `https://github.com/BerjisTech/MapboxLandscape/issues`
  - [x] `MarketplaceURL` intentionally empty — set by Fab on submission.
  - [x] `CreatedBy` updated from `Airmuseum` to `BerjisTech`.
- [x] **`LICENSE.md`** added at repo root. Covers: Fab Content License for buyers, evaluation-only for GitHub clones, third-party data terms (Mapbox + OSM), attribution requirements, no warranty.

## Submission-blocking but easy

- [ ] **Marketing assets.** **YOU NEED TO PROVIDE THESE** — can't be auto-generated.
  - [ ] 1× featured image, 1920×1080
  - [ ] 5+ gallery images, 1920×1080 (importer panel, fetched landscape, layer painting, PCG scatter, before/after)
  - [ ] Optional but high-conversion: 30-60s demo video
- [ ] **Sample/demo level (`.umap`)** in `Content/`. Step-by-step in `SAMPLE_LEVEL.md` (~30 min, location suggestions included). Needs you in the editor.
- [x] **`PlatformAllowList` declared in `.uplugin`** — set to `["Win64"]` matching your tested platform.
- [ ] **Engine version specificity.** Currently `MapboxLandscape.uplugin` is generic; on Fab submission you tag it `5.7`. Decide before submit whether to backport to 5.4/5.5/5.6 for a larger buyer pool — each backport is its own build + test pass.

## Recommended polish (not blocking but matters)

- [x] **Help button in the Importer panel** — added above the DetailsView, opens `DocsURL` in the user's browser.
- [ ] **Crash-safety test pass** in a clean project (not the airmuseum dev project): empty API key, wrong API key, no network, cancel mid-fetch, editor reload mid-fetch, 100km+ import. **NEEDS YOU IN THE EDITOR**.
- [x] **Memory-pressure note in the README** — added a per-radius table up top so 16GB buyers don't OOM unexpectedly.
- [ ] **Host the `wiki/` folder via GitHub Pages.** Two paths:
  - **Web UI (30 seconds):** github.com/BerjisTech/MapboxLandscape → Settings → Pages → Source: `Deploy from a branch` → Branch: `master` / Folder: `/docs` (you'll need to rename `wiki/` → `docs/` first since Pages only serves from `/` or `/docs`). Save.
  - **gh CLI (if authed):**
    ```bash
    gh auth login   # one-time, if not yet done
    gh api -X POST repos/BerjisTech/MapboxLandscape/pages \
      -f source.branch=master -f source.path=/docs
    ```
  Once it has a URL (e.g. `https://berjistech.github.io/MapboxLandscape/`), update `DocsURL` in `MapboxLandscape.uplugin` and `PluginDocsUrl` in `MapboxImporterPanel.cpp`.
- [ ] **Fab tags on submission:** *Real World, GIS, Procedural, Terrain Generation, Mapbox* (in addition to the existing `Landscape` category).

## Verification before clicking submit

- [ ] Plugin installs cleanly into a brand-new UE 5.7 project (not via copy from dev project — actually unzip the release artifact).
- [ ] Whole fetch flow works end-to-end with a fresh user account and fresh Mapbox key.
- [x] **No references to `airmuseum` or dev paths anywhere in source.** Audited — only one stale `Airmuseum` mention in `wiki/world-partition.md` (about flight-sim cell sizing) rewritten to be generic.
- [x] **`.gitignore` excludes** `Binaries/`, `Intermediate/`, `Saved/`, `DerivedDataCache/`, IDE droppings.
- [x] **`RunUAT BuildPlugin` dry run passes** (2026-05-23). `BUILD SUCCESSFUL`, ExitCode=0, 69 MB packaged artifact at `C:\Temp\MapboxLandscape_Fab\` with Win64 DLL + PDB + Source + Content. Re-run before final submit:
  ```
  "D:\Epic Games\UE_5.7\Engine\Build\BatchFiles\RunUAT.bat" BuildPlugin -Plugin="F:\airmuseum\Plugins\MapboxLandscape\MapboxLandscape.uplugin" -Package="C:\Temp\MapboxLandscape_Fab" -TargetPlatforms=Win64
  ```
  Note: the build log surfaces a `Module 'Http' has incorrect text case` warning attributed to a different plugin (`LandscapingMapbox.uplugin`) in the project. Not from this plugin — non-blocking.

## What's left for you (in order of importance)

1. **Icon128.png** in `Resources/` — blocker. Gemini prompt + drop-in instructions in `Resources/README.md`.
2. **Sample `.umap`** in `Content/` — blocker. Full walkthrough in `SAMPLE_LEVEL.md` (~30 min, location suggestions).
3. **Marketing screenshots** — 5+ at 1920×1080 of the importer panel + a rendered landscape + satellite-textured terrain + PCG scatter + before/after the fetch. Best done after #2 so the sample level is the subject.
4. **Demo video** — optional but Fab buyers convert significantly higher when there is one. 30–60s screen capture is enough.
5. **Clean-project test pass** — install the plugin into a fresh UE 5.7 project, do one full fetch end-to-end, fix anything that breaks.
6. **GitHub Pages for the wiki** — one-time setup, commands above.
7. **Final `RunUAT BuildPlugin`** after the sample level lands — confirm `Content/Sample/` ends up in the packaged artifact.
