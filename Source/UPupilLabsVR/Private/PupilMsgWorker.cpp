// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Chifor Tudor

#include "PupilMsgWorker.h"

PupilMsgWorker* PupilMsgWorker::Instance = nullptr;
/*Global Context Variable for the ZMQ Networking Protocol Library*/
zmq::context_t* ZmqContext;
zmq::socket_t *SubSocket;
std::string Addr = "tcp://127.0.0.1:";//ToDo UObject Options
std::string PupilTopic = u8"gaze"; //TODO Implement Options With UObject

/**
 * \brief Thread which connects and receive data from a certain @PupilTopic from Pupil Serice.
 * Start- and StopListening are all what is needed to use this Thread.
 */
PupilMsgWorker::PupilMsgWorker()
{
	Thread = FRunnableThread::Create(this, TEXT("PupilMsgWorker"), TPri_BelowNormal);
}

PupilMsgWorker::~PupilMsgWorker()
{
	if (Thread != nullptr) {
		Thread->WaitForCompletion();
		delete Thread;
		Thread = nullptr;
	}
}

/**
 * \brief Initializes the context and socket to connect to Pupil Service.
 *	Starts Run() if successful.
 * \return true if the Initialization was  successful
 */
bool PupilMsgWorker::Init()
{	
	UE_LOG(LogTemp, Warning, TEXT("MsgThread>>>>Initialized"));
	zmq::socket_t ReqSocket = ConnectToZmqPupilPublisher("55555");
	SubSocket = ConnectToSubport(std::move(ReqSocket), PupilTopic);

	return true; //TODO BUILD A ERROR BASED LOG. FALSE IF THE INITIALISATION FAILED
}

/**
 * \brief Constantly retrives data from Pupil Service if it has been successfuly initialized & nobody has stopped the Thread.
 * \return A number indicating where it has failed TODO
 */
uint32 PupilMsgWorker::Run()
{
	FPlatformProcess::Sleep(0.03);

	while (IsRunning && IsSuccessfulyInit)
	{
		zmq::message_t topic;
		SubSocket->recv(&topic);
		zmq::message_t info;
		SubSocket->recv(&info);
		GazeStruct ReceivedGazeStruct = ConvertMsgPackToStruct(std::move(info));
		UE_LOG(LogTemp, Warning, TEXT("MsgThread>>>>Loop Ellipse : %f"),ReceivedGazeStruct.base_data.pupil.ellipse.center.x);
	}
	return 1;
}

void PupilMsgWorker::Stop()
{
	Instance->IsRunning = false;
}

void PupilMsgWorker::EnsureCompletion()
{
	Stop();
	Thread->WaitForCompletion();
}

void PupilMsgWorker::Shutdown()
{
	if (Instance)
	{
		Instance->EnsureCompletion();
		delete Instance;
		Instance = nullptr;
	}
}

/**
* \brief This method checks if possible and then starts a Thread and Initializes it.
* The Initialization also starts the Thread by calling the Run() method.
* \return Instance of the object containing the Worker Thread
*/
PupilMsgWorker* PupilMsgWorker::StartListening()
{
	//Create new instance of thread if it does not exist
	//		and the platform supports multi threading!
	if (!Instance && FPlatformProcess::SupportsMultithreading())
	{
		Instance = new PupilMsgWorker();
		Instance->IsSuccessfulyInit = Instance->Init();
		Instance->IsRunning = true;
	}
	return Instance;
}

/**
 * \brief Waits and Stops the Thread in the correct way.
 */
void PupilMsgWorker::StopListening()
{
	if (Thread != nullptr) {
		Instance->Stop();
		Thread->WaitForCompletion();
		delete Thread;
		Thread = nullptr;
	}
}

/**
 * \Function which connects to the ZMQ Socket of the Pupul with a given Addr and Req_Port
 * \param Addr Ip Adress or localhost.
 * \param Reqport Port on which Pupil Capture is configured.
 * \return ReqSocket the afformentioned ZMQ Socket 
 */
zmq::socket_t PupilMsgWorker::ConnectToZmqPupilPublisher(std::string ReqPort) {
	ZmqContext = new zmq::context_t(1);
	std::string ConnAddr = Addr + ReqPort;
	zmq::socket_t ReqSocket(*ZmqContext, ZMQ_REQ);
	ReqSocket.connect(ConnAddr);

	return ReqSocket;
}

/**
 * \brief 
 * \param ReqSocket 
 */
zmq::socket_t* PupilMsgWorker::ConnectToSubport(zmq::socket_t ReqSocket, std::string Topic)
{
	/* Send Request for Sub Port */
	std::string SendSubPort = u8"SUB_PORT";
	zmq::message_t subport_request(8);
	memcpy(subport_request.data(), SendSubPort.c_str(), SendSubPort.length());
	ReqSocket.send(subport_request);
	/* Receive Sub Port */
	zmq::message_t Reply;
	ReqSocket.recv(&Reply);
	std::string  SubportReply = std::string(static_cast<char*>(Reply.data()), Reply.size());
	LogSubPortUE(SubportReply);
	/* SUBSCRIBER SOCKET */
	std::string SubPortAddr = Addr + SubportReply;
	zmq::socket_t* SubSocket = new zmq::socket_t(*ZmqContext, ZMQ_SUB);
	SubSocket->connect(SubPortAddr);
	std::string filter = Topic; 
	SubSocket->setsockopt(ZMQ_SUBSCRIBE, filter.c_str(), filter.length());

	return SubSocket;
}

 void PupilMsgWorker::LogSubPortUE(std::string SubportReply)
{
	FString PortRequest(SubportReply.c_str());
	UE_LOG(LogTemp, Warning, TEXT("ZMQ>>>>Subport : %s"), *PortRequest);
}

GazeStruct PupilMsgWorker::ConvertMsgPackToStruct(zmq::message_t info)
{
	char* payload = static_cast<char*>(info.data());
	msgpack::object_handle oh = msgpack::unpack(payload, info.size());
	msgpack::object deserialized = oh.get();
	GazeStruct ReceivedGazeStruct;
	deserialized.convert(ReceivedGazeStruct);

	return ReceivedGazeStruct;
}