// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTestPupilActor.h"


// Sets default values
AMyTestPupilActor::AMyTestPupilActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;

}

// Called when the game starts or when spawned
void AMyTestPupilActor::BeginPlay()
{
	Super::BeginPlay();
	//void *zmq_ctx = zmq_ctx_new();
	//zmq_send(nullptr, "SUB_POR", 8, 0);
	//UE_LOG(BobsPlayground, Log, TEXT("%s"), IModule::Get().IsThisNumber42(42) ? TEXT("True") : TEXT("False"));
}

// Called every frame
void AMyTestPupilActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

}

