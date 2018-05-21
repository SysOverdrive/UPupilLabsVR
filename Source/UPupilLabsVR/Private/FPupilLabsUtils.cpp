// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Chifor Tudor

#include "FPupilLabsUtils.h"

FPupilLabsUtils::FPupilLabsUtils()
{
	UE_LOG(LogTemp, Warning, TEXT("FPupilLabsutil>>>>Initialized"));
	zmq::socket_t ReqSocket = ConnectToZmqPupilPublisher(Port);
	SubSocket = ConnectToSubport(&ReqSocket, PupilTopic);
	SynchronizePupilServiceTimestamp();
	SetDetectionMode(&ReqSocket);
	StartEyeProcesses(&ReqSocket);
	//Todo Close All Sockets within an ArrayList of Sockets
	ReqSocket.close();
}

FPupilLabsUtils::~FPupilLabsUtils()
{
	ZmqContext = nullptr;
	SubSocket = nullptr;
}


/**
* \Function which connects to the ZMQ Socket of the Pupul with a given Addr and Req_Port
* \param Addr Ip Adress or localhost.
* \param Reqport Port on which Pupil Capture is configured.
* \return ReqSocket the afformentioned ZMQ Socket
*/
zmq::socket_t FPupilLabsUtils::ConnectToZmqPupilPublisher(const std::string ReqPort) {
	ZmqContext = new zmq::context_t(1);
	std::string ConnAddr = Addr + ReqPort;
	zmq::socket_t ReqSocket(*ZmqContext, ZMQ_REQ);
	ReqSocket.connect(ConnAddr);

	return ReqSocket; //Todo Return Error Flag
}

/**
* \brief Takes the current Req Socket and request a subport on which it opens a connection to Pupil Service by binding a SubSocket 
* \param ReqSocket
*/
zmq::socket_t* FPupilLabsUtils::ConnectToSubport(zmq::socket_t *ReqSocket,const std::string Topic)
{
	/* Send Request for Sub Port */
	std::string SendSubPort = u8"SUB_PORT";
	zmq::message_t subport_request(8);
	memcpy(subport_request.data(), SendSubPort.c_str(), SendSubPort.length());
	ReqSocket->send(subport_request);
	/* SUBSCRIBER SOCKET */
	std::string SubPortAddr = Addr + this->ReceiveSubPort(ReqSocket);
	zmq::socket_t* SubSocket = new zmq::socket_t(*ZmqContext, ZMQ_SUB);
	SubSocket->connect(SubPortAddr);
	SubSocket->setsockopt(ZMQ_SUBSCRIBE, Topic.c_str(), Topic.length());


	return SubSocket;
}

GazeStruct FPupilLabsUtils::ConvertMsgPackToGazeStruct(zmq::message_t info)
{
	char* payload = static_cast<char*>(info.data());
	msgpack::object_handle oh = msgpack::unpack(payload, info.size());
	msgpack::object deserialized = oh.get();
	GazeStruct ReceivedGazeStruct;
	deserialized.convert(ReceivedGazeStruct);

	return ReceivedGazeStruct;
}

std::string FPupilLabsUtils::ReceiveSubPort(zmq::socket_t *ReqSocket)
{
	zmq::message_t Reply;
	ReqSocket->recv(&Reply);
	std::string  SubportReply = std::string(static_cast<char*>(Reply.data()), Reply.size());
	LogSubPortUE(SubportReply);

	return SubportReply;
}
/**Todo Must be placed at the start of the Calibration*/
void FPupilLabsUtils::SynchronizePupilServiceTimestamp()
{
	//This is a different Socket such that it does not interfere with the other sockets //TODO Ask andrei if this is the best approuch
	zmq::socket_t TimeReqSocket = ConnectToZmqPupilPublisher(Port);
	
	float CurrentUETimestamp = FPlatformTime::Seconds();
	FString TheFloatStr = FString::SanitizeFloat(CurrentUETimestamp);
	std::string SendCurrentUETimeStamp = u8"T " + std::to_string(CurrentUETimestamp);
	FString SendTimestamp(SendCurrentUETimeStamp.c_str());
	UE_LOG(LogTemp, Warning, TEXT("Current TimeStamp %s "), *SendTimestamp);

	zmq::message_t subport_request(17);
	memcpy(subport_request.data(), SendCurrentUETimeStamp.c_str(), SendCurrentUETimeStamp.length());
	TimeReqSocket.send(subport_request);
	//We always have to receive the data so it is non blocking
	zmq::message_t Reply;
	TimeReqSocket.recv(&Reply);
	std::string  TimeStampReply = std::string(static_cast<char*>(Reply.data()), Reply.size());
	LogSubPortUE(TimeStampReply); //ToDo delete after implementation
	TimeReqSocket.close();

}

