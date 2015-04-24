#include "LightImpact.h"




LightImpact::LightImpact(Vector3f& Lcolor,Vector3f& Direction)
{
	 
		//_Lcolor = Lcolor;
		this->Lcolor = Lcolor;
		this->IsHit = true;
	 
		//_Direction = Direction;
		this->Direction = Direction;
		this->IsAmbient = true;
	
}


LightImpact::LightImpact(void)
{
	this->IsHit = false;
	this->Lcolor = Vector3f::zero();
	this->Direction = Vector3f::zero();
}

LightImpact::~LightImpact(void)
{

}
