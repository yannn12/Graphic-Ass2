#pragma once
#include "Vector3f.h"
#include "Ray.h"
#include <vector>
#include "glut.h"
#include "Scene.h"
#include "Intersection.h"


class ViewPlane
{
private:


public:

	int width, height; // plane width & height
	float dist; //distance from the camera to the view plane


	ViewPlane(int width, int height, float dist);
	ViewPlane();
	ViewPlane(ViewPlane& p);
	~ViewPlane();
};



class Camera
{
public:	

	Vector3f up, forward, right;
	Vector3f position;
	ViewPlane viewPlane;
	int dpi;

	Camera();
	Camera(Vec& position, Vector3f& up, Vector3f& forward, ViewPlane& viewPlane, int dpi);
	~Camera();

	GLubyte* getPicture(Scene& scene, IntersectionEngine& intersectionFinder);

};
