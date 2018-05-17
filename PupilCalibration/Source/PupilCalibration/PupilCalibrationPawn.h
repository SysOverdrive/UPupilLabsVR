// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Pawn.h"
#include "PupilCalibrationPawn.generated.h"

UCLASS()
class PUPILCALIBRATION_API APupilCalibrationPawn : public APawn
{
	GENERATED_BODY()
public:
	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class USceneComponent* VRWorldAlignedPosition;

	UPROPERTY(EditAnywhere, BlueprintReadOnly)
		class UCameraComponent* Camera;

public:
	// Sets default values for this pawn's properties
	APupilCalibrationPawn();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	// Called to bind functionality to input
	virtual void SetupPlayerInputComponent(class UInputComponent* PlayerInputComponent) override;

	
	
};
