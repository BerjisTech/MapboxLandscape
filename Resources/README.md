# Resources

This folder is where Fab / the Plugins window picks up the plugin's icon
and any other branding assets.

## What goes here

| File | Required? | Size | Purpose |
|---|---|---|---|
| `Icon128.png` | **Yes** | 128 × 128 PNG | Shown in the editor's Plugins window and on the Fab listing tile. UE picks it up automatically. |
| `FeaturedNew.png` | Optional | 264 × 264 PNG | Featured-plugin highlight inside the editor. Skip unless we ever want to land in the featured carousel. |

The image at `Icon128.png` must be a plain PNG with alpha — no rounded
corners, no shadow, no padding. UE applies its own framing. Designs that
fill the full 128×128 with bleed-through colour look best in the Plugins
window grid.

## Gemini prompt for the icon

Paste this into Gemini (or any text-to-image model that can produce
clean 128×128 logo-style output) when you're ready to generate it. The
prompt is tuned to produce something on-brand for a Fab landscape /
geo tool, not a generic map pin:

```
A flat vector icon for a 3D landscape tool called "Mapbox Landscape".
128×128 pixels, square, with full alpha. The icon shows a stylised
3D terrain topology — concentric isolines or a low-poly mountain
silhouette — with a subtle Mapbox-blue (#4264FB) wash that fades to
a deep navy. No text, no map pin, no compass rose. Centered
composition, no padding, fills the canvas edge to edge. Bold,
high-contrast, readable at 32×32. Output as PNG with transparency.
```

If the first generation gives you a map pin or a globe (common
failure), iterate with: *"no pin, no globe — show the terrain
geometry itself, like a wireframe ridge or contour rings."*

## After the icon exists

Drop the PNG in this folder. No registration needed in the `.uplugin`
or anywhere else — UE looks for `Resources/Icon128.png` by convention.
Restart the editor, open the Plugins window, search for "Mapbox
Landscape", confirm the icon shows.
