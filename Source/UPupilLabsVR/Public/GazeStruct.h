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

struct gaze_struct {
	std::string topic;
	norm_pos norm_pos;
	base_data base_data;
	double confidence;
	double id;
	double timestamp;
	MSGPACK_DEFINE_MAP(topic, norm_pos, confidence, id, timestamp, base_data);
};




