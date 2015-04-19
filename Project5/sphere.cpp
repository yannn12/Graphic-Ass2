#include "sphere.h"


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
	Vec d = (ray.p - center);
	float l = d.getLength();

	// a = 1;
	float b = d *(ray.v * 2);
	float c = l*l - radius*radius;

	float diterminata = b*b - 4 * c;

	if (diterminata < 0)
		return -1;

	diterminata = sqrt(diterminata);
	float r1 = (-b - diterminata) / 2;
	float r2 = (-b + diterminata) / 2;

	if (r1 > 0)  //r1 is smaller then r2 -always
		return r1;
 
	return r2; //r1 is negative. if  r2 is positive (we are inside the sphere) else it will return negative number- no intersection
}


Vector3f Sphere::normal(Vector3f& point){

	Vector3f n=( point - center);
	n.normalize();
	return  n;

}