// Copyright under LGPL

#pragma once

#include "CoreMinimal.h"
#include "HAL/Runnable.h"
#include "HAL/RunnableThread.h"
#include "ThreadSafeCounter.h"
#include "MyTestPupilActor.h"


class UPUPILLABSVR_API PupilMessagingWorker : public FRunnable {
	/** Singleton instance, can access the thread any time via static accessor, if it is active! */
	static  PupilMessagingWorker* Runnable;

	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	/** The PC */
	AMyTestPupilActor* ThePC;
	//	void* ThePC;
	/** Stop this thread? Uses Thread Safe Counter */
	FThreadSafeCounter StopTaskCounter;

	//The actual finding of prime numbers
	int32 FindNextPrimeNumber();

private:
	int32	PrimesFoundCount;
public:

	int32	TotalPrimesToFind;

	//Done?
	bool IsFinished() const
	{
		return PrimesFoundCount >= TotalPrimesToFind;
	}

	//~~~ Thread Core Functions ~~~

	//Constructor / Destructor
	PupilMessagingWorker(AMyTestPupilActor *IN_PC);

	virtual ~PupilMessagingWorker();

	// Begin FRunnable interface.
	virtual bool Init();
	virtual uint32 Run();
	virtual void Stop();
	// End FRunnable interface

	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();

	static PupilMessagingWorker* JoyInit(AMyTestPupilActor* IN_PC);


	//~~~ Starting and Stopping Thread ~~~



	/*
	Start the thread and the worker from static (easy access)!
	This code ensures only 1 Prime Number thread will be able to run at a time.
	This function returns a handle to the newly started instance.
	*/

	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

	static bool IsThreadFinished();

};