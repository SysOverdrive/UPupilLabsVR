// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Chifor Tudor

#pragma once

#include "Runnable.h"
#include "RunnableThread.h"
#include "GenericPlatformProcess.h"
#include "PlatformProcess.h"

#include "DrawDebugHelpers.h"
#include "Engine/Engine.h"
#include "Editor.h"
#include "GameFramework/PlayerController.h"
#include "FPupilLabsUtils.h"

/**
 * Thread which connects and receive data from a certain @PupilTopic from Pupil Serice.
 * Start- and StopListening are all what is needed to use this Thread.
 */
class FPupilMsgWorker : public FRunnable
{
public:
	/**Starts listening to Pupil Service. Static so It can be called also outside of the Thread Context  */
	static FPupilMsgWorker* StartListening();
	/**Stops the Thread and ensures its completion before deleting it*/
	void StopListening();

public:
	DECLARE_EVENT_OneParam(FPupilMsgWorker, DummyEvent, GazeStruct*);
//	DECLARE_EVENT(FPupilMsgWorker, DummyEvent)
	DummyEvent& OnNewData()  { return NewPupilDataEvent; }

private:
	/** Constructor */
	FPupilMsgWorker();
	/** Destructor */
	~FPupilMsgWorker();
	/* Begin FRunnable interface */
	bool Init() override;
	virtual void Stop() override;
	virtual uint32 Run() override;
	/* End FRunnable interface */
	/** Makes sure this thread has stopped properly */
	void EnsureCompletion();
	/** Shuts down the thread. Static so it can easily be called from outside the thread context */
	static void Shutdown();

private:
	/**Static instance variable that ensures the Singleton behavior */
	static FPupilMsgWorker* Instance;
	/** Thread to run the worker FRunnable on */
	FRunnableThread* Thread;

	FPupilLabsUtils PupilHelper; //this is already an instance of the object
	//before the construtor code is called - ie at allocationn

	bool bSuccessfulyInit;

	bool bRunning;

	DummyEvent NewPupilDataEvent;

	GazeStruct ReceivedGazeStructure;
};
