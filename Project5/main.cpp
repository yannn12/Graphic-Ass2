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
#include "DirectionalLight.h"

using namespace std;



IntersectionEngine *intersectionFinder;
Scene* scene;
Camera camera;
int width = 512, height = 512;
//Vec CamPos(0, 0, 0), Up(0, 1, 0), Forward(0, 0, 1);
//
//const int width = 320, height = 240,dpi =1;
//
//float PlaneDist = 30.0f;


void createScene(){

	Vec CamPos(0, 0, 0), Up(0, 1, 0), Forward(0, 0, -1);
	
	
	AmbientLight* ambient;
	DirectionalLight* directional;
	DirectionalLight* directional2;
	SpotLight* spot;
	
	 
	float PlaneDist = 1; 
	ambient = new AmbientLight(Vec(0.0, 0.0, 0.0));
	directional = new DirectionalLight(Vec(0, 0, -1), Vec(0., 0.5, 0.5));
	//directional2 = new DirectionalLight(Vec(-1, -1, 0), Vec50.1, 0.4, 0.2));
	spot = new SpotLight(Vec(0, 20, -10 ), Vec(0, -1, 0), Vec(0.5, 0.5, 0.5), 50/180* M_PI);

	intersectionFinder = new  NaiveIntersection();
	scene =new Scene(intersectionFinder, ambient);
	camera = Camera(CamPos, Up, Forward, ViewPlane(width, height, PlaneDist),1);
	
	Material material(Vec(0.5, 0.5, 0.5), Vec(0, 1, 1), Vec(0, 1, 1), 1),
		material2(Vec(0.5, 0.5, 0), Vec(0, 0.7, 0.7), Vec(0.5, 0.8, 1), 1);
	
	Sphere* sphere = new Sphere(Vec(0, 0, -10), 1, material);
	
	Plane* plane = new Plane(Vec(0, 0, -10), Vec(0, 1, 1), 2, 2, material2);
	
	//scene->objects.push_back(plane);
	scene->objects.push_back(sphere);
	scene->lightSources.push_back(directional);
//	scene->lightSources.push_back(spot);


 
}

int main(int  argc, char** argv)
{
	
	GLubyte *pic;
	

	
	
	createScene();
	pic =camera.getPicture(*scene, *intersectionFinder);

	Display display(width, height, "RayTracing");
	display.setPicture(pic);
	display.show();
 
	delete intersectionFinder;
	delete pic;
	delete scene;
	return 0;
	
	 
	return 0;
}