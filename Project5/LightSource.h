#pragma once
#include "LightImpact.h"
#include "Vector3f.h"
 


class LightSource
{
public:
	LightSource(void);
	virtual ~LightSource(void);
	virtual LightImpact lightImpact(Vector3f& point) = 0;
	 

};

