#pragma once

#include "Vector3f.h"
#include "Line.h"
#include "Ray.h"
#include "Material.h"
#include "Scene.h"
#include "Intersection.h"

class Object
{
protected:
	
	Vector3f color;
	


public:

	
	Material material;

	//returns negative number  if there are  no intersactions or the ray is orthogonal
	virtual float Intersect(Ray& ray) = 0;
	// return the normal of an object at a point on the object . Assuming the point is on the object
	virtual Vector3f normal(Vector3f& point) = 0;
	
	//return the ambient  color vector of the object in the point 
	virtual  Vec Ka(Vec& pointOfImpact);
	
	//return the diffuse coefficient vector of the object in the point 
	 virtual  Vec Kd(Vec& pointOfImpact);

	//return the specular coefficient vector of the object in the point 
	 virtual  Vec Ks(Vec& pointOfImpact);

	 // return the specular Exponent
	 virtual int getSpecularExponent();


};



