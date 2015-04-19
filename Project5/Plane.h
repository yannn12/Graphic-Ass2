#pragma once
#include "Vector3f.h"
#include "Ray.h"
#include "Object.h"

typedef Vector3f Vec;

class Plane : public Object
{
public:

	//distance from the beginnig and a normal to the plane
	Vec  n;
	float d;
	 

	//recives a point and a normal 
	Plane( float d, Vec& n ,Vec& color );   
	//recives a 3 points in space where p0 is the distance of the plane to the origin 
	Plane(Vec& p0, Vec& p1, Vec& p2, Vec& color);
	~Plane();
	virtual float Intersect(Ray& ray);
	virtual Vector3f normal(Vector3f& point);
};

