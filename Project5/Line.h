#pragma once
#include "Vector3f.h"
#include <string>

/*
	Represent a Line p+ v.t were p and v are 3d vectors and t is  a scalar;

*/

typedef Vector3f Vec;
class Line 
{
public:
	// p + t * v
	Vec p, v;

	Line(Vec &_p, Vec &_v);
	Line(const Line& line);
	~Line();

	Vec getPoint(float t);
	float distance(const Line& line);
 
	std::string toString();
	
};

