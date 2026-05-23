# Fab Submission Checklist

Audit performed 2026-05-23. Estimated effort to submission-ready: 3-5 focused days.

## Hard blockers

- [ ] **Mapbox TOS handling.** Mapbox's developer terms don't allow permanent tile caching, and baking satellite imagery into a shipping commercial game is gray-area. Needs:
  - [ ] README section *"What you can legally ship from a Mapbox build"* (geometry from height tiles = derivative work, generally OK; satellite textures baked into shipping commercial game = needs a Mapbox commercial license).
  - [ ] First-run dialog in the Importer panel linking to Mapbox TOS, with an "I understand" acknowledgement.
  - [ ] Required Mapbox attribution string ("© Mapbox © OpenStreetMap") visible somewhere on output — e.g. as a landscape actor tag, or burnt into the satellite texture's corner. Without this Mapbox can revoke API keys.
- [ ] **`Resources/Icon128.png`** — 128×128 PNG required by Fab. Without it, the plugin shows the default puzzle-piece icon in the Plugins window.
- [ ] **Fill empty metadata fields in `MapboxLandscape.uplugin`:**
  - [ ] `CreatedByURL` — your brand site
  - [ ] `DocsURL` — hosted wiki (GitHub Pages from `wiki/` is one command)
  - [ ] `SupportURL` — GitHub issues URL or support email
  - [ ] `MarketplaceURL` — leave empty until Fab assigns one
- [ ] **`LICENSE` file** at repo root. Fab plugins are governed by the Fab Content License once submitted, but a bare repo with no LICENSE confuses validation. MIT, "All rights reserved, distribution via Fab only", or similar.

## Submission-blocking but easy

- [ ] **Marketing assets:**
  - [ ] 1× featured image, 1920×1080
  - [ ] 5+ gallery images, 1920×1080 (importer panel, fetched landscape, layer painting, PCG scatter, before/after)
  - [ ] Optional but high-conversion: 30-60s demo video
- [ ] **Sample/demo level (`.umap`)** in `Content/`. Currently ships a material and a PCG graph but no level. Best done as a small pre-fetched region (Diani, Kilifi) saved with the API-key portion stripped so reviewers can open it without setup.
- [ ] **`SupportedTargetPlatforms` declared in `.uplugin`.** If you only test Win64, declare it explicitly — Fab will otherwise assume all platforms and reject when their automated build fails on Mac/Linux.
- [ ] **Engine version specificity.** Fab requires version-specific submissions. Currently tested on 5.7 only. Decide whether to also build/test on 5.4/5.5/5.6 (more buyers) or ship 5.7-only.

## Recommended polish (not blocking but matters)

- [ ] **Help button in the Importer panel** that opens your hosted docs (`DocsURL`). Buyers shouldn't have to leave the editor to figure out the workflow.
- [ ] **Crash-safety test pass** in a clean project (not the airmuseum dev project): empty API key, wrong API key, no network, cancel mid-fetch, editor reload mid-fetch, 100km+ import.
- [ ] **Memory-pressure note in the README.** 70-100km imports peak at ~500MB+. `wiki/memory-sizing.md` covers it; surface it in the main README too so 16GB-machine buyers don't OOM.
- [ ] **Host the `wiki/` folder.** Currently buyers can only find it by browsing the GitHub repo. GitHub Pages from `wiki/` is one command. Then point `DocsURL` at the hosted version.
- [ ] **Fab tags on submission:** *Real World, GIS, Procedural, Terrain Generation, Mapbox* (in addition to the existing `Landscape` category).

## Verification before clicking submit

- [ ] Plugin installs cleanly into a brand-new UE 5.7 project (not via copy from dev project — actually unzip the release artifact).
- [ ] Whole fetch flow works end-to-end with a fresh user account and fresh Mapbox key.
- [ ] No references to `airmuseum`, your dev paths, internal URLs anywhere in the shipping ZIP.
- [ ] No `Binaries/`, `Intermediate/`, `Saved/`, `DerivedDataCache/`, `.git/` in the ZIP (`.gitignore` already handles these in source; double-check the release artifact).
- [ ] Final build with `RunUAT BuildPlugin` from a clean engine install — that's the actual command Fab's validation uses.
