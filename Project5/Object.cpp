#include "Object.h"
#include "Material.h"
#include "Const.h"



//return the ambient  color vector of the object in the point 
Vec Object::Ka(Vec& pointOfImpact)
{
	return material.Coefficients[Material::Ka];
}


//return the diffuse coefficient vector of the object in the point 
Vec Object::Kd(Vec& pointOfImpact){
	return material.Coefficients[Material::Kd];
}

//return the specular coefficient vector of the object in the point 
Vec Object::Ks(Vec& pointOfImpact){
	return material.Coefficients[Material::Ks];
}

// return the specular Exponent
int Object::getSpecularExponent(){
	
	return material.specularExponent;
}