void FPupilLabsUtils::LogSubPortUE(std::string SubportReply)
{
	FString PortRequest(SubportReply.c_str());
	UE_LOG(LogTemp, Warning, TEXT("ZMQ>>>>Subport : %s"), *PortRequest);
}

GazeStruct FPupilLabsUtils::GetGazeStructure()
{
	
	zmq::message_t topic;
	SubSocket->recv(&topic);
	zmq::message_t info;
	SubSocket->recv(&info);
	GazeStruct ReceivedGazeStruct = ConvertMsgPackToGazeStruct(std::move(info));

//	double x = ReceivedGazeStruct.base_data.pupil.norm_pos.x;
//	double y = ReceivedGazeStruct.base_data.pupil.norm_pos.y;
//	UE_LOG(LogTemp, Warning, TEXT("[%s][%d]XXXXXXX : %f"), TEXT(__FUNCTION__), __LINE__, x);
//	UE_LOG(LogTemp, Warning, TEXT("[%s][%d]YYYYYYY : %f"), TEXT(__FUNCTION__), __LINE__, y);

	return ReceivedGazeStruct;
}

void FPupilLabsUtils::CloseSubSocket()
{
	SubSocket->close();
}

void FPupilLabsUtils::InitializeCalibration(zmq::socket_t *ReqSocket)
{
	//Todo move in Calibration class
	UE_LOG(LogTemp, Warning, TEXT("[%s][%d]Calibration initialized"), TEXT(__FUNCTION__), __LINE__);
	//Calibration Variables
	//If no sphere initilize it
	UE_LOG(LogTemp, Warning, TEXT("[%s][%d]Calibration started"), TEXT(__FUNCTION__), __LINE__);

	//Todo send start eye process
	//Todo send plugin 
	//2D Mode Move From Here
	zmq::socket_t* Sub2DSocket = new zmq::socket_t(*ZmqContext, ZMQ_PUB);




	std::string SendSubPort = u8"SUB_PORT";
	zmq::message_t subport_request(8);
	memcpy(subport_request.data(), SendSubPort.c_str(), SendSubPort.length());
	ReqSocket->send(subport_request);

	std::string SubPort2DAddr = Addr + this->ReceiveSubPort(ReqSocket);

	Sub2DSocket->connect(SubPort2DAddr);

	EyeStruct EyeStruct = { "notify.eye_process.should_start.0",1 };

	msgpack::sbuffer sbuf;
	msgpack::pack(sbuf, EyeStruct);

	std::string SendDetectionString = u8"notify.set_detection_mapping_mode";
	zmq::message_t topic(34);
	//memcpy(topic.data(), sbuf, SendDetectionString.length());
	Sub2DSocket->send(topic, ZMQ_SNDMORE);

	std::string SendDetectionStringMethod = u8"2d";
	zmq::message_t subject(27);
	memcpy(subject.data(), SendDetectionString.c_str(), SendDetectionString.length());
	bool BSendCalibrationMode = Sub2DSocket->send(subject, 0);

}

void FPupilLabsUtils::UpdateCalibration()
{

}

