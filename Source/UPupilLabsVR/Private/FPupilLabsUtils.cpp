// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Chifor Tudor

#include "FPupilLabsUtils.h"

FPupilLabsUtils::FPupilLabsUtils()
{
	UE_LOG(LogTemp, Warning, TEXT("FPupilLabsutil>>>>Initialized"));
	zmq::socket_t ReqSocket = ConnectToZmqPupilPublisher(Port);
	SubSocket = ConnectToSubport(std::move(ReqSocket), PupilTopic);
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
zmq::socket_t* FPupilLabsUtils::ConnectToSubport(zmq::socket_t ReqSocket,const std::string Topic)
{
	/* Send Request for Sub Port */
	std::string SendSubPort = u8"SUB_PORT";
	zmq::message_t subport_request(8);
	memcpy(subport_request.data(), SendSubPort.c_str(), SendSubPort.length());
	ReqSocket.send(subport_request);
	/* SUBSCRIBER SOCKET */
	std::string SubPortAddr = Addr + this->ReceiveSubPort(std::move(ReqSocket));
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



std::string FPupilLabsUtils::ReceiveSubPort(zmq::socket_t ReqSocket)
{
	zmq::message_t Reply;
	ReqSocket.recv(&Reply);
	std::string  SubportReply = std::string(static_cast<char*>(Reply.data()), Reply.size());
	LogSubPortUE(SubportReply);

	return SubportReply;
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
	return ReceivedGazeStruct;
}

/**TODO: Delete after the plugin is finished */
GazeStruct FPupilLabsUtils::GetDummyHomeData()
{
	GazeStruct MyDummyStruct = { "gaze.2d",
	{ 50.0, 50.0 },
	{ { "gaze.2d", 0.0,
	{ { 50.0, 50.0 },{ 50.0, 50.0 }, 68.0 }, 40.0,{ 50.0, 50.0 }, 45.0,
		"method:c++2D", 1.0 } }
	};
	return MyDummyStruct;
}

/**This method returns a value from the deepest member of the structure to check if everything is working properly during development
*TODO: Delete after the plugin is finished */
float FPupilLabsUtils::GetDummyElipseData()
{
	zmq::message_t topic;
	SubSocket->recv(&topic);
	zmq::message_t info;
	SubSocket->recv(&info);
	GazeStruct ReceivedGazeStruct = ConvertMsgPackToGazeStruct(std::move(info));

	return ReceivedGazeStruct.base_data.pupil.ellipse.center.x;
}