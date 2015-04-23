#include "LightImpact.h"




LightImpact::LightImpact(Vector3f* Lcolor,Vector3f* Direction)
{
	this->Lcolor = NULL;
	this->Direction = NULL;
	this->IsHit = false;
	this->IsAmbient = false;

	if(Lcolor!=NULL){
		_Lcolor = *Lcolor;
		this->Lcolor = &_Lcolor;
		this->IsHit = true;
	}
	if(Direction!=NULL){
		_Direction = *Direction;
		this->Direction = &_Direction;
		this->IsAmbient = true;
	}
}



LightImpact::~LightImpact(void)
{

}
