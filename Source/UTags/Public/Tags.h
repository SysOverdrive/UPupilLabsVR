// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Andrei Haidu (http://haidu.eu)

#pragma once
#include "CoreMinimal.h"
#include "EngineUtils.h"
#include "Tags.generated.h"

/**
* Helper functions for manipulating tags with key value pairs
*
*  Correctly written tag example ["TagType;Key1,Value1;Key2,Value2;Key3,Value3;"]:
*  - first word always represents the TagType, this is followed by a semicolon
*  - separate the [Key] from the [Value] using a comma 
*  - separate the [Key,Value]-pairs using a semicolon
*  - always end the tag description with a semicolon
*  - do NOT use white spaces in the tag descriptions
*/
USTRUCT()
struct UTAGS_API FTags
{
	GENERATED_USTRUCT_BODY()

	///////////////////////////////////////////////////////////////////////////
	// Return the index where the tag type was found in the array
	static int32 GetTagTypeIndex(const TArray<FName>& InTags, const FString& TagType);

	// Return the index where the tag type was found in the actor's array
	static int32 GetTagTypeIndex(AActor* Actor, const FString& TagType);

	// Return the index where the tag type was found in the component's array
	static int32 GetTagTypeIndex(UActorComponent* Component, const FString& TagType);

	// Return the index where the tag type was found in the object
	static int32 GetTagTypeIndex(UObject* Object, const FString& TagType);

	///////////////////////////////////////////////////////////////////////////
	// Check if type exists in tag
	static bool HasType(const FName& InTag, const FString& TagType);

	// Check if type exists tag array
	static bool HasType(const TArray<FName>& InTags, const FString& TagType);

	// Check if type exists from actor
	static bool HasType(AActor* Actor, const FString& TagType);

	// Check if type exists from component
	static bool HasType(UActorComponent* Component, const FString& TagType);

	// Check if type exists from object
	static bool HasType(UObject* Object, const FString& TagType);


	///////////////////////////////////////////////////////////////////////////
	// Check if key exists in tag
	static bool HasKey(const FName& InTag, const FString& TagKey);

	// Check if key exists tag array
	static bool HasKey(const TArray<FName>& InTags, const FString& TagType, const FString& TagKey);

	// Check if key exists from actor
	static bool HasKey(AActor* Actor, const FString& TagType, const FString& TagKey);

	// Check if key exists from component
	static bool HasKey(UActorComponent* Component, const FString& TagType, const FString& TagKey);
	
	// Check if key exists from object
	static bool HasKey(UObject* Object, const FString& TagType, const FString& TagKey);


	///////////////////////////////////////////////////////////////////////////
	// Check if key value pair exists in tag
	static bool HasKeyValuePair(const FName& InTag, const FString& TagKey, const FString& TagValue);

	// Check if key value pair exists in tag array
	static bool HasKeyValuePair(const TArray<FName>& InTags, const FString& TagType, const FString& TagKey, const FString& TagValue);

	// Check if key value pair exists in actor tags
	static bool HasKeyValuePair(AActor* Actor, const FString& TagType, const FString& TagKey, const FString& TagValue);

	// Check if key value pair exists in component tags
	static bool HasKeyValuePair(UActorComponent* Component, const FString& TagType, const FString& TagKey, const FString& TagValue);

	// Check if key value pair exists in object
	static bool HasKeyValuePair(UObject* Object, const FString& TagType, const FString& TagKey, const FString& TagValue);


	///////////////////////////////////////////////////////////////////////////
	// Get tag key value from tag
	static FString GetKeyValue(const FName& InTag, const FString& TagKey);

	// Get tag key value from tag array
	static FString GetKeyValue(const TArray<FName>& InTags, const FString& TagType, const FString& TagKey);

	// Get tag key value from actor
	static FString GetKeyValue(AActor* Actor, const FString& TagType, const FString& TagKey);

	// Get tag key value from component
	static FString GetKeyValue(UActorComponent* Component, const FString& TagType, const FString& TagKey);

	// Get tag key value from object
	static FString GetKeyValue(UObject* Object, const FString& TagType, const FString& TagKey);


