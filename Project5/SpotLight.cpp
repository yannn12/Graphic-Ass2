#include "SpotLight.h"


SpotLight::SpotLight(Vector3f& Location,Vector3f& Direction,Vector3f& Icolor,float RadAngel): Location(Location),Direction(Direction),Icolor(Icolor)
{
	this->Angel = RadAngel;
}


SpotLight::~SpotLight(void)
{
}


LightImpact SpotLight::lightImpact(Vector3f point){

	Vector3f ImpactDir = point-Location;
	Direction.normalize();
	ImpactDir.normalize();
	float angel = acos( ImpactDir*Direction);
	if(angel>this->Angel){
		LightImpact result( NULL,NULL); // no hit
		return result;
	}

	LightImpact result( &Icolor,&ImpactDir); // not mention about distance
	return result;
}