bool FPupilLabsUtils::SetDetectionMode(zmq::socket_t *ReqSocket)
{
	//2D Mode Move From Here
	zmq::socket_t* Sub2DSocket = new zmq::socket_t(*ZmqContext, ZMQ_PUB);


	std::string SendSubPort = u8"SUB_PORT";
	zmq::message_t subport_request(8);
	memcpy(subport_request.data(), SendSubPort.c_str(), SendSubPort.length());
	ReqSocket->send(subport_request);

	std::string SubPort2DAddr = Addr + this->ReceiveSubPort(ReqSocket);

	Sub2DSocket->connect(SubPort2DAddr);

	DetectionModeStruct DetectStruct = { u8"notify.set_detection_mapping_mode" , u8"2d" };
	//msgpack::sbuffer FirstBuffer;
	//msgpack::pack(FirstBuffer, DetectStruct.subject);
	std::string FirstBuffer = DetectStruct.subject;

	zmq::message_t FirstFrame(FirstBuffer.size());

	memcpy(FirstFrame.data(), FirstBuffer.data(), FirstBuffer.size());
	//Sub2DSocket->send(FirstFrame, ZMQ_SNDMORE);
	

	msgpack::sbuffer SecondBuf;

	msgpack::pack(SecondBuf, DetectStruct.mode);

	zmq::message_t SecondFrame(SecondBuf.size());
	memcpy(SecondFrame.data(), SecondBuf.data(), SecondBuf.size());

	zmq::multipart_t multipart;

	multipart.add(std::move(FirstFrame));
	multipart.add(std::move(SecondFrame));

	multipart.send(*Sub2DSocket);

	//zmq::message_t Reply;
	//Sub2DSocket->recv(&Reply);

	//bool BSendCalibrationMode = Sub2DSocket->send(SecondFrame, 0);


	return true;

}


bool FPupilLabsUtils::StartEyeProcesses(zmq::socket_t *ReqSocket)
{
	PackStartEyeNotification(ReqSocket, 0);
	return true;
}


void FPupilLabsUtils::PackStartEyeNotification(zmq::socket_t *ReqSocket, int EyeId)
{
	EyeStruct EyeStruct = { "notify.eye_process.should_start.0",  EyeId, 0.1};
	zmq::socket_t* EyeSocket = new zmq::socket_t(*ZmqContext, ZMQ_PUB);

	//CONNECTION
	std::string SendSubPort = u8"SUB_PORT";
	zmq::message_t subport_request(8);
	memcpy(subport_request.data(), SendSubPort.c_str(), SendSubPort.length());
	ReqSocket->send(subport_request);

	std::string SubPortAddr = Addr + this->ReceiveSubPort(ReqSocket);

	EyeSocket->connect(SubPortAddr);

	//msgpack::sbuffer FirstBuffer;
	//msgpack::pack(FirstBuffer, EyeStruct.subject);
	std::string FirstBuffer = EyeStruct.subject;

	zmq::message_t FirstFrame(FirstBuffer.size());
	memcpy(FirstFrame.data(), FirstBuffer.data(), FirstBuffer.size());
	//->send(FirstFrame,ZMQ_SNDMORE);
	///2
	msgpack::sbuffer SecondBuf;

	msgpack::pack(SecondBuf, EyeStruct.id);

	zmq::message_t SecondFrame(SecondBuf.size());
	memcpy(SecondFrame.data(), SecondBuf.data(), SecondBuf.size());
	//EyeSocket->send(SecondFrame, ZMQ_SNDMORE);
	///3
	msgpack::sbuffer ThirdBuf;

	msgpack::pack(ThirdBuf, EyeStruct.delay);

	zmq::message_t ThirdFrame(ThirdBuf.size());
	memcpy(ThirdFrame.data(), ThirdBuf.data(), ThirdBuf.size());
	//EyeSocket->send(SecondFrame, 0);

	zmq::multipart_t multipart;

	multipart.add(std::move(FirstFrame));
	multipart.add(std::move(SecondFrame));

	multipart.send(*EyeSocket);

	//zmq::message_t Reply;
	//EyeSocket->recv(&Reply);

	//char* payload = static_cast<char*>(Reply.data());
	//msgpack::object_handle oh = msgpack::unpack(payload, Reply.size());
	//msgpack::object deserialized = oh.get();
}