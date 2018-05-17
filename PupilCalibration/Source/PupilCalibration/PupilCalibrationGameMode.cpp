// Fill out your copyright notice in the Description page of Project Settings.

#include "PupilCalibrationGameMode.h"

#include "Engine/World.h"
#include "FocusActor.h"
#include "Kismet/GameplayStatics.h"
#include "PupilCalibrationPawn.h"
#include "Camera/CameraComponent.h"
#include "HUD/HUDWidget.h"
#include "TimerManager.h"

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

void APupilCalibrationGameMode::BeginPlay()
{
	Super::BeginPlay();
	HUD = Cast<APupilCalibrationPawn>(UGameplayStatics::GetPlayerPawn(this, 0))->GetHUD();
	HUD->SetMessage(FText::FromString("Attempting to connect to the pupil service/capture.\n Please make sure it's running in the background."));
	ConnectToPupilService();
}

void APupilCalibrationGameMode::ConnectToPupilService()
{
	// TODO: Interface with Pupil Backend.
	OnConnectToPupilServiceResponse(bPassConnection);
}

void APupilCalibrationGameMode::OnConnectToPupilServiceResponse(bool bSucceeded)
{
	if (bSucceeded)
	{
		HUD->SetMessage(FText::FromString("Connection to Pupil Successful.\n Press 'C' to start the calibration process."));
		RenderEyeCamera(0);
		RenderEyeCamera(1);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to connect to Pupil Service. Retrying."));
		FTimerHandle th;
		GetWorld()->GetTimerManager().SetTimer(th, this, &APupilCalibrationGameMode::ConnectToPupilService, ConnectionRetryInterval, false);
	}
}

void APupilCalibrationGameMode::UpdatePupilTrackingState()
{
	// TODO: Interface with Pupil Backend.
}

void APupilCalibrationGameMode::UpdatePupilTrackingStateResponse(bool bSucceeded, EPupilTrackingState NewTrackingState)
{
	if (bSucceeded)
	{
		PupilTrackingState = NewTrackingState;
		FocusActor->UpdateMaterial(NewTrackingState);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to update Pupil Tracking State"));
	}
}

void APupilCalibrationGameMode::RenderEyeCamera(uint8 EyeIndex)
{
	// TODO: Interface with Pupil Backend.
	OnRenderEyeCameraResponse(bPassRenderEyes, 0);
	OnRenderEyeCameraResponse(bPassRenderEyes, 1);
}

void APupilCalibrationGameMode::OnRenderEyeCameraResponse(bool bSucceeded, uint8 EyeIndex)
{
	if (bSucceeded)
	{
		FTimerManager& TM = GetWorld()->GetTimerManager();
		if (!TM.IsTimerActive(RenderEyeTimer))
		{
			float UpdateInterval = 1.f / EyeCameraFPS;
			TM.SetTimer(RenderEyeTimer, this, &APupilCalibrationGameMode::UpdateEyeDisplay, UpdateInterval, true);
		}
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to start rendering %s eye camera. Retrying."), EyeIndex == 0 ? *FString("Left") : *FString("Right"));
		FTimerHandle th;
		FTimerDelegate TimerDelegate = FTimerDelegate::CreateUObject(this, &APupilCalibrationGameMode::RenderEyeCamera, EyeIndex);
		GetWorld()->GetTimerManager().SetTimer(th, TimerDelegate, RenderEyeRetryInterval, false);
	}
}

void APupilCalibrationGameMode::UpdateEyeDisplay()
{
	// TODO: Interface with Pupil Backend.

	// TODO: Create default image for eye rendering.
	const uint8* Data = new uint8[200 * 200 * 3];

	OnUpdateEyeDisplayResponse(bPassUpdateEyeDisplay, 0, Data);
	OnUpdateEyeDisplayResponse(bPassUpdateEyeDisplay, 1, Data);
}

void APupilCalibrationGameMode::OnUpdateEyeDisplayResponse(bool bSucceeded, uint8 EyeIndex, const uint8*& Data)
{
	if (bSucceeded)
	{
		// TODO: Don't enable this until the default image is working or it stalls the engine.
		//HUD->UpdateEyeImage(EyeIndex, Data);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Failed to update %s eye display"), EyeIndex == 0 ? *FString("Left") : *FString("Right"));
	}
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
