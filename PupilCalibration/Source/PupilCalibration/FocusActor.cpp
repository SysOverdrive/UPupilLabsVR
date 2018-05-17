// Fill out your copyright notice in the Description page of Project Settings.

#include "FocusActor.h"

#include "Components/SceneComponent.h"
#include "Components/StaticMeshComponent.h"
#include "ConstructorHelpers.h"
#include "PupilCalibrationGameMode.h"


// Sets default values
AFocusActor::AFocusActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = false;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	FocusMesh = CreateDefaultSubobject<UStaticMeshComponent>(TEXT("FocusMesh"));
	static ConstructorHelpers::FObjectFinder<UStaticMesh> FocusMeshAsset(TEXT("/Game/PupilCalibration/Meshes/Shape_Sphere.Shape_Sphere"));
	if (FocusMeshAsset.Succeeded())
	{
		FocusMesh->SetStaticMesh(FocusMeshAsset.Object);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find starter content sphere when creating focus actor."));
	}
	FocusMesh->SetupAttachment(RootComponent);

	// Store state change materials.
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> M_BothAsset(TEXT("/Game/PupilCalibration/Materials/M_BothTracking.M_BothTracking"));
	if (M_BothAsset.Succeeded())
	{
		BothTrackingMat = M_BothAsset.Object;
		FocusMesh->SetMaterial(0, BothTrackingMat);
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find focus actor material for both pupils tracking."));
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> M_OneAsset(TEXT("/Game/PupilCalibration/Materials/M_OneTracking.M_OneTracking"));
	if (M_OneAsset.Succeeded())
	{
		OneTrackingMat = M_OneAsset.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find focus actor material for one pupil tracking."));
	}
	static ConstructorHelpers::FObjectFinder<UMaterialInterface> M_NoneAsset(TEXT("/Game/PupilCalibration/Materials/M_NoneTracking.M_NoneTracking"));
	if (M_NoneAsset.Succeeded())
	{
		NoneTrackingMat = M_NoneAsset.Object;
	}
	else
	{
		UE_LOG(LogTemp, Error, TEXT("Could not find focus actor material for neither pupil tracking."));
	}

}

void AFocusActor::UpdateMaterial(EPupilTrackingState CurrentTrackingState)
{
	switch (CurrentTrackingState)
	{
	case EPupilTrackingState::BOTH:
		FocusMesh->SetMaterial(0, BothTrackingMat);
		break;
	case EPupilTrackingState::ONE:
		FocusMesh->SetMaterial(0, OneTrackingMat);
		break;
	case EPupilTrackingState::NONE:
		FocusMesh->SetMaterial(0, NoneTrackingMat);
		break;
	}
}

void AFocusActor::SetNewLocation(const FVector& NewLocation)
{
	FocusMesh->SetRelativeLocation(NewLocation);
	UE_LOG(LogTemp, Warning, TEXT("New Focus Location: %s"), *NewLocation.ToString());
}

void AFocusActor::SetScale(const float& Scale)
{
	FocusMesh->SetWorldScale3D(FVector(Scale));
}
