// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PupilTrackingStateEnum.h"
#include "CalibrationTypeEnum.h"

#include "CoreMinimal.h"
#include "GameFramework/GameMode.h"
#include "PupilCalibrationGameMode.generated.h"

/**
 * 
 */

UCLASS()
class PUPILCALIBRATION_API APupilCalibrationGameMode : public AGameMode
{
	GENERATED_BODY()
private:
	uint8 CalibrationLocationIndex = 0;

	UPROPERTY()
		FTimerHandle FocusMovementTimer;

protected:
	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pupil Calibration")
		float UpdatePupilTrackingInterval = 0.05f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pupil Calibration")
		float UpdateFocusLocationInterval = 5.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pupil Calibration")
		float FocusScale = 1.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pupil Calibration|2D")
		TArray<FVector2D> CalibrationLocations_2D;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pupil Calibration|2D")
		float CalibrationXDistance = 100.f;

	UPROPERTY(EditDefaultsOnly, BlueprintReadOnly, Category = "Pupil Calibration|3D")
		TArray<FVector> CalibrationLocations_3D;

	UPROPERTY()
		class AFocusActor* FocusActor;

	UPROPERTY()
		ECalibrationType CalibrationType = ECalibrationType::MAX;

protected:
	UPROPERTY()
		EPupilTrackingState PupilTrackingState;
	
public:
	UFUNCTION(BlueprintCallable)
		void BeginCalibration(ECalibrationType Calibration_Type = ECalibrationType::_2D);
protected:
	UFUNCTION()
		void UpdatePupilTrackingState();

	UFUNCTION()
		void UpdatePupilTrackingStateResponse();

	UFUNCTION()
		void OnPupilTrackingStateUpdated(EPupilTrackingState NewTrackingState);

	UFUNCTION()
		void MoveFocusToNextLocation(bool bUpdateLocationIndex = true);

	UFUNCTION()
		void FinishCalibration();
};
