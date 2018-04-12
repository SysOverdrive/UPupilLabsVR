// Fill out your copyright notice in the Description page of Project Settings.

#pragma once

#include "CoreMinimal.h"
#include "GameFramework/Actor.h"
#include "IPluginManager.h"

#include "Core.h"
#include "zmq.hpp"

#include <string>//Todo delete some of this
#include <cstdlib>
#include <fstream>
#include <iostream>
#include <stdlib.h>

#define   MSGPACK_USE_CPP03
#include "msgpack.hpp"

#include "MyTestPupilActor.generated.h"

struct norm_pos {
	double x;
	double y;
	MSGPACK_DEFINE_ARRAY(x, y);
};

struct axes {
	double x;
	double y;
	MSGPACK_DEFINE_ARRAY(x, y);
};

struct center {
	double x;
	double y;
	MSGPACK_DEFINE_ARRAY(x, y);
};

struct ellipse {
	center center;
	axes axes;
	double angle;
	MSGPACK_DEFINE_MAP(center, axes, angle);
};

struct pupil {
	std::string topic;
	double confidence;
	ellipse ellipse;
	double diameter;
	norm_pos norm_pos;
	double timestamp;
	std::string method;
	double id;
	MSGPACK_DEFINE_MAP(topic, confidence, ellipse, diameter, norm_pos, timestamp, method, id);
};

struct base_data {
	pupil pupil;
	MSGPACK_DEFINE_ARRAY(pupil);
};

struct gaze {
	std::string topic;
	norm_pos norm_pos;
	base_data base_data;
	double confidence;
	double id;
	double timestamp;
	MSGPACK_DEFINE_MAP(topic, norm_pos, confidence, id, timestamp, base_data);
};




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

public:	
	// Called every frame
	virtual void Tick(float DeltaTime) override;

	
	
};
