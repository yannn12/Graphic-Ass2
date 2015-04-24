#pragma once

#include "Vector3f.h"
class LightImpact
{
public:
	Vector3f Lcolor;
	Vector3f Direction;
	bool IsHit;	
	 
	LightImpact(Vector3f& Lcolor,Vector3f& direction);
	LightImpact(void);
	~LightImpact(void);


 
};

