#pragma once
#include "Vector3f.h"
#include "Line.h"
 

class Ray :public Line
	
{
public:
	
	Ray(Vec &_p, Vec &_v); 
	~Ray();
	
};

