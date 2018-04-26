// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Chifor Tudor

#pragma once

#include "Runnable.h"
#include "RunnableThread.h"
#include "GenericPlatformProcess.h"
#include "PlatformProcess.h"
#include "LogMacros.h"
#include "Core.h"
#include "zmq.hpp"
/**
 * \MSGPACK_USE_CPP03 has been applied to use the CPP03 _t implementations instead of _type.
 *  Any usage of CPP011 calls from msgpack will not work. 
 *  As of now the mvsc compiler does not work with CPP11.
 */
#define   MSGPACK_USE_CPP03
#include "msgpack.hpp"
#include "GazeStruct.h"


class PupilMsgWorker : public FRunnable
{
	static PupilMsgWorker* Instance;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion(); 

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

private:
	bool IsSuccessfulyInit;

	bool IsRunning;

	bool Init() override;

	virtual void Stop();

	virtual uint32 Run();

	zmq::socket_t ConnectToZmqPupilPublisher(std::string ReqPort);

	zmq::socket_t* ConnectToSubport(zmq::socket_t ReqSocket, std::string Topic);

	void LogSubPortUE(std::string SubportReply);

	GazeStruct ConvertMsgPackToStruct(zmq::message_t info);
public:
	PupilMsgWorker();
	~PupilMsgWorker();

	static PupilMsgWorker* StartListening();

	void StopListening();

};
