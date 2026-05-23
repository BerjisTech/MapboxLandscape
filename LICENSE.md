# License

When obtained through Epic Games' Fab marketplace, this plugin is licensed
to you under the [Fab Content License Agreement](https://www.fab.com/eula).
That agreement controls what you can do with the plugin and any content it
ships — please read it.

When obtained directly from this GitHub repository (https://github.com/BerjisTech/MapboxLandscape),
this plugin is provided **for evaluation only**. You may build it, run it
inside the Unreal Editor, and inspect the source, but you may **not**
redistribute the plugin or its compiled binaries, and you may not ship a
project that includes the plugin's source or compiled output without a
valid Fab license for each commercial seat that uses it.

## Third-party data

This plugin downloads data from Mapbox under the terms of your individual
Mapbox account. The plugin itself does NOT grant you any rights to Mapbox
data. Specifically:

- You must supply your own Mapbox access token (Project Settings → Plugins
  → Mapbox Landscape → API Key).
- Tile data fetched through the plugin is governed by the
  [Mapbox Terms of Service](https://www.mapbox.com/legal/tos), not by
  this license.
- Mapbox terrain-RGB and vector data baked into Unreal landscapes is a
  derivative work — generally permitted for personal use under Mapbox's
  evaluation terms. Shipping a commercial product containing baked Mapbox
  satellite imagery requires a Mapbox commercial agreement that you arrange
  directly with Mapbox.

OpenStreetMap data exposed through Mapbox vector tiles is © OpenStreetMap
contributors and made available under the
[Open Database License](https://opendatacommons.org/licenses/odbl/).

## Attribution

Any project that ships output produced by this plugin must visibly credit
Mapbox and OpenStreetMap (e.g. in a credits screen) per Mapbox's
attribution requirements. The plugin stamps the attribution string on
every spawned landscape actor as a tag — see `MapboxLandscape:Attribution`
in the actor's tags array — so it survives in saved levels and can be
surfaced programmatically.

## Warranty

Provided "as-is" without warranty of any kind. See the Fab Content License
for the complete disclaimer of warranties and limitation of liability.
