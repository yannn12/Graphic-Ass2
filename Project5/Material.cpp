#include "Material.h"



Material::Material(Vec& Ka_, Vec& Kd_, Vec& Ks_, int specularExponent)
{
	Coefficients[Ka] = Ka_;
	Coefficients[Kd] = Kd_;
	Coefficients[Ks] = Ks_;
	Coefficients[Kt] = Vec::zero();
	this->specularExponent = specularExponent;
}

Material::Material(Vec& Ka_, Vec& Kd_, Vec& Ks_, Vec& Kr_, int specularExponent){

	Coefficients[Ka] = Ka_;
	Coefficients[Kd] = Kd_;
	Coefficients[Ks] = Ks_;
	Coefficients[Kt] = Kr_;
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
