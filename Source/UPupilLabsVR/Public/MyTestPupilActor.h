// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "Core.h"
#include "GameFramework/Actor.h"
#include "Kismet/GameplayStatics.h"
#include "Engine.h"
#include "FPupilMsgWorker.h"
#include "MyTestPupilActor.generated.h"


UCLASS()
class UPUPILLABSVR_API AMyTestPupilActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTestPupilActor();

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;
	
	///--BEGIN RAYCAST--///
	//Method for receiving the GazeStructure for The RayCasting
	void OnNewPupilData(GazeStruct *GazeStructure);
	void PerformRaycast(UWorld* CurrentWorld);
	//Received Data From The Worker's Event
	GazeStruct *ReceivedGazeStructure;
	///--END RAYCAST--///

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;
	FPupilMsgWorker* PupilComm;
};