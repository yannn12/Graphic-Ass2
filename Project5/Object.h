#pragma once

#include "Vector3f.h"
#include "Line.h"
#include "Ray.h"
 

class Object
{
protected:
	
	
	Vector3f color;

public:

	

	//returns negative number  if there are  no intersactions or the ray is orthogonal
	virtual float Intersect(Ray& ray) = 0;
	// return the normal of an object at a point on the object . Assuming the point is on the object
	virtual Vector3f normal(Vector3f& point) = 0;
	//return the base color vector of the object in the point 
	virtual Vec getColor(Vector3f& point);


};



