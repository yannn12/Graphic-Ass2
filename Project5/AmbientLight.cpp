#include "AmbientLight.h"


AmbientLight::AmbientLight(Vector3f& Icolor):Icolor(Icolor)
{
}


AmbientLight::~AmbientLight(void)
{
}


LightImpact AmbientLight::lightImpact(Vector3f& point)
{
	LightImpact result( &Icolor,NULL);
	return result;
}