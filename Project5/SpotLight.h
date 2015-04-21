#pragma once
#include "lightsource.h"
#include "Vector3f.h"
class SpotLight :
	public LightSource
{
public:
	Vector3f Location;
	Vector3f Icolor;
	Vector3f Direction;
	float Angel;
	SpotLight(Vector3f& Location,Vector3f& Direction,Vector3f& Icolor,float RadAngel);
	virtual ~SpotLight(void);
	virtual LightImpact lightImpact(Vector3f point);
};

