#include "MapboxMvtReader.h"

namespace MapboxMvt
{
	// ---------- Protobuf wire-format reader (minimal) ----------
	struct FPbReader
	{
		const uint8* Data = nullptr;
		const uint8* End = nullptr;

		bool AtEnd() const { return Data >= End; }

		uint64 ReadVarint()
		{
			uint64 Result = 0;
			int32 Shift = 0;
			while (Data < End)
			{
				const uint8 B = *Data++;
				Result |= ((uint64)(B & 0x7F)) << Shift;
				if (!(B & 0x80)) break;
				Shift += 7;
				if (Shift >= 64) break;
			}
			return Result;
		}

		int64 ReadSint() { const uint64 V = ReadVarint(); return (int64)((V >> 1) ^ -(int64)(V & 1)); }

		FString ReadString()
		{
			const uint64 Len = ReadVarint();
			if (Data + Len > End) { Data = End; return FString(); }
			FString S((int32)Len, (const ANSICHAR*)Data);
			Data += Len;
			return S;
		}

		void SkipField(uint32 Tag)
		{
			const uint32 WireType = Tag & 0x7;
			switch (WireType)
			{
			case 0: ReadVarint(); break;
			case 1: Data = FMath::Min(Data + 8, End); break;
			case 2: { const uint64 L = ReadVarint(); Data = FMath::Min(Data + L, End); break; }
			case 5: Data = FMath::Min(Data + 4, End); break;
			default: Data = End; break;
			}
		}

		FPbReader SubReader()
		{
			const uint64 Len = ReadVarint();
			FPbReader Sub;
			Sub.Data = Data;
			Sub.End = FMath::Min(Data + Len, End);
			Data = Sub.End;
			return Sub;
		}
	};

	// ---------- MVT-specific layer + value tables ----------
	enum class EValueKind : uint8 { String, Int, Float, Bool, None };

	struct FParseValue
	{
		EValueKind Kind = EValueKind::None;
		int32 Index = -1;
	};

	struct FParsingLayer
	{
		FString Name;
		uint32 Extent = 4096;
		TArray<FString> Keys;
		TArray<FString> ValuesString;
		TArray<int64> ValuesInt;
		TArray<double> ValuesFloat;
		TArray<bool> ValuesBool;
		TArray<FParseValue> Values;
	};

	static FString ValueToString(const FParsingLayer& L, const FParseValue& V)
	{
		switch (V.Kind)
		{
		case EValueKind::String: return L.ValuesString.IsValidIndex(V.Index) ? L.ValuesString[V.Index] : FString();
		case EValueKind::Int:    return L.ValuesInt.IsValidIndex(V.Index) ? FString::Printf(TEXT("%lld"), L.ValuesInt[V.Index]) : FString();
		case EValueKind::Float:  return L.ValuesFloat.IsValidIndex(V.Index) ? FString::Printf(TEXT("%g"), L.ValuesFloat[V.Index]) : FString();
		case EValueKind::Bool:   return L.ValuesBool.IsValidIndex(V.Index) ? (L.ValuesBool[V.Index] ? TEXT("true") : TEXT("false")) : FString();
		default: return FString();
		}
	}

	static void ParseValue(FPbReader R, FParsingLayer& L)
	{
		FParseValue V;
		while (!R.AtEnd())
		{
			const uint32 Tag = (uint32)R.ReadVarint();
			const uint32 Field = Tag >> 3;
			switch (Field)
			{
			case 1: V.Index = L.ValuesString.Add(R.ReadString()); V.Kind = EValueKind::String; break;
			case 2: { const float F = *(const float*)R.Data; R.Data += 4; V.Index = L.ValuesFloat.Add((double)F); V.Kind = EValueKind::Float; break; }
			case 3: { const double D = *(const double*)R.Data; R.Data += 8; V.Index = L.ValuesFloat.Add(D); V.Kind = EValueKind::Float; break; }
			case 4: V.Index = L.ValuesInt.Add((int64)R.ReadVarint()); V.Kind = EValueKind::Int; break;
			case 5: V.Index = L.ValuesInt.Add((int64)R.ReadVarint()); V.Kind = EValueKind::Int; break;
			case 6: V.Index = L.ValuesInt.Add(R.ReadSint()); V.Kind = EValueKind::Int; break;
			case 7: V.Index = L.ValuesBool.Add(R.ReadVarint() != 0); V.Kind = EValueKind::Bool; break;
			default: R.SkipField(Tag); break;
			}
		}
		L.Values.Add(V);
	}

