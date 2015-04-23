#include "sphere.h"
#include "Object.h"

Sphere::Sphere(Vec center, float radius, Vec color) : center(center), radius(radius)
{
	this->color = color;
}

Sphere::Sphere(Sphere& s, Vec color) : center(s.center), radius(s.radius)
{
	this->color = color;
}

Sphere::~Sphere()
{}

//returns negative number  if there are  no intersactions or the ray is orthogonal
float Sphere::Intersect(Ray& ray)
{
	Vec po = (ray.p - center);
	


	// a = 1;
	/*float b = 2 * (po *ray.v);
	float c = po*po - radius*radius;

	float diterminata = b*b - 4 * c;

	if (diterminata < 0)
		return -1;

	diterminata = sqrt(diterminata);
	float r1 = (-b - diterminata) / 2;
	float r2 = (-b + diterminata) / 2;
*/
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