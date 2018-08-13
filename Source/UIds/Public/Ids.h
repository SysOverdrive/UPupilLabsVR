// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#pragma once

#include "EngineMinimal.h"
#include "Misc/Guid.h"
#include "Misc/Base64.h"
#include "Ids.generated.h"

/**
* Helper functions to generate UUIDs in base64 using FGuid
* and convert them back from base64
*/
USTRUCT(BlueprintType, Category = "UIds")
struct UIDS_API FIds
{
	GENERATED_BODY()

	// Encodes GUID to Base64
	static FString GuidToBase64(FGuid InGuid)
	{		
		FBufferArchive GuidBufferArchive;							// FBufferArchive inherits from TArray<uint8>
		GuidBufferArchive << InGuid;
		FString GuidInBase64 = FBase64::Encode(GuidBufferArchive);	// Needs binary as TArray<uint8>
		GuidInBase64.RemoveFromEnd(TEXT("=="));						// Remove last unnecessary two equal characters from end
		return GuidInBase64;
	}

	// Creates a new GUID and encodes it to Base64
	static FString NewGuidInBase64()
	{
		FGuid NewGuid = FGuid::NewGuid();
		return GuidToBase64(NewGuid);
	}

	// Encodes GUID to Base64
	static FString GuidToBase64Url(FGuid InGuid)
	{
		FBufferArchive GuidBufferArchive;							// FBufferArchive inherits from TArray<uint8>
		GuidBufferArchive << InGuid;
		FString GuidInBase64 = FBase64::Encode(GuidBufferArchive);	// Needs binary as TArray<uint8>
		GuidInBase64.RemoveFromEnd(TEXT("=="));						// Remove last unnecessary two equal characters from end
		return Base64ToBase64Url(GuidInBase64);
	}

	// Creates a new GUID and encodes it to Base64Url
	static FString NewGuidInBase64Url()
	{
		FGuid NewGuid = FGuid::NewGuid();
		return GuidToBase64Url(NewGuid);
	}

	// Creates a GUID from Base64
	static FGuid Base64ToGuid(const FString& InGuidInBase64, bool bNewIfInvalid = false)
	{
		TArray<uint8> GuidBinaryArray;
		FBase64::Decode(InGuidInBase64, GuidBinaryArray);
		FMemoryReader Ar = FMemoryReader(GuidBinaryArray, true);
		Ar.Seek(0);
		FGuid LocalGuid;
		Ar << LocalGuid;
		if (bNewIfInvalid)
		{
			if (LocalGuid.IsValid())
			{
				return LocalGuid;
			}
			else
			{
				return FGuid::NewGuid();
			}
		}
		else
		{
			return LocalGuid;
		}
	}

	// Creates a GUID from Base64Url
	static FGuid Base64UrlToGuid(const FString& InGuidInBase64, bool bNewIfInvalid = false)
	{
		return Base64ToGuid(Base64UrlToBase64(InGuidInBase64), bNewIfInvalid);
	}

	// Convert Base64 to Base64Url (e.g. replace '+', '/' with '_','-')
	FORCEINLINE static FString Base64ToBase64Url(const FString& InBase64)
	{
		FString Base64Url = InBase64;
		Base64Url.ReplaceInline(TEXT("+"), TEXT("-"), ESearchCase::CaseSensitive);
		Base64Url.ReplaceInline(TEXT("/"), TEXT("_"), ESearchCase::CaseSensitive);
		return Base64Url;
	}

	// Convert Base64Url to Base64 (e.g. replace '_','-' with '+', '/')
	FORCEINLINE static FString Base64UrlToBase64(const FString& InBase64Url)
	{
		FString Base64 = InBase64Url;
		Base64.ReplaceInline(TEXT("-"), TEXT("+"), ESearchCase::CaseSensitive);
		Base64.ReplaceInline(TEXT("_"), TEXT("/"), ESearchCase::CaseSensitive);
		return Base64;
	}
};
