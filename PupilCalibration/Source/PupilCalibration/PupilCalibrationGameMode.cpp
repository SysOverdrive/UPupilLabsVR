// Fill out your copyright notice in the Description page of Project Settings.

#include "PupilCalibrationGameMode.h"

#include "Engine/World.h"
#include "FocusActor.h"
#include "Kismet/GameplayStatics.h"
#include "PupilCalibrationPawn.h"
#include "Camera/CameraComponent.h"

void APupilCalibrationGameMode::BeginCalibration(ECalibrationType Calibration_Type)
{
	CalibrationType = Calibration_Type;

	FocusActor = GetWorld()->SpawnActor<AFocusActor>();
	FocusActor->SetScale(FocusScale);
	APupilCalibrationPawn* Pawn = Cast<APupilCalibrationPawn>(UGameplayStatics::GetPlayerPawn(this, 0));
	FocusActor->AttachToComponent(Pawn->Camera, FAttachmentTransformRules::SnapToTargetNotIncludingScale);
	MoveFocusToNextLocation(false);

	FTimerHandle TrackingTimer;
	GetWorld()->GetTimerManager().SetTimer(TrackingTimer, this, &APupilCalibrationGameMode::UpdatePupilTrackingState, UpdatePupilTrackingInterval, true);

	FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &APupilCalibrationGameMode::MoveFocusToNextLocation, true);
	GetWorld()->GetTimerManager().SetTimer(FocusMovementTimer, TimerDelegate, UpdateFocusLocationInterval, true);
}

void APupilCalibrationGameMode::UpdatePupilTrackingState()
{
	//UE_LOG(LogTemp, Warning, TEXT("UpdatePupilTrackingState"));
}

void APupilCalibrationGameMode::UpdatePupilTrackingStateResponse()
{
}

void APupilCalibrationGameMode::OnPupilTrackingStateUpdated(EPupilTrackingState NewTrackingState)
{
	PupilTrackingState = NewTrackingState;
	FocusActor->UpdateMaterial(NewTrackingState);
}

void APupilCalibrationGameMode::MoveFocusToNextLocation(bool bUpdateLocationIndex)
{
	if (bUpdateLocationIndex)
	{
		++CalibrationLocationIndex;
	}

	FVector NewLocation_3D = FVector(0.f);

	switch (CalibrationType)
	{
	case ECalibrationType::_2D:
		if (CalibrationLocations_2D.IsValidIndex(CalibrationLocationIndex))
		{
			FVector2D NewLocation_2D = CalibrationLocations_2D[CalibrationLocationIndex];
			NewLocation_3D = FVector(CalibrationXDistance, NewLocation_2D.X, NewLocation_2D.Y);
		}
		else
		{
			FinishCalibration();
			return;
		}
		break;
	case ECalibrationType::_3D:
		if (CalibrationLocations_3D.IsValidIndex(CalibrationLocationIndex))
		{
			NewLocation_3D = CalibrationLocations_3D[CalibrationLocationIndex];
		}
		else
		{
			FinishCalibration();
			return;
		}
		break;
	}
	UE_LOG(LogTemp, Warning, TEXT("Moved Focus"));
	FocusActor->SetNewLocation(NewLocation_3D);
}

void APupilCalibrationGameMode::FinishCalibration()
{
	GetWorld()->GetTimerManager().ClearTimer(FocusMovementTimer);
	UE_LOG(LogTemp, Warning, TEXT("Calibration Finished"));
}
