#pragma once
#include "Vector3f.h"
#include "Ray.h"
#include "Object.h"


typedef Vector3f Vec;

class Plane : public Object
{
public:

	//distance from the beginnig and a normal to the plane
	Vec  n, center;
	float width, length	;
	float d;
	Vec baseW, baseL;  // normal vectors that define the span of the plane
	Vec p1, p2, p3, p4;


	//recives a point and a normal assumes one normal coordiante is 0 and 1 edge of the plane is parallel to  one of the axis
	Plane(Vec& Center, Vec& n ,Vec& color , float width, float length);   
	//recives a 3 points in space where p0 is the distance of the plane to the origin 
	~Plane();
	virtual float Intersect(Ray& ray);
	virtual Vector3f normal(Vector3f& point);
	inline virtual Vec Ka(Vec& pointOfImpact);
	inline virtual Vec Kd(Vec& pointOfImpact);
};

