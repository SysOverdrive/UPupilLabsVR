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
<<<<<<< HEAD
{
	Super::BeginPlay();

	ctx = new context_t(1);
	string addr = "tcp://127.0.0.1:";
	string req_port = "55555";
	string con_addr = addr + req_port;

	zmq::socket_t s(*ctx, ZMQ_REQ);
	s.connect(con_addr);
	// Send Request for Sub Port
	string sendSubPort = u8"SUB_PORT";
	zmq::message_t subport_request(8);
	memcpy(subport_request.data(), sendSubPort.c_str(), sendSubPort.length());
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

	PupilMsgWorker::JoyInit(this);
}

// Called every frame
void AMyTestPupilActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime / 100);
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
	//deserialized.convert(rvec);

	int i = 0;
	i++;

	double id;
	id = rvec.id;

	UE_LOG(LogTemp, Warning, TEXT("ZMQ >>>>Ceva "));
	//std::cout << deserialized << std::endl;
=======
{	Super::BeginPlay();
	UE_LOG(LogTemp, Warning, TEXT("PupilActor>>>>BeginPlay"));
	PupilComm = FPupilMsgWorker::StartListening();
	PupilComm->OnNewData().AddUObject(this, &AMyTestPupilActor::OnNewPupilData);


}
// Called every frame
void AMyTestPupilActor::Tick(float DeltaTime)
{
	Super::Tick(DeltaTime);

	FConstCameraActorIterator MyTestCameraIterator = GetWorld()->GetAutoActivateCameraIterator();
	UWorld* CurrentWorld = GetWorld();
	PerformRaycast(CurrentWorld);
}

void AMyTestPupilActor::OnNewPupilData(GazeStruct *GazeStructure)
{
	this->ReceivedGazeStructure = GazeStructure;
	//UE_LOG(LogTemp, Warning, TEXT("[%s][%d]"), TEXT(__FUNCTION__), __LINE__);
	UE_LOG(LogTemp, Warning, TEXT("[%s][%d] Norm Data : %f"), TEXT(__FUNCTION__), __LINE__, this->ReceivedGazeStructure->base_data.pupil.ellipse.center.x);
}

void AMyTestPupilActor::PerformRaycast(UWorld* CurrentWorld)
{
	APlayerController* UPupilPlayerController = UGameplayStatics::GetPlayerController(GetWorld(), 0);
	FVector CameraLocation;
	FRotator CameraRotator;
	int x, y;
	float Confidence;
	//TEST Eye Gazing data
	if(ReceivedGazeStructure!=nullptr){
	x = this->ReceivedGazeStructure->base_data.pupil.norm_pos.x;
	y = this->ReceivedGazeStructure->base_data.pupil.norm_pos.y;
	 Confidence = this->ReceivedGazeStructure->base_data.pupil.confidence;
	}
	//TEST Eye Gazing data
	UPupilPlayerController->GetPlayerViewPoint(CameraLocation, CameraRotator);
	FHitResult* HitResult = new FHitResult(ForceInit);
	const FVector StartTrace = CameraLocation;
	const FVector ForwardVector = CameraRotator.Vector();
	FVector *EndTrace = new FVector();
	*EndTrace = ((ForwardVector *5000.f) + StartTrace);
/*	Experimental
	if (Confidence >= 0.1 && ReceivedGazeStructure != nullptr)
	{
		 EndTrace = new FVector(x, y, 0);
	}
	else {
		EndTrace = new FVector(x, y, 0);

	}*/
	FCollisionQueryParams* TraceParams = new FCollisionQueryParams();

	if(GetWorld()->LineTraceSingleByChannel(*HitResult, StartTrace, *EndTrace, ECC_Visibility, *TraceParams))
	{
		DrawDebugLine(GetWorld(), StartTrace, *EndTrace, FColor(238, 0, 238), true);
		GEngine->AddOnScreenDebugMessage(-1, 5.f, FColor::Red, FString::Printf(TEXT("You hit: %s"), *HitResult->Actor->GetName()));
	}
>>>>>>> e95bee50cd2cfed5145f81d174d611fb29a4aad2
}
