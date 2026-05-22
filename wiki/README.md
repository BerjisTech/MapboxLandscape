# MapboxLandscape — Wiki

Practical operating notes for the plugin. Read these before complaining about long fetches or memory warnings.

## Pages

- [Why is fetching slow?](why-slow.md) — where the time actually goes, what's avoidable, what isn't
- [Speed knobs & tradeoffs](speed-knobs.md) — the settings that move the needle, what to turn off when, with examples
- [Memory sizing & radius limits](memory-sizing.md) — how big a fetch your machine can take, WP vs non-WP, real numbers
- [World Partition streaming](world-partition.md) — what conversion does, when to skip it, manual re-run
- [World features](world-features.md) — roads/paths/railways as landscape splines (Blosm-style), Brushify road-dust recipe
- [Layer system](layers.md) — the 20-layer default set, how classification picks winners, the special Clear layer
- [Troubleshooting](troubleshooting.md) — flat landscapes, assertion crashes, missing textures, things that look broken
- [Workflow recipes](workflows.md) — "I want to do X" → concrete settings and steps
- [Architecture & internals](architecture.md) — the pipeline at a high level, where the bodies are buried

## Quick reference

| Want to… | Do this |
|---|---|
| Fast iteration on 5–10 km area | Open World level, default settings, leave WP convert ON |
| Big region (30+ km) but fast fetch | Turn OFF `bConvertToWorldPartitionStreaming`, click `Convert Generated Landscapes To Streaming` later |
| Huge region (50+ km), accept long fetch | WP level, WP convert ON, `PartitionBatchSize` = 4, walk away |
| Non-WP level | Up to ~15 km on 16 GB RAM; bigger needs more RAM |
| Smoother cliffs/slopes | Increase `HeightZoomBonus` to 1 (small areas only — 4× height requests) |
| More streaming granularity | Reduce `WorldPartitionGridSizeInComponents` (default 16 → 8 = 4× as many proxies) |
| Cancel a running fetch | Click `Cancel Fetch` in the importer panel |
| Generate roads + paths + rails from OSM | After landscape fetch: tick `Populate Roads`, click `Reset Road Classes To Defaults`, assign meshes, click `Populate World Features`. See [world-features.md](world-features.md) |
