#include "Material.h"



Material::Material(Vec& Ka_, Vec& Kd_, Vec& Ks_)
{
	Coefficients[Ka] = Ka_;
	Coefficients[Kd] = Kd_;
	Coefficients[Ks] = Ks_;
}
Material::Material()
{
	Coefficients[Ka] = Vec::zero();
	Coefficients[Kd] = Vec::zero();
	Coefficients[Ks] = Vec::zero();
}


Material::~Material()
{
}
