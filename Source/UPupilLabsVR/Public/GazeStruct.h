// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Chifor Tudor

#pragma once

#define   MSGPACK_USE_CPP03
#include "msgpack.hpp"

struct norm_pos {
	float x;
	float y;
	MSGPACK_DEFINE_ARRAY(x, y);
};

struct axes {
	float x;
	float y;
	MSGPACK_DEFINE_ARRAY(x, y);
};

struct center {
	float x;
	float y;
	MSGPACK_DEFINE_ARRAY(x, y);
};

struct ellipse {
	center center;
	axes axes;
	float angle;
	MSGPACK_DEFINE_MAP(center, axes, angle);
};

struct pupil {
	std::string topic;
	float confidence;
	ellipse ellipse;
	float diameter;
	norm_pos norm_pos;
	float timestamp;
	std::string method;
	float id;
	MSGPACK_DEFINE_MAP(topic, confidence, ellipse, diameter, norm_pos, timestamp, method, id);
};

struct base_data {
	pupil pupil;
	MSGPACK_DEFINE_ARRAY(pupil);
};

struct GazeStruct {
	std::string topic;
	norm_pos norm_pos;
	base_data base_data;
	float confidence;
	float id;
	float timestamp;
	MSGPACK_DEFINE_MAP(topic, norm_pos, confidence, id, timestamp, base_data);
};

//Todo move in struct folder

struct DetectionModeStruct
{
	std::string subject;
	std::string mode;
	MSGPACK_DEFINE_MAP(subject, mode);

};

struct EyeStruct
{
	std::string subject;
	int eye_id;
	float delay;
	MSGPACK_DEFINE_MAP(subject, eye_id, delay);

};

struct StartPluginStruct
{
	std::string subject;
	std::string name;
	MSGPACK_DEFINE_MAP(subject, name);
};

struct CalibrationShouldStartStruct
{
	std::string subject;
	float hmd_video_frame_size[2];
	int outlier_threshold;
	float translation_eye0[3]; //Like an FVector
	float translation_eye1[3];
	MSGPACK_DEFINE_MAP(subject, hmd_video_frame_size, outlier_threshold, translation_eye0, translation_eye1);

};

struct CalibrationShouldStopStruct
{
	std::string subject;
	MSGPACK_DEFINE_MAP(subject);

};
/**We use a Vector of structs to represent most values and this is just one element of it*/
struct AddCalibrationReferenceElementStruct
{
	norm_pos norm_pos;
	float timestamp;
	float id;
};

struct AddCalibrationReferenceDataStruct
{
	
};