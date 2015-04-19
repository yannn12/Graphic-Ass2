#pragma once
#include "Vector3f.h"
#include "Ray.h"
#include "Object.h"


typedef Vector3f Vec;

class Sphere : public Object
{
public:

	Vec center;
	float radius;

	Sphere(Vec center, float radius, Vec color);
	Sphere(Sphere& s, Vec color);
	~Sphere();

	float Intersect(Ray& ray);
	Vector3f normal(Vector3f& point);

};

