// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTestPupilActor.h"
#include "UnrealString.h"
// Sets default values
#include "atlstr.h"
#include "msgpack.h"

using namespace std;


AMyTestPupilActor::AMyTestPupilActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
	

}

// Called when the game starts or when spawned
void AMyTestPupilActor::BeginPlay()
{	Super::BeginPlay();
	
}
	
// Called every frame
void AMyTestPupilActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime/100);

	char localhost[10] = "127.0.0.1"; //For 192.168.1.10 adresses change localhost[15]
	char req_port[6] = "55555";
	char addr[22];
	UE_LOG(LogTemp, Warning, TEXT("ZMQ >>>> Start Actor"));
	strcpy_s(addr, "tcp://");
	strcat_s(addr, localhost);
	strcat_s(addr, ":");
	strcat_s(addr, req_port);
	UE_LOG(LogTemp, Warning, TEXT("ZMQ >>>>Before ZMQ"));
	zmq_ctx = zmq_ctx_new();

	UE_LOG(LogTemp, Warning, TEXT("ZMQ >>>>Before Socket"));
	requester = zmq_socket(zmq_ctx, ZMQ_REQ);
	zmq_connect(requester, addr);

	zmq_send(requester, "SUB_POR", 8, 0);
	zmq_recv(requester, req_port, 6, 0);

	zmq_setsockopt(requester, ZMQ_SUBSCRIBE, "", 0);

	//--
	//char *buffer = (char*)malloc(1000 * sizeof(char) + 1);

	char topic[256];
	UE_LOG(LogTemp, Warning, TEXT("ZMQ >>>>Before Receiving"));
	zmq_recv(requester, topic, 256, 0);

	zmq_msg_t  msg;
	zmq_msg_init(&msg);
	int rc = zmq_msg_recv(&msg, socket, 0);


	/*
	string myString(buffer);
	TCHAR shouldRenameTheUsefullVariables[1000]; // = UTF8_TO_TCHAR(buffer);
	_tcscpy(shouldRenameTheUsefullVariables,UTF8_TO_TCHAR(buffer));
	FString response = FString(UTF8_TO_TCHAR(buffer));
	UE_LOG(LogTemp, Warning, TEXT("ZMQ >>>Pupil data: %s"), *response);
	//cout << "Test " << request_nbr << ": " << buffer << endl;
	//string message = "TEST" + buffer;
//	GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Blue, TestHUDString);
*/
	zmq_close(requester);
	zmq_ctx_destroy(zmq_ctx);

}
//
//void AMyTestPupilActor::EndPlay(const EEndPlayReason::Type EndPlayReason){
//
//
//	zmq_close(requester);
//	zmq_ctx_destroy(zmq_ctx);
//	Super::EndPlay(EndPlayReason);
//}
//
