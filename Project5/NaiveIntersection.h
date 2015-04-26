#pragma once
#include "Intersection.h"


class NaiveIntersection :
	public IntersectionEngine
{

 
public:
	
	Intersection FindIntersection(Ray& ray, Scene& scene, Object* currentObj);
	NaiveIntersection();
	~NaiveIntersection();

};

