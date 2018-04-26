// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Chifor Tudor

#include "MyTestPupilActor.h"

AMyTestPupilActor::AMyTestPupilActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyTestPupilActor::BeginPlay()
{	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PupilActor>>>>BeginPlay"));
	PupilMessagingListener =FPupilMsgWorker::StartListening();
}
// Called every frame
void AMyTestPupilActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
}
