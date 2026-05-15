# Mapbox Landscape Plugin

This plugin allows you to fetch landscape heightmaps and metadata from Mapbox and create Unreal Engine landscapes.

## Features
- Fetches Terrain-RGB tiles for accurate height data.
- Fetches Mapbox Style tiles for metadata (landuse classification).
- Automatically creates `ALandscape` actors with multiple layers (Forest, Urban, Road, Water).
- Supports Z-scaling for real-world elevation.

## How to Use
1.  **Place the Actor:** Search for `MapboxLandscapeActor` in the Place Actors panel and drag it into your level.
2.  **Configure API Key:** Get a Mapbox Access Token and paste it into the `Api Key` field in the actor's details.
3.  **Set Coordinates:** Choose a `Coordinate Mode`:
    - **Bounding Box**: Manually enter North, South, East, and West latitudes/longitudes.
    - **Center Point & Radius**: Enter `Center Latitude`, `Center Longitude`, and a `Radius Km`. The plugin will calculate the bounding box for you.
    - **Tool String**: Paste a comma-separated string of coordinates from tools like [BBox Finder](https://maps.ludicdrive.com/) or [blender-osm](https://prochitecture.com/blender-osm/extent/). The plugin automatically detects `Lat, Lng` or `Lng, Lat` formats and finds the bounding box from any number of points (corners).
4.  **Adjust Zoom:** 
    - `Zoom Level`: 15 is usually good for high detail. The number of tiles is calculated automatically based on your coordinates and zoom level.
5.  **Fetch:** Click the `Fetch Landscape` button.

## Metadata Classification
The plugin uses a color-based classification system from the Mapbox style. For best results, use a Mapbox style that has clear, solid colors for different landuses.
- **Green** -> Forest
- **Gray/Neutral** -> Urban
- **Blue** -> Water
- **Default** -> Road

## Requirements
- Unreal Engine 5.7
- Mapbox API Key
- `LandscapeEditor` module (available in Editor builds)

## Integration with PCG
The created landscapes have layers named `Forest`, `Urban`, `Road`, and `Water`. You can use a **Landscape Layer Sampler** node in a PCG Graph to spawn trees, buildings, or other assets specifically on these layers.
