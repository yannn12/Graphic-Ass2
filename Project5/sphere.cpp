#include "sphere.h"
#include "Object.h"

Sphere::Sphere(Vec center, float radius, Material& material ) : center(center), radius(radius)
{
	this->material = material;
}

Sphere::Sphere(Sphere& s, Vec color) : center(s.center), radius(s.radius)
{
	  
}

Sphere::~Sphere()
{}

//returns negative number  if there are  no intersactions or the ray is orthogonal
float Sphere::Intersect(Ray& ray)
{
	Vec po = (ray.p - center);
	

	float b = (ray.v*po);
	float c = po*po - radius*radius;
	float determinata = b*b - c;

	if (determinata < 0)
		return -1;
	determinata = sqrt(determinata);
	float r1 = (-b - determinata) ;
	float r2 = (-b + determinata) ;

	

		if (r1<r2 && r1>0) 
		return r1;
 
	return r2; 
}


Vector3f Sphere::normal(Vector3f& point){

	Vector3f n=( point - center);
	n.normalize();
	return  n;

}