#include "SpotLight.h"


SpotLight::SpotLight(Vector3f& Location,Vector3f& Direction,Vector3f& Icolor,float RadAngel): Location(Location),Direction(Direction),Icolor(Icolor)
{
	this->Angel = cos(RadAngel);
	Direction.normalize();
}


SpotLight::~SpotLight(void)
{
}


LightImpact SpotLight::lightImpact(Vector3f& point){

	Vector3f ImpactDir = point - Location;
	
	ImpactDir.normalize();
	
	float angel =  ImpactDir*(Direction);
	
	if(angel < this->Angel){
		return LightImpact(); // no hit
		 
	}

	LightImpact result(Icolor, -ImpactDir); // not mention about distance
	return result;
}