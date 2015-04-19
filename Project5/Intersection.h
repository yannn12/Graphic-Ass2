#pragma once

class Scene;
class Ray;
class Object;


class Intersection
{

	

public:

	float t;
	Object* object;

	Intersection(float param, Object* ob);
	~Intersection();
};


class IntersectionEngine{

public :
	virtual Intersection FindIntersection(Ray& ray, Scene& scene) = 0;
};

