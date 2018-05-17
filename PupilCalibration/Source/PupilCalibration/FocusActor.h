// Fill out your copyright notice in the Description page of Project Settings.

#pragma once
#include "PupilTrackingStateEnum.h"

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "FocusActor.generated.h"

UCLASS()
class PUPILCALIBRATION_API AFocusActor : public AActor
{
	GENERATED_BODY()
protected:
	UPROPERTY()
		UMaterialInterface* BothTrackingMat;
	UPROPERTY()
		UMaterialInterface* OneTrackingMat;
	UPROPERTY()
		UMaterialInterface* NoneTrackingMat;

public:
	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class USceneComponent* DefaultSceneRoot;

	UPROPERTY(EditAnywhere, BlueprintReadWrite)
		class UStaticMeshComponent* FocusMesh;
	
public:	
	// Sets default values for this actor's properties
	AFocusActor();

public:
	UFUNCTION()
		void UpdateMaterial(EPupilTrackingState CurrentTrackingState);

	UFUNCTION()
		void SetNewLocation(const FVector& NewLocation);

	UFUNCTION()
		void SetScale(const float& Scale);
	
};
