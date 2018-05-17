// Fill out your copyright notice in the Description page of Project Settings.

#include "PupilCalibrationPawn.h"

#include "Components/SceneComponent.h"
#include "Camera/CameraComponent.h"
#include "Kismet/GameplayStatics.h"
#include "Components/WidgetComponent.h"
#include "HUD/HUDWidget.h"


// Sets default values
APupilCalibrationPawn::APupilCalibrationPawn()
{
 	// Set this pawn to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

	DefaultSceneRoot = CreateDefaultSubobject<USceneComponent>(TEXT("DefaultSceneRoot"));
	RootComponent = DefaultSceneRoot;

	VRWorldAlignedPosition = CreateDefaultSubobject<USceneComponent>(TEXT("VRWorldAlignedPosition"));
	VRWorldAlignedPosition->SetAbsolute(true, true, true);
	VRWorldAlignedPosition->SetupAttachment(RootComponent);

	Camera = CreateDefaultSubobject<UCameraComponent>(TEXT("Camera"));
	Camera->SetupAttachment(VRWorldAlignedPosition);

	HUD = CreateDefaultSubobject<UWidgetComponent>(TEXT("HUD"));
	HUD->SetupAttachment(Camera);
}

// Called when the game starts or when spawned
void APupilCalibrationPawn::BeginPlay()
{
	Super::BeginPlay();
	UGameplayStatics::GetPlayerController(this, 0)->SetViewTarget(this);
}

// Called every frame
void APupilCalibrationPawn::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}

// Called to bind functionality to input
void APupilCalibrationPawn::SetupPlayerInputComponent(UInputComponent* PlayerInputComponent)
{
	Super::SetupPlayerInputComponent(PlayerInputComponent);

}

UHUDWidget* APupilCalibrationPawn::GetHUD()
{
	return Cast<UHUDWidget>(HUD->GetUserWidgetObject());
}