	static void DecodeGeometry(const TArray<uint32>& G, EFeatureType GeomType, TArray<TArray<FVector2D>>& OutGeom)
	{
		int32 Cx = 0, Cy = 0;
		int32 i = 0;
		TArray<FVector2D> Current;

		while (i < G.Num())
		{
			const uint32 CmdInt = G[i++];
			const uint32 Cmd = CmdInt & 0x7;
			const uint32 Count = CmdInt >> 3;

			if (Cmd == 1) // MoveTo
			{
				if (Current.Num() >= 1)
				{
					if ((GeomType == EFeatureType::LineString && Current.Num() > 1) ||
					    (GeomType == EFeatureType::Polygon && Current.Num() > 2) ||
					    (GeomType == EFeatureType::Point))
					{
						OutGeom.Add(MoveTemp(Current));
					}
					Current.Reset();
				}
				for (uint32 k = 0; k < Count && (i + 1) < G.Num(); ++k)
				{
					const int32 Dx = (int32)((G[i] >> 1) ^ -(int32)(G[i] & 1)); ++i;
					const int32 Dy = (int32)((G[i] >> 1) ^ -(int32)(G[i] & 1)); ++i;
					Cx += Dx; Cy += Dy;
					if (GeomType == EFeatureType::Point)
					{
						OutGeom.Add({ FVector2D(Cx, Cy) });
					}
					else
					{
						Current.Add(FVector2D(Cx, Cy));
					}
				}
			}
			else if (Cmd == 2) // LineTo
			{
				for (uint32 k = 0; k < Count && (i + 1) < G.Num(); ++k)
				{
					const int32 Dx = (int32)((G[i] >> 1) ^ -(int32)(G[i] & 1)); ++i;
					const int32 Dy = (int32)((G[i] >> 1) ^ -(int32)(G[i] & 1)); ++i;
					Cx += Dx; Cy += Dy;
					Current.Add(FVector2D(Cx, Cy));
				}
			}
			else if (Cmd == 7) // ClosePath
			{
				if (Current.Num() > 0)
				{
					Current.Add(Current[0]);
				}
			}
		}
		if ((GeomType == EFeatureType::LineString && Current.Num() > 1) ||
		    (GeomType == EFeatureType::Polygon && Current.Num() > 2))
		{
			OutGeom.Add(MoveTemp(Current));
		}
	}

	static void ParseFeature(FPbReader R, FParsingLayer& L, FLayer& OutLayer)
	{
		FFeature F;
		TArray<uint32> Tags;
		TArray<uint32> Geom;
		uint32 RawType = 0;
		while (!R.AtEnd())
		{
			const uint32 Tag = (uint32)R.ReadVarint();
			const uint32 Field = Tag >> 3;
			switch (Field)
			{
			case 1: R.ReadVarint(); break; // id
			case 2:
			{
				FPbReader Sub = R.SubReader();
				while (!Sub.AtEnd()) Tags.Add((uint32)Sub.ReadVarint());
				break;
			}
			case 3: RawType = (uint32)R.ReadVarint(); break;
			case 4:
			{
				FPbReader Sub = R.SubReader();
				while (!Sub.AtEnd()) Geom.Add((uint32)Sub.ReadVarint());
				break;
			}
			default: R.SkipField(Tag); break;
			}
		}

		switch (RawType)
		{
		case 1: F.Type = EFeatureType::Point; break;
		case 2: F.Type = EFeatureType::LineString; break;
		case 3: F.Type = EFeatureType::Polygon; break;
		default: F.Type = EFeatureType::Unknown; break;
		}

		// Resolve tag key/value indices into a TMap for caller convenience.
		for (int32 i = 0; i + 1 < Tags.Num(); i += 2)
		{
			const uint32 KeyIdx = Tags[i];
			const uint32 ValIdx = Tags[i + 1];
			if (KeyIdx >= (uint32)L.Keys.Num() || ValIdx >= (uint32)L.Values.Num()) continue;
			F.Properties.Add(L.Keys[KeyIdx], ValueToString(L, L.Values[ValIdx]));
		}

		DecodeGeometry(Geom, F.Type, F.Geometry);

		OutLayer.Features.Add(MoveTemp(F));
	}

