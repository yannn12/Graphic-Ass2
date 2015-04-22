#pragma once

#include "Vector3f.h"
class LightImpact
{
public:
	Vector3f* Lcolor;
	Vector3f* Direction;
	bool IsHit;	
	bool IsAmbient;
	LightImpact(Vector3f* Lcolor,Vector3f* direction);
	~LightImpact(void);

private:
	Vector3f _Lcolor;
	Vector3f _Direction;
};

