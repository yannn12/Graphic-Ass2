#include "Plane.h"


Plane::Plane(float dist, Vec& norm, Vec& color) : d(dist), n(norm)
{
	//normalize values so that the plane eqaution n.p+d=0 becomes n.p / |n|  + d /|n| =0
	float l = n.normalize();
	d = d / l;
	
	this->color = color;
}

Plane::Plane(Vec& p0, Vec& p1, Vec& p2, Vec& color) : n((p1 - p0) ^ (p2 - p0))
{
	
	d = p0 * n;
	float l = n.normalize();
	d = -d / l;
	
	this->color = color;
}


Plane::~Plane()
{}

//returns negative number  if there are  no intersactions or the ray is orthogonal
float Plane::Intersect(Ray& ray)
{
	float dot = (n * ray.v);
	if (dot == 0) // ray is orthogonal
		return -1;
	
	return -(n*ray.p + d) / dot;
}

Vector3f Plane::normal(Vector3f& point){
		
	return n;

}