	static void ParseLayer(FPbReader R, FLayer& Out)
	{
		FParsingLayer L;
		while (!R.AtEnd())
		{
			const uint32 Tag = (uint32)R.ReadVarint();
			const uint32 Field = Tag >> 3;
			switch (Field)
			{
			case 1: L.Name = R.ReadString(); break;
			case 2: { FPbReader Sub = R.SubReader(); /* defer feature parse until keys/values populated */ break; }
			case 3: L.Keys.Add(R.ReadString()); break;
			case 4: ParseValue(R.SubReader(), L); break;
			case 5: L.Extent = (uint32)R.ReadVarint(); break;
			case 15: R.ReadVarint(); break; // version
			default: R.SkipField(Tag); break;
			}
		}

		Out.Name = L.Name;
		Out.Extent = L.Extent;
		// Features are parsed in a second pass below — see ParseTile.
	}

	bool ParseTile(const TArray<uint8>& Bytes, TArray<FLayer>& OutLayers)
	{
		// Two-pass parse per layer because MVT does NOT guarantee keys/values come before features in wire order
		// (though in practice they usually do). We collect features in a deferred pass after keys/values are known.

		FPbReader R; R.Data = Bytes.GetData(); R.End = R.Data + Bytes.Num();

		while (!R.AtEnd())
		{
			const uint32 Tag = (uint32)R.ReadVarint();
			const uint32 Field = Tag >> 3;
			if (Field != 3) { R.SkipField(Tag); continue; }

			FPbReader LayerReader = R.SubReader();

			// Pass 1: collect keys/values/extent/name + remember feature byte ranges.
			FParsingLayer L;
			TArray<FPbReader> FeatureBlocks;
			{
				FPbReader Walk = LayerReader;
				while (!Walk.AtEnd())
				{
					const uint32 Tag2 = (uint32)Walk.ReadVarint();
					const uint32 Field2 = Tag2 >> 3;
					switch (Field2)
					{
					case 1: L.Name = Walk.ReadString(); break;
					case 2: FeatureBlocks.Add(Walk.SubReader()); break;
					case 3: L.Keys.Add(Walk.ReadString()); break;
					case 4: ParseValue(Walk.SubReader(), L); break;
					case 5: L.Extent = (uint32)Walk.ReadVarint(); break;
					case 15: Walk.ReadVarint(); break;
					default: Walk.SkipField(Tag2); break;
					}
				}
			}

			// Pass 2: parse features using the populated key/value tables.
			FLayer Out;
			Out.Name = L.Name;
			Out.Extent = L.Extent;
			for (FPbReader& FB : FeatureBlocks)
			{
				ParseFeature(FB, L, Out);
			}

			OutLayers.Add(MoveTemp(Out));
		}

		return OutLayers.Num() > 0;
	}

	bool FeatureMatchesClass(const FFeature& Feature, const TArray<FString>& AllowedClasses)
	{
		if (AllowedClasses.IsEmpty()) return true;
		const FString* ClassVal = Feature.Properties.Find(TEXT("class"));
		if (!ClassVal) return false;
		for (const FString& Allowed : AllowedClasses)
		{
			if (Allowed.Equals(*ClassVal, ESearchCase::IgnoreCase)) return true;
		}
		return false;
	}

	double SignedRingArea(const TArray<FVector2D>& Ring)
	{
		const int32 N = Ring.Num();
		if (N < 3) return 0.0;
		double A = 0.0;
		for (int32 i = 0; i < N; ++i)
		{
			const FVector2D& P0 = Ring[i];
			const FVector2D& P1 = Ring[(i + 1) % N];
			A += (double)P0.X * P1.Y - (double)P1.X * P0.Y;
		}
		return 0.5 * A;
	}
}