	///////////////////////////////////////////////////////////////////////////
	// Add tag key value to tag, if bReplaceExisting is true, replace existing value
	static bool AddKeyValuePair(FName& InTag, const FString& TagKey, const FString& TagValue, bool bReplaceExisting = true);

	// Add tag key value to tags, if bReplaceExisting is true, replace existing value
	static bool AddKeyValuePair(TArray<FName>& InTags, const FString& TagType, const FString& TagKey, const FString& TagValue, bool bReplaceExisting = true);

	// Add tag key value to actor, if bReplaceExisting is true, replace existing value
	static bool AddKeyValuePair(AActor* Actor, const FString& TagType, const FString& TagKey, const FString& TagValue, bool bReplaceExisting = true);

	// Add tag key value to component, if bReplaceExisting is true, replace existing value
	static bool AddKeyValuePair(UActorComponent* Component,	const FString& TagType,	const FString& TagKey, const FString& TagValue,	bool bReplaceExisting = true);

	// Add tag key value to object, if bReplaceExisting is true, replace existing value
	static bool AddKeyValuePair(UObject* Object, const FString& TagType, const FString& TagKey, const FString& TagValue, bool bReplaceExisting = true);


	///////////////////////////////////////////////////////////////////////////
	//Add array of tag key values to tag, if bReplaceExisting is true, replace existing value
	static bool AddKeyValuePairs(FName& InTag, const TArray<TPair<FString, FString>>& InKeyValuePairs, bool bReplaceExisting = true);

	// Add array of tag key values to tags, if bReplaceExisting is true, replace existing value
	static bool AddKeyValuePairs(TArray<FName>& InTags, const FString& TagType, const TArray<TPair<FString, FString>>& InKeyValuePairs, bool bReplaceExisting = true);

	// Add array of tag key values to the actor,, if bReplaceExisting is true, replace existing value
	static bool AddKeyValuePairs(AActor* Actor, const FString& TagType, const TArray<TPair<FString, FString>>& InKeyValuePairs, bool bReplaceExisting = true);

	// Add array of tag key values to component, if bReplaceExisting is true, replace existing value
	static bool AddKeyValuePairs(UActorComponent* Component, const FString& TagType, const TArray<TPair<FString, FString>>& InKeyValuePairs, bool bReplaceExisting = true);

	// Add array of tag key values to object, if bReplaceExisting is true, replace existing value
	static bool AddKeyValuePairs(UObject* Object, const FString& TagType, const TArray<TPair<FString, FString>>& InKeyValuePairs, bool bReplaceExisting = true);


	///////////////////////////////////////////////////////////////////////////
	//Add map of tag key values to tag, if bReplaceExisting is true, replace existing value
	static bool AddKeyValuePairs(FName& InTag, const TMap<FString, FString>& InKeyValuePairs, bool bReplaceExisting = true);

	// Add map of tag key values to tags, if bReplaceExisting is true, replace existing value
	static bool AddKeyValuePairs(TArray<FName>& InTags, const FString& TagType, const TMap<FString, FString>& InKeyValuePairs, bool bReplaceExisting = true);

	// Add map of tag key values to the actor,, if bReplaceExisting is true, replace existing value
	static bool AddKeyValuePairs(AActor* Actor, const FString& TagType, const TMap<FString, FString>& InKeyValuePairs, bool bReplaceExisting = true);

	// Add map of tag key values to component, if bReplaceExisting is true, replace existing value
	static bool AddKeyValuePairs(UActorComponent* Component, const FString& TagType, const TMap<FString, FString>& InKeyValuePairs, bool bReplaceExisting = true);
	
	// Add map of tag key values to object, if bReplaceExisting is true, replace existing value
	static bool AddKeyValuePairs(UObject* Object, const FString& TagType, const TMap<FString, FString>& InKeyValuePairs, bool bReplaceExisting = true);


	///////////////////////////////////////////////////////////////////////////
	// Remove tag key value from tags
	static bool RemoveKeyValuePair(FName& InTag, const FString& TagKey);

	// Remove tag key value from tags
	static bool RemoveKeyValuePair(TArray<FName>& InTags, const FString& TagType, const FString& TagKey);

	// Remove tag key value from actor
	static bool RemoveKeyValuePair(AActor* Actor, const FString& TagType, const FString& TagKey);

