// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Chifor Tudor

#pragma once

#include "Core.h"
#include "LogMacros.h"
#include "zmq.hpp"
/**
* \MSGPACK_USE_CPP03 has been applied to use the CPP03 _t implementations instead of _type.
*  Any usage of CPP011 calls from msgpack will not work.
*  As of now the mvsc compiler does not work with CPP11.
*/
#define   MSGPACK_USE_CPP03
#include "msgpack.hpp"
#include "GazeStruct.h"

// 
/**
 * \brief A class to wrap all the communication done with the help of ZeroMQ and Msgpack 
 *	ZeroMq is a networking protocol whilst msgpack an encoding format used by the client from Pupil Service for maximum communication speed. You can think of msgpack as a JSON format but send in binary Instead of Human Readeble Format
 *	Also Other Strucs and values can be accessed from the this Helper class like :
 *	gaze
 *	notify
 *	pupil
 *	logging
 *	By changing the Topic filter (Upcomming feature)
 */
class FPupilLabsUtils
{
public:
	/** Constructor. Initializes the Zmq Context and Req Sockect*/
	FPupilLabsUtils();
	/** Destructor */
	~FPupilLabsUtils();
	/**Public Method accesible by the Worker Thread such that we can always do a sanity check*/
	float GetDummyElipseData();

private:
	/**Method that starts connecting to the Response Socket of the Pupil Service using a Request Socket */
	zmq::socket_t ConnectToZmqPupilPublisher(std::string ReqPort);
	/**Method that connects to the Subport of the Publisher given from the Request Socket*/
	zmq::socket_t* ConnectToSubport(zmq::socket_t ReqSocket, std::string Topic);
	/**Method that receives and logs the SubPort */
	std::string ReceiveSubPort(zmq::socket_t ReqSocket);
	 /**Helper Method that logs the SubPort */
	 void LogSubPortUE(std::string SubportReply);
	/**Helper Method that converts the binary message into a C structure using msgpack*/
	 GazeStruct ConvertMsgPackToGazeStruct(zmq::message_t info);


private:
	 /**Context for Zmq to rely on*/
	zmq::context_t* ZmqContext;
	/**Subsocket on which the Zmq Request Socket Subscribes*/
	zmq::socket_t *SubSocket;
	/**Begin Hardcoded strings that define the connection and type of Subscription */
	std::string Addr = "tcp://127.0.0.1:";//TODO UPROPERTY Options
	std::string Port = "55555";
	std::string PupilTopic = u8"gaze"; //TODO Implement Options With UObject
	/**End Hardcoded strings that define the connection and type of Subscription */
};

