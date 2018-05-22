// Copyright 2018, Institute for Artificial Intelligence - University of Bremen
// Author: Chifor Tudor

#pragma once

#define   MSGPACK_USE_CPP03
#include "msgpack.hpp"

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

struct GazeStruct {
	std::string topic;
	norm_pos norm_pos;
	base_data base_data;
	double confidence;
	double id;
	double timestamp;
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