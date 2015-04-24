#include "Material.h"



Material::Material(Vec& Ka_, Vec& Kd_, Vec& Ks_, float specularExponent)
{
	Coefficients[Ka] = Ka_;
	Coefficients[Kd] = Kd_;
	Coefficients[Ks] = Ks_;
	this->specularExponent = specularExponent;
}
Material::Material()
{
	Coefficients[Ka] = Vec::zero();
	Coefficients[Kd] = Vec::zero();
	Coefficients[Ks] = Vec::zero();
	this->specularExponent = 1;

}


Material::~Material()
{
}
