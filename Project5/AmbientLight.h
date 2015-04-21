#pragma once
#include "lightsource.h"
class AmbientLight :
	public LightSource
{
public:
	Vector3f Icolor;
	AmbientLight(Vector3f& Icolor);
	~AmbientLight(void);
	virtual LightImpact lightImpact(Vector3f point);
};

