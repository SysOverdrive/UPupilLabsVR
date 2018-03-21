// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTestPupilActor.h"
#include "UnrealString.h"
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

	
	//zmq_send(nullptr, "SUB_POR", 8, 0);
	//UE_LOG(BobsPlayground, Log, TEXT("%s"), IModule::Get().IsThisNumber42(42) ? TEXT("True") : TEXT("False"));
	
}

// Called every frame
void AMyTestPupilActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
	char localhost[10] = "127.0.0.1"; //For 192.168.1.10 adresses change localhost[15]
	char req_port[6] = "55200";
	char addr[22];
	UE_LOG(LogTemp, Warning, TEXT("ZMQ >>>> Start Actor"));
	strcpy_s(addr, "tcp://");
	strcat_s(addr, localhost);
	strcat_s(addr, ":");
	strcat_s(addr, req_port);
	UE_LOG(LogTemp, Warning, TEXT("ZMQ >>>>Before ZMQ"));
	void *zmq_ctx = zmq_ctx_new();

	UE_LOG(LogTemp, Warning, TEXT("ZMQ >>>>Before Socket"));
	void *requester = zmq_socket(zmq_ctx, ZMQ_REQ);
	zmq_connect(requester, addr);

	zmq_send(requester, "SUB_POR", 8, 0);
	zmq_recv(requester, req_port, 6, 0);

	char buffer[100];

	UE_LOG(LogTemp, Warning, TEXT("ZMQ >>>>Before Socket"));
	zmq_recv(requester, buffer, 100, 0);
	FString response(buffer);
	UE_LOG(LogTemp, Warning, TEXT("ZMQ >>>Pupil data: %s"), *buffer);
		//cout << "Test " << request_nbr << ": " << buffer << endl;
		//string message = "TEST" + buffer;
	
	zmq_close(requester);
	zmq_ctx_destroy(zmq_ctx);

}

