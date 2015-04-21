#include "DirectionalLight.h"


DirectionalLight::DirectionalLight(Vector3f& Direction,Vector3f& Icolor):Direction(Direction),Icolor(Icolor)
{

}


DirectionalLight::~DirectionalLight(void)
{
}


LightImpact DirectionalLight::lightImpact(Vector3f point){
	LightImpact result( &Icolor,&Direction);
	return result;
}