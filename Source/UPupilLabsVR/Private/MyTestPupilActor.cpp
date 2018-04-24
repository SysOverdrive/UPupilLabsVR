// Fill out your copyright notice in the Description page of Project Settings.

#include "MyTestPupilActor.h"

AMyTestPupilActor::AMyTestPupilActor()
{
 	// Set this actor to call Tick() every frame.  You can turn this off to improve performance if you don't need it.
	PrimaryActorTick.bCanEverTick = true;
}

// Called when the game starts or when spawned
void AMyTestPupilActor::BeginPlay()
{	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("Actor>>>>BeginPlay"));
	Worker = PupilMsgWorkerThread::StartListening();

	//ctx = new zmq::context_t(1);
	//std::string Addr = "tcp://127.0.0.1:";
	//std::string Req_port = "55555";
	//std::string con_addr = Addr + Req_port;

	//zmq::socket_t s(*ctx, ZMQ_REQ);
	//s.connect(con_addr);
	//// Send Request for Sub Port
	//std::string sendSubPort = u8"SUB_PORT";
	//zmq::message_t subport_request(8);
	//memcpy(subport_request.data(), sendSubPort.c_str(), sendSubPort.length());
	//s.send(subport_request);
	////Receive Sub Port
	//zmq::message_t reply;
	//s.recv(&reply);
	////Log Subport
	//std::string  rpl = std::string(static_cast<char*>(reply.data()), reply.size());
	//FString PortRequest(rpl.c_str());
	///// SUBSCRIBER SOCKET
	//std::string subPortAddr = Addr + rpl;
	//subSocket = new zmq::socket_t(*ctx, ZMQ_SUB);
	//subSocket->connect(subPortAddr);
	//std::string filter = u8"gaze";
	////string filter = u8"gaze";
	////string filter = u8"notify";
	////string filter = u8"pupil";
	////string filter = u8"logging";
	//subSocket->setsockopt(ZMQ_SUBSCRIBE, filter.c_str(), filter.length());
}
// Called every frame
void AMyTestPupilActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);
 //   UE_LOG(LogTemp, Warning, TEXT("Actor>>>>Tick"));

	//zmq::message_t topic;
	//subSocket->recv(&topic);
	//std::string  rpl = std::string(static_cast<char*>(topic.data()), topic.size());
	////FString PortRequest(rpl.c_str());

	//zmq::message_t info;
	//subSocket->recv(&info);
	////std::string  rplInfo = std::string(static_cast<char*>(info.data()), info.size()); For Debug
	////FString PortRequestInfo(rplInfo.c_str());

	//char* payload = static_cast<char*>(info.data());
	//msgpack::object_handle oh = msgpack::unpack(payload, info.size());
	//msgpack::object deserialized = oh.get();
	//gaze ReceivedGazeStruct;
	//deserialized.convert(ReceivedGazeStruct);
	//UE_LOG(LogTemp, Warning, TEXT("Struct>>>>Ellipse X: %d", ReceivedGazeStruct.base_data.pupil.ellipse.center.x));
}
//
////Freaky String Stuff
//std::vector<char> bytes(sendSubPort.begin(), sendSubPort.end());
//bytes.push_back('\0');
//char *c = &bytes[0];
////Freaky String Stuff