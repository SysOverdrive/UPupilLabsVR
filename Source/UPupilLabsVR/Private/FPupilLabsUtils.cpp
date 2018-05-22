// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Chifor Tudor

#include "FPupilLabsUtils.h"

FPupilLabsUtils::FPupilLabsUtils()
{//Todo AndreiQ : De ce se cheama de doua ori ? M-am uitat prin cod si nu pare logic? Sa il fac singleton
	UE_LOG(LogTemp, Warning, TEXT("FPupilLabsutil>>>>Initialized"));
	zmq::socket_t ReqSocket = ConnectToZmqPupilPublisher(Port);
	SubSocket = ConnectToSubport(&ReqSocket, PupilTopic);
	SynchronizePupilServiceTimestamp();
	StartHMDPlugin(&ReqSocket); //TODO METODA GENERICA PENTRU ASTEA 3 CU PARAMS REQSOCKET SI GENERIC STRUCT 
	CalibrationShouldStart(&ReqSocket);
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
	zmq::message_t subport_request(SendSubPort.size());
	memcpy(subport_request.data(), SendSubPort.c_str(), SendSubPort.length());
	ReqSocket->send(subport_request);
	/* SUBSCRIBER SOCKET */
	std::string SubPortAddr = Addr + ReceiveSubPort(ReqSocket);
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

void FPupilLabsUtils::CloseSubSocket()
{
	SubSocket->close();
}

void FPupilLabsUtils::LogSubPortUE(std::string SubportReply)
{
	FString PortRequest(SubportReply.c_str());
	UE_LOG(LogTemp, Warning, TEXT("ZMQ>>>>Reply : %s"), *PortRequest);
}

/**Todo Must be placed at the start of the Calibration*/
void FPupilLabsUtils::SynchronizePupilServiceTimestamp()
{
	//This is a different Socket such that it does not interfere with the other sockets //TODO Ask andrei if this is the best approuch
	zmq::socket_t TimeReqSocket = ConnectToZmqPupilPublisher(Port);
	
	float CurrentUETimestamp = FPlatformTime::Seconds();
	std::string SendCurrentUETimeStamp = u8"T " + std::to_string(CurrentUETimestamp);
	FString SendTimestamp(SendCurrentUETimeStamp.c_str());
	UE_LOG(LogTemp, Warning, TEXT("Current TimeStamp %s "), *SendTimestamp);

	zmq::message_t TimestampSendRequest(SendCurrentUETimeStamp.length());
	memcpy(TimestampSendRequest.data(), SendCurrentUETimeStamp.c_str(), SendCurrentUETimeStamp.length());
	TimeReqSocket.send(TimestampSendRequest);
	//We always have to receive the data so it is non blocking
	zmq::message_t Reply;
	TimeReqSocket.recv(&Reply);
	std::string  TimeStampReply = std::string(static_cast<char*>(Reply.data()), Reply.size());
	LogSubPortUE(TimeStampReply); //ToDo delete after implementation
	TimeReqSocket.close();

}

GazeStruct FPupilLabsUtils::GetGazeStructure()
{
	zmq::message_t topic;
	SubSocket->recv(&topic);
	zmq::message_t info;
	SubSocket->recv(&info);
	GazeStruct ReceivedGazeStruct = ConvertMsgPackToGazeStruct(std::move(info));

	return ReceivedGazeStruct;
}


void FPupilLabsUtils::InitializeCalibration(zmq::socket_t *ReqSocket)
{
	//TODO
	/*SubscribeTo("notify.calibration.successful");
	SubscribeTo("notify.calibration.failed");
	SubscribeTo("pupil.");*/

}

void FPupilLabsUtils::UpdateCalibration()
{
	
}

void FPupilLabsUtils::StartHMDPlugin(zmq::socket_t *ReqSocket)
{
	///DATA MARSHELLING
	StartPluginStruct StartPluginStruct = { u8"start_plugin" , PupilPluginName };
	std::string FirstBuffer = "notify." + StartPluginStruct.subject;

	zmq::message_t FirstFrame(FirstBuffer.size());
	memcpy(FirstFrame.data(), FirstBuffer.c_str(), FirstBuffer.size());

	msgpack::sbuffer SecondBuf;
	msgpack::pack(SecondBuf, StartPluginStruct);
	zmq::message_t SecondFrame(SecondBuf.size());
	memcpy(SecondFrame.data(), SecondBuf.data(), SecondBuf.size());
	//DATA SENDING
	zmq::multipart_t multipart;

	multipart.add(std::move(FirstFrame));
	multipart.add(std::move(SecondFrame));
	multipart.send(*ReqSocket);

	zmq::message_t Reply;
	ReqSocket->recv(&Reply);

	std::string  HMDPluginReply = std::string(static_cast<char*>(Reply.data()), Reply.size());
	LogSubPortUE(HMDPluginReply); //ToDo delete after implementation
}

void FPupilLabsUtils::CalibrationShouldStart(zmq::socket_t* ReqSocket)
{
	///DATA MARSHELLING
	CalibrationShouldStartStruct ShouldStartStruct = { "calibration.should_start", {1200, 1200}, 35, {0,0,0}, {0,0,0} };
	std::string FirstBuffer = "notify." + ShouldStartStruct.subject;

	zmq::message_t FirstFrame(FirstBuffer.size());
	memcpy(FirstFrame.data(), FirstBuffer.c_str(), FirstBuffer.size());

	msgpack::sbuffer SecondBuf;
	msgpack::pack(SecondBuf, ShouldStartStruct);
	zmq::message_t SecondFrame(SecondBuf.size());
	memcpy(SecondFrame.data(), SecondBuf.data(), SecondBuf.size());
	//DATA SENDING
	zmq::multipart_t multipart;

	multipart.add(std::move(FirstFrame));
	multipart.add(std::move(SecondFrame));
	multipart.send(*ReqSocket);

	zmq::message_t Reply;
	ReqSocket->recv(&Reply);

	std::string  HMDPluginReply = std::string(static_cast<char*>(Reply.data()), Reply.size());
	LogSubPortUE(HMDPluginReply); //ToDo delete after implementation
}

bool FPupilLabsUtils::SetDetectionMode(zmq::socket_t *ReqSocket)
{
	DetectionModeStruct DetectStruct = { u8"set_detection_mapping_mode" , u8"2d" };
	std::string FirstBuffer ="notify." + DetectStruct.subject;

	zmq::message_t FirstFrame(FirstBuffer.size());
	memcpy(FirstFrame.data(), FirstBuffer.c_str(), FirstBuffer.size());
	
	msgpack::sbuffer SecondBuf;
	msgpack::pack(SecondBuf, DetectStruct);
	zmq::message_t SecondFrame(SecondBuf.size());
	memcpy(SecondFrame.data(), SecondBuf.data(), SecondBuf.size());
	//DATA SENDING
	zmq::multipart_t multipart;

	multipart.add(std::move(FirstFrame));
	multipart.add(std::move(SecondFrame));

	multipart.send(*ReqSocket);

	zmq::message_t Reply;
	ReqSocket->recv(&Reply);

	std::string  Notification2DReply = std::string(static_cast<char*>(Reply.data()), Reply.size());
	LogSubPortUE(Notification2DReply); //ToDo delete after implementation
	return true;
}


bool FPupilLabsUtils::StartEyeProcesses(zmq::socket_t *ReqSocket)
{
	StartEyeNotification(ReqSocket, "0");
	StartEyeNotification(ReqSocket, "1");

	return true;
}


void FPupilLabsUtils::StartEyeNotification(zmq::socket_t* ReqSocket, std::string EyeId)
{
	std::string Subject = "eye_process.should_start." + EyeId;
	
	EyeStruct EyeStruct = { Subject, atoi(EyeId.c_str()), 0.1};
	//zmq::socket_t* EyeSocket = new zmq::socket_t(*ZmqContext, ZMQ_PUB);
	zmq::socket_t EyeSocket = ConnectToZmqPupilPublisher(Port);
	std::string FirstBuffer ="notify." + Subject;

	zmq::message_t FirstFrame(FirstBuffer.size());
	memcpy(FirstFrame.data(), FirstBuffer.c_str(), FirstBuffer.size());

	msgpack::sbuffer SecondBuf;
	msgpack::pack(SecondBuf, EyeStruct);
	zmq::message_t SecondFrame(SecondBuf.size());
	memcpy(SecondFrame.data(), SecondBuf.data(), SecondBuf.size());
	//DATA SENDING
	zmq::multipart_t multipart;
	multipart.add(std::move(FirstFrame));
	multipart.add(std::move(SecondFrame));

	multipart.send(*ReqSocket);

	zmq::message_t Reply;
	ReqSocket->recv(&Reply);

	std::string  Notification2DReply = std::string(static_cast<char*>(Reply.data()), Reply.size());
	LogSubPortUE(Notification2DReply);
}