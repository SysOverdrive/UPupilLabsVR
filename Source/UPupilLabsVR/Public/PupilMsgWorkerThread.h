#pragma once
#include "Runnable.h"
#include "RunnableThread.h"
#include "GenericPlatformProcess.h"
#include "PlatformProcess.h"
#include "LogMacros.h"

#include "GazeStruct.h"

#include "Core.h"

#include "zmq.hpp"
#define   MSGPACK_USE_CPP03
#include "msgpack.hpp"

class PupilMsgWorkerThread : public FRunnable
{
	static PupilMsgWorkerThread* Instance;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;
	/** Makes sure this thread has stopped properly */
	void EnsureCompletion(); //ToDo Implement

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	static bool IsThreadFinished();

	void StopListening();

public:
	PupilMsgWorkerThread();
	~PupilMsgWorkerThread();

	void *zmq_ctx;
	void *requester;
	zmq::context_t *ctx;
	zmq::socket_t *subSocket;

	bool IsSuccessfullyInit;
	bool IsRunning;
	int ControlFlag; //TODO DELETE AFTER DEVELOPMENT

	bool Init() override;
	virtual void Stop();
	virtual uint32 Run();
	static PupilMsgWorkerThread* StartListening();
	
};