	// Remove tag key value from component
	static bool RemoveKeyValuePair(UActorComponent* Component, const FString& TagType, const FString& TagKey);

	// Remove all tag key values from world
	static bool RemoveAllKeyValuePairs(UWorld* World, const FString& TagType, const FString& TagKey);

	// Remove all tag key values from world
	DEPRECATED(4.19, "RemoveKeyValuePairs is deprecated.  Use RemoveAllKeyValuePairs instead")
	static bool RemoveKeyValuePairs(UWorld* World, const FString& TagType, const FString& TagKey);



	///////////////////////////////////////////////////////////////////////////
	// Get tag key value pairs from tag array
	static TMap<FString, FString> GetKeyValuePairs(const TArray<FName>& InTags, const FString& TagType);

	// Get tag key value pairs from actor
	static TMap<FString, FString> GetKeyValuePairs(AActor* Actor, const FString& TagType);

	// Get tag key value pairs from component
	static TMap<FString, FString> GetKeyValuePairs(UActorComponent* Component, const FString& TagType);

	// Get tag key value pairs from object
	static TMap<FString, FString> GetKeyValuePairs(UObject* Object, const FString& TagType);


	///////////////////////////////////////////////////////////////////////////
	// Get all objects (actor and actor components) to tag key value pairs from world
	static TMap<UObject*, TMap<FString, FString>> GetObjectsToKeyValuePairs(UWorld* World, const FString& TagType);

	// Get all actors to tag key value pairs from world
	static TMap<AActor*, TMap<FString, FString>> GetActorsToKeyValuePairs(UWorld* World, const FString& TagType);

	// Get all components to tag key value pairs from world
	static TMap<UActorComponent*, TMap<FString, FString>> GetComponentsToKeyValuePairs(UWorld* World, const FString& TagType);


	/////////////////////////////////////////////////////////////////////////
	// Get all objects (actor and actor components) to tag key value
	static TMap<UObject*, FString> GetObjectsToKeyValue(UWorld* World, const FString& TagType, const FString& TagKey);

	// Get all actors to tag key value
	static TMap<AActor*, FString> GetActorsToKeyValue(UWorld* World, const FString& TagType, const FString& TagKey);

	// Get all components to tag key value
	static TMap<UActorComponent*, FString> GetComponentsToKeyValue(UWorld* World, const FString& TagType, const FString& TagKey);


	/////////////////////////////////////////////////////////////////////////
	// Get key values to objects (actor and actor components)
	static TMap<FString, UObject*> GetKeyValuesToObject(UWorld* World, const FString& TagType, const FString& TagKey);

	// Get tag key values to actors
	static TMap<FString, AActor*> GetKeyValuesToActor(UWorld* World, const FString& TagType, const FString& TagKey);

	// Get tag key values to components
	static TMap<FString, UActorComponent*> GetKeyValuesToComponents(UWorld* World, const FString& TagType, const FString& TagKey);


	///////////////////////////////////////////////////////////////////////////
	// Get all actors with the key value pair as array
	static TArray<AActor*> GetActorsWithKeyValuePair(UWorld* World, const FString& TagType, const FString& TagKey, const FString& TagValue);

	// Get all actors with the key value pair as set
	static TSet<AActor*> GetActorsWithKeyValuePairAsSet(UWorld* World, const FString& TagType, const FString& TagKey, const FString& TagValue);

	// Get all components with the key value pair as array
	static TArray<UActorComponent*> GetComponentsWithKeyValuePair(UWorld* World, const FString& TagType, const FString& TagKey, const FString& TagValue);

	// Get all components with the key value pair as set
	static TSet<UActorComponent*> GetComponentsWithKeyValuePairAsSet(UWorld* World, const FString& TagType, const FString& TagKey, const FString& TagValue);
	

	///////////////////////////////////////////////////////////
	// Get all actors with the key value pair	
	static TSet<AActor*> GetActorSetWithKeyValuePair(UWorld* World, const FString& TagType, const FString& TagKey, const FString& TagValue);

	// Gets all components with the key value pair
	static TSet<UActorComponent*> GetComponentSetWithKeyValuePair(UWorld* World, const FString& TagType, const FString& TagKey, const FString& TagValue);
};
