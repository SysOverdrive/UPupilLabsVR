// Fill out your copyright notice in the Description page of Project Settings.

#include "PupilMessagingWorker.h"
//***********************************************************
//Thread Worker Starts as NULL, prior to being instanced
//		This line is essential! Compiler error without it
PupilMessagingWorker* PupilMessagingWorker::Runnable = nullptr;
//***********************************************************

PupilMessagingWorker::PupilMessagingWorker(AMyTestPupilActor *IN_PC) :ThePC(IN_PC)

{

}

PupilMessagingWorker::~PupilMessagingWorker()
{
	delete Thread;
	Thread = NULL;
}

//Init
bool PupilMessagingWorker::Init()
{

	return true;
}

PupilMessagingWorker* PupilMessagingWorker::JoyInit(AMyTestPupilActor *IN_PC)
{
	//Create new instance of thread if it does not exist
	//		and the platform supports multi threading!
	if (!Runnable && FPlatformProcess::SupportsMultithreading())
	{
		Runnable = new PupilMessagingWorker(IN_PC);
		UE_LOG(LogTemp, Warning, TEXT("ZMQ >>>>THREAD INIT "));
	}
	return Runnable;
}

