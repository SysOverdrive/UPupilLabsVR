// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTestPupilActor.h"
#include "UnrealString.h"
// Sets default values

using namespace zmq;
using namespace std;


AMyTestPupilActor::AMyTestPupilActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyTestPupilActor::BeginPlay()
{	Super::BeginPlay();

	ctx = new context_t(1);
	string addr = "tcp://127.0.0.1:";
	string req_port = "55555";
	string con_addr = addr + req_port;
	
	zmq::socket_t s(*ctx, ZMQ_REQ);
	s.connect(con_addr);
	// Send Request for Sub Port
	string sendSubPort = u8"SUB_PORT";
	zmq::message_t subport_request(8);
	memcpy(subport_request.data(),sendSubPort.c_str(), sendSubPort.length());
	s.send(subport_request);
	//Receive Sub Port
	zmq::message_t reply;
	s.recv(&reply);
	//Log Subport
	std::string  rpl = std::string(static_cast<char*>(reply.data()), reply.size());
	FString PortRequest(rpl.c_str());
	UE_LOG(LogTemp, Warning, TEXT("ZMQ >>>>Sub Port Respons %s"), *PortRequest);
	/// SUBSCRIBER SOCKET
	string subPortAddr = addr + rpl;
	subSocket = new socket_t(*ctx, ZMQ_SUB);
	subSocket->connect(subPortAddr);

	string filter = u8"gaze";
	//string filter = u8"gaze";
	//string filter = u8"notify";
	//string filter = u8"pupil";
	//string filter = u8"logging";
	subSocket->setsockopt(ZMQ_SUBSCRIBE, filter.c_str(), filter.length());
}
	
// Called every frame
void AMyTestPupilActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime/100);
	zmq::message_t topic;
	subSocket->recv(&topic);
	std::string  rpl = std::string(static_cast<char*>(topic.data()), topic.size());
	FString PortRequest(rpl.c_str());
	UE_LOG(LogTemp, Warning, TEXT("ZMQ >>>>Topic %s"), *PortRequest);

	zmq::message_t info;
	subSocket->recv(&info);
	std::string  rplInfo = std::string(static_cast<char*>(info.data()), info.size());
	FString PortRequestInfo(rplInfo.c_str());
	UE_LOG(LogTemp, Warning, TEXT("ZMQ >>>>Info %s"), *PortRequestInfo);

	char* payload = static_cast<char*>(info.data());

	msgpack::object_handle result;
	result = msgpack::unpack(payload, info.size());
	msgpack::object obj(result.get());

	UE_LOG(LogTemp, Warning, TEXT("ZMQ >>>>Info "));
	msgpack::object_handle oh = msgpack::unpack(payload, info.size());
	msgpack::object deserialized = oh.get();

	gaze rvec;
	deserialized.convert(rvec);

	int i = 0;
	i++;

	double id;
   id = rvec.id;

   UE_LOG(LogTemp, Warning, TEXT("ZMQ >>>>Ceva "));
	//std::cout << deserialized << std::endl;
}
//
////Freaky String Stuff
//std::vector<char> bytes(sendSubPort.begin(), sendSubPort.end());
//bytes.push_back('\0');
//char *c = &bytes[0];
////Freaky String Stuff