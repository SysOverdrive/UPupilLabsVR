	// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "Camera/CameraComponent.h"
#include "Components/SphereComponent.h"
#include "Components/StaticMeshComponent.h"
#include "Kismet/GameplayStatics.h"

#include "ConstructorHelpers.h"

#include "Engine.h"
#include "APupilLabsVisualMarkersPawn.generated.h"

UCLASS()
class UPUPILLABSVR_API AAPupilLabsVisualMarkersPawn : public APawn
{
	GENERATED_BODY()

public:
	// Sets default values for this pawn's properties
	AAPupilLabsVisualMarkersPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;
	
	//Called To Update A Markers Position
	void UpdatePosition(int CurrentCalibrationPoint);
	//Called To Start The Calibration Process
	void StartCalibration();
	//Used to redraw the spheres in a circle and then give back the relevant reference data
	void RedrawSphere(UWorld* CurrentWorld, int CurrentCalibrationPoint);
	//Sphere Component used to represent a point of focus for the user to gaze on
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spheres")
		USphereComponent* SphereComponent;
	//Sphere Visuals used to better focus the eyes of the user using a dot. //todo
	UPROPERTY(EditAnywhere, BlueprintReadWrite, Category = "Spheres")
		UStaticMeshComponent* SphereVisual;
	int i;//TODO Delete after implementation


	//class USceneComponent* DefaultScene; 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USceneComponent* VRWorldAlignedPosition;
	//Calibration Camera Used 
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UCameraComponent* CalibrationCamera;
	
};
