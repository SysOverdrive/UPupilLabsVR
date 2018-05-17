// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "PupilTrackingStateEnum.generated.h"

/**
 * 
 */

UENUM(BlueprintType)
enum class EPupilTrackingState : uint8
{
	/**
	* Both pupils are being tracked successfully.
	*/
	BOTH	UMETA(DisplayName = "Both"),
	/**
	* Only one pupil is being tracked successfully.
	*/
	ONE		UMETA(DisplayName = "One"),
	/**
	* Neither pupil is being tracked successfully.
	*/
	NONE	UMETA(DisplayName = "None"),
	MAX
};

UCLASS()
class PUPILCALIBRATION_API UPupilTrackingStateEnum : public UUserDefinedEnum
{
	GENERATED_BODY()
	
	
	
	
};
