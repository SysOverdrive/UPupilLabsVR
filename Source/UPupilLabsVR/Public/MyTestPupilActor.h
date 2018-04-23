// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IPluginManager.h"

#include "Core.h"
#include "zmq.hpp"

#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdlib.h>

#define   MSGPACK_USE_CPP03
#include "msgpack.hpp"

#include "GazeStruct.h"
#include "MyTestPupilActor.generated.h"


UCLASS()
class UPUPILLABSVR_API AMyTestPupilActor : public AActor
{
	GENERATED_BODY()
	
public:	
	// Sets default values for this actor's properties
	AMyTestPupilActor();
	void *zmq_ctx;
	void *requester;
	zmq::context_t *ctx;
	zmq::socket_t *subSocket;

protected:
	// Called when the game starts or when spawned
	virtual void BeginPlay() override;


	/*Calculates prime numbers in the game thread*/
	UFUNCTION(BlueprintCallable, Category = MultiThreading)
		void CalculatePrimeNumbers();

	/*Calculates prime numbers in a background thread*/
	UFUNCTION(BlueprintCallable, Category = MultiThreading)
		void CalculatePrimeNumbersAsync();

	/*The max prime number*/
	UPROPERTY(EditAnywhere, Category = MultiThreading)
		int32 MaxPrime;

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

};
namespace ThreadingTest
{
	static void CalculatePrimeNumbers(int32 UpperLimit)
	{
		//Calculating the prime numbers...
		for (int32 i = 1; i <= UpperLimit; i++)
		{
			bool isPrime = true;

			for (int32 j = 2; j <= i / 2; j++)
			{
				if (FMath::Fmod(i, j) == 0)
				{
					isPrime = false;
					break;
				}
			}

			if (isPrime) GLog->Log("Prime number #" + FString::FromInt(i) + ": " + FString::FromInt(i));
		}
	}

	// Init Function
	//Communicate function
}

/*PrimeCalculateAsyncTask is the name of our task
FNonAbandonableTask is the name of the class I've located from the source code of the engine*/
class PrimeCalculationAsyncTask : public FNonAbandonableTask
{
	int32 MaxPrime;

public:
	/*Default constructor*/
	PrimeCalculationAsyncTask(int32 MaxPrime)
	{
		this->MaxPrime = MaxPrime;
	}

	/*This function is needed from the API of the engine.
	My guess is that it provides necessary information
	about the thread that we occupy and the progress of our task*/
	FORCEINLINE TStatId GetStatId() const
	{
		RETURN_QUICK_DECLARE_CYCLE_STAT(PrimeCalculationAsyncTask, STATGROUP_ThreadPoolAsyncTasks);
	}

	/*This function is executed when we tell our task to execute*/
	void DoWork()
	{
		ThreadingTest::CalculatePrimeNumbers(MaxPrime);

		GLog->Log("--------------------------------------------------------------------");
		GLog->Log("End of prime numbers calculation on background thread");
		GLog->Log("--------------------------------------------------------------------");
	}
};