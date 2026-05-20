#pragma once

#include "CoreMinimal.h"

/**
 * Minimal Mapbox Vector Tile (MVT) protobuf reader. Spec: https://github.com/mapbox/vector-tile-spec
 * Decodes layers + features + LineString/Polygon geometry. Resolves tag key/value indices
 * into a friendly TMap<FString, FString> per feature.
 *
 * Tile-local coords are in [0, Extent] (typically [0, 4096]). Convert to world via the importer's
 * tile-to-world mapping.
 */
namespace MapboxMvt
{
	enum class EFeatureType : uint8
	{
		Unknown = 0,
		Point = 1,
		LineString = 2,
		Polygon = 3,
	};

	struct FFeature
	{
		EFeatureType Type = EFeatureType::Unknown;

		/** All MVT tag key/value pairs already resolved to strings (numbers stringified). */
		TMap<FString, FString> Properties;

		/**
		 * For LineString: each entry is one polyline.
		 * For Polygon: each entry is one ring (first = outer, subsequent = holes per MVT spec; sign of signed area distinguishes).
		 * For Point: single-element arrays of length 1.
		 */
		TArray<TArray<FVector2D>> Geometry;
	};

	struct FLayer
	{
		FString Name;
		uint32 Extent = 4096;
		TArray<FFeature> Features;
	};

	/** Returns true if at least one layer was parsed. Bytes must be raw protobuf (no gzip wrapper). */
	MAPBOXLANDSCAPE_API bool ParseTile(const TArray<uint8>& Bytes, TArray<FLayer>& OutLayers);

	/** Returns true if Feature has a "class" property matching one of AllowedClasses (case-insensitive). Empty AllowedClasses = always matches. */
	MAPBOXLANDSCAPE_API bool FeatureMatchesClass(const FFeature& Feature, const TArray<FString>& AllowedClasses);

	/** Compute signed area of a ring (positive = outer in MVT convention). */
	MAPBOXLANDSCAPE_API double SignedRingArea(const TArray<FVector2D>& Ring);
}
