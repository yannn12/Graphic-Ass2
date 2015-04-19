#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <iostream>
#include <math.h>
 
#include "Display.h"
#include "glut.h"
#include "Camera.h"
#include "Scene.h"
#include "Plane.h"
#include "sphere.h"
#include "NaiveIntersection.h"
#include "Intersection.h"

using namespace std;


Scene scene;
Camera camera;
Vec CamPos(0, 0, 0), Up(0, 1, 0), Forward(0, 0, 1);

const int width = 640, height = 480,dpi =1;

float PlaneDist = 5.0f;
IntersectionEngine *intersectionFinder = new  NaiveIntersection();

void createScene(){

	Sphere* sphere	=new Sphere(Vec (0,0,10), 8, Vec (255,255,255));
	Sphere* sphere2 = new Sphere(Vec(0, 10, 10), 8, Vec(0, 0, 255));
	Plane* floor = new Plane( -1, Vec(0, 1, 0), Vec(90, 60, 30));
	
	


//	scene.objects.push_back(sphere);
	scene.objects.push_back(sphere2);
	//scene.objects.push_back(floor);
}

int main(int  argc, char** argv)
{
	
	GLubyte *pic;
	

	camera = Camera(CamPos, Up, Forward, ViewPlane(width, height, PlaneDist), dpi);

	createScene();
	pic =camera.getPicture(scene, *intersectionFinder);

	Display display(width, height, "RayTracing");
	display.setPicture(pic);
	display.show();
 
	delete intersectionFinder;
	delete pic;
	return 0;
	 

}