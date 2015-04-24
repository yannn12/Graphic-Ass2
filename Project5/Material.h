#pragma once

#include "Vector3f.h"

typedef Vector3f Vec;

class Material
{


private:

	
	
public:

	
	static const int Ka = 0, Kd = 1, Ks = 2;
	Vector3f Coefficients[3];
	int specularExponent;


	Material(Vec& Ka, Vec& Kd, Vec& Ks,int specularExponent);
	Material();
	~Material();
};

