
#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(Vector3f& Direction,Vector3f& Icolor):Direction(-Direction),Icolor(Icolor)
{
	this->Direction.normalize();
}


DirectionalLight::~DirectionalLight(void)
{
}


LightImpact DirectionalLight::lightImpact(Vector3f& point)
{
	 
	
	return LightImpact(Icolor, (Direction));
}