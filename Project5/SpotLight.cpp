#include "SpotLight.h"


SpotLight::SpotLight(Vector3f& Location,Vector3f& Direction,Vector3f& Icolor,float RadAngel): Location(Location),Direction(Direction),Icolor(Icolor)
{
	this->Angel = RadAngel;
}


SpotLight::~SpotLight(void)
{
}


LightImpact SpotLight::lightImpact(Vector3f point){

	Vector3f dir = point-Location;
	Direction.normalize();
	dir.normalize();
	float angel = acos( point*dir);
	if(angel>this->Angel){
		LightImpact result( NULL,NULL); // no hit
		return result;
	}

	LightImpact result( &Icolor,&dir); // not mention about distance
	return result;
}