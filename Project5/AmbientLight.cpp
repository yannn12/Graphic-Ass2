#include "AmbientLight.h"


AmbientLight::AmbientLight(Vector3f& Icolor):Icolor(Icolor)
{
}


AmbientLight::~AmbientLight(void)
{
}


LightImpact AmbientLight::lightImpact(Vector3f& point)
{
	LightImpact result( Icolor, Vector3f(0,0,0) );
	return result;
}