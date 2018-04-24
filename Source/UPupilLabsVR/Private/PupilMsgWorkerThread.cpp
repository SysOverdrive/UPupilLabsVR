#include "PupilMsgWorkerThread.h"



PupilMsgWorkerThread* PupilMsgWorkerThread::Instance = nullptr;

PupilMsgWorkerThread::PupilMsgWorkerThread()
{
	Thread = FRunnableThread::Create(this, TEXT("PupilMsgWorkerThread"), TPri_BelowNormal);
}


PupilMsgWorkerThread::~PupilMsgWorkerThread()
{
	if (Thread != nullptr) {
		Thread->WaitForCompletion();
		delete Thread;
		Thread = nullptr;
	}
}

bool PupilMsgWorkerThread::Init()
{
	ctx = new zmq::context_t(1);
	std::string Addr = "tcp://127.0.0.1:";
	std::string Req_port = "55555";
	std::string con_addr = Addr + Req_port;

	zmq::socket_t s(*ctx, ZMQ_REQ); //TODO Put in a function
	s.connect(con_addr);
	// Send Request for Sub Port
	std::string sendSubPort = u8"SUB_PORT";
	zmq::message_t subport_request(8);
	memcpy(subport_request.data(), sendSubPort.c_str(), sendSubPort.length());
	s.send(subport_request);
	//Receive Sub Port
	zmq::message_t reply;
	s.recv(&reply);
	//Log Subport
	std::string  rpl = std::string(static_cast<char*>(reply.data()), reply.size());
	FString PortRequest(rpl.c_str());
	/// SUBSCRIBER SOCKET
	std::string subPortAddr = Addr + rpl;
	subSocket = new zmq::socket_t(*ctx, ZMQ_SUB);
	subSocket->connect(subPortAddr);
	std::string filter = u8"gaze";
	//string filter = u8"gaze";
	//string filter = u8"notify";
	//string filter = u8"pupil";
	//string filter = u8"logging";
	subSocket->setsockopt(ZMQ_SUBSCRIBE, filter.c_str(), filter.length());

	return true; //TODO BUILD A ERROR BASED LOG. FALSE IF THE INITIALISATION FAILED
}

uint32 PupilMsgWorkerThread::Run()
{
	FPlatformProcess::Sleep(0.03);

	while (IsRunning && IsSuccessfullyInit)
	{

		zmq::message_t topic;
		subSocket->recv(&topic);
		std::string  rpl = std::string(static_cast<char*>(topic.data()), topic.size());
		//FString PortRequest(rpl.c_str());

		zmq::message_t info;
		subSocket->recv(&info);

		char* payload = static_cast<char*>(info.data());

		msgpack::object_handle oh = msgpack::unpack(payload, info.size());
		msgpack::object deserialized = oh.get();
		gaze ReceivedGazeStruct;
		deserialized.convert(ReceivedGazeStruct);
		UE_LOG(LogTemp, Warning, TEXT("MsgThread>>>>Loop Ellipse : %f"),ReceivedGazeStruct.base_data.pupil.ellipse.center.x);



	}
	return 1;
}

void PupilMsgWorkerThread::Stop()
{
	Instance->IsRunning = false;
}

PupilMsgWorkerThread* PupilMsgWorkerThread::StartListening()
{
	//Create new instance of thread if it does not exist
	//		and the platform supports multi threading!
	if (!Instance && FPlatformProcess::SupportsMultithreading())
	{
		UE_LOG(LogTemp, Warning, TEXT("MsgThread>>>>Initialized"));
		Instance = new PupilMsgWorkerThread();
		Instance->IsSuccessfullyInit = Instance->Init();
		Instance->IsRunning = true;
	}
	return Instance;
}