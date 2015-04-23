#pragma once
#include "spotlight.h"
 

class DirectionalLight :
	public LightSource
{
public:
	Vector3f Icolor;
	Vector3f Direction;

	DirectionalLight(Vector3f& Direction,Vector3f& Icolor);
	virtual ~DirectionalLight(void);
	virtual LightImpact lightImpact(Vector3f& point);

};

