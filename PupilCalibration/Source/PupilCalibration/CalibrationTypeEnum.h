// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Engine/UserDefinedEnum.h"
#include "CalibrationTypeEnum.generated.h"

/**
 * 
 */
UENUM(BlueprintType)
enum class ECalibrationType : uint8
{
	_2D	UMETA(DisplayName = "2D"),
	_3D	UMETA(DisplayName = "3D"),
	MAX
};

UCLASS()
class PUPILCALIBRATION_API UCalibrationTypeEnum : public UUserDefinedEnum
{
	GENERATED_BODY()
	
	
	
	
};
