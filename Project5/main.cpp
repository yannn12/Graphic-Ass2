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
AmbientLight* ambient;
DirectionalLight* directional;
DirectionalLight* directional2;
SpotLight* spot;

Scene* scene;
Camera camera;
int width = 512, height = 512;
//Vec CamPos(0, 0, 0), Up(0, 1, 0), Forward(0, 0, 1);
//
//const int width = 320, height = 240,dpi =1;
//
//float PlaneDist = 30.0f;


void createScene(){

	Vec CamPos(0, 0, -2), Up(0, 1, 0), Forward(0, 0, 1);

	float PlaneDist =110; 
	ambient = new AmbientLight(Vec(0.0, 0.0, 0.0));
	directional = new DirectionalLight(Vec(0,-1, 0), Vec(0.5, 0.5, 0.5));
	directional2 = new DirectionalLight(Vec(-1, -1, 0), Vec(0.1, 0.4, 0.2));
	spot = new SpotLight(Vec(0, 5, 120), Vec(0, -1, 0), Vec(0.5, 0.5, 0.5), 3.14 / 10);

	intersectionFinder = new  NaiveIntersection();
	scene =new Scene(intersectionFinder, ambient);
	camera = Camera(CamPos, Up, Forward, ViewPlane(width, height, PlaneDist), 1);
	
	
	//for (int i = 0; i < 10; i++){
	//Sphere* sphere = new Sphere(Vec(-100 + i*50, i*100, 20+i*10), 15+i*2, Vec(30+i*10, 60, 90));
		Sphere* sphere = new Sphere(Vec(20, 40, 120), 40, Vec(40, 20, 80));

	/*	Plane* plane1 = new Plane(Vec(20, 0, 150),	Vec(-1, 0, -1), Vec(60, 60,  60), 100, 100);
		Plane* plane2 = new Plane(Vec(-20, 0, 150), Vec(1, 0, -1),	Vec(120, 120, 120), 100, 100);
		Plane* plane3 = new Plane(Vec(0, 20, 200),	Vec(0, -1, 0),	Vec(180, 180, 180), 100, 100);*/
		Plane* plane4 = new Plane(Vec(0, -20, 150), Vec(0, 1, 0),	Vec(60, 30, 240), 100, 100);


	//	sphere->material = Material(Vec(0.7, 0.3, 0.6), Vec(0.7, 0.3, 0.6), Vec(1, 1, 1),2);
		plane4->material = Material(Vec(80 / 255.f, 153.0f / 255.f, 77.0f / 255.0f), Vec(80 / 255.f, 153.0f / 255.f, 77.0f / 255.0f), Vec(0, 0, 0),0);
	//	scene->objects.push_back(sphere);
	//	scene.objects.push_back(plane1);
	//	scene.objects.push_back(plane2);
	//	scene.objects.push_back(plane3);
		scene->objects.push_back(plane4);
		scene->lightSources.push_back(spot);
		scene->lightSources.push_back(directional);
	//	scene->lightSources.push_back(directional2);
	//}
	//scene.objects.push_back(sphere2);
	//scene.objects.push_back(floor);
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
	
	Vec x(1, 0, 0);
	Vec y(0, 1, 0);

	cout << (x^y).toString() << endl;
	cout << (y^x).toString() << endl;
	
	
	Ray ray(Vec(0, 0, 0), Vec(0.5, 10.5, 1));
	
	cout << ray.toString() << endl;
	cout << "length" <<ray.v.getLength() << endl;
	
	
	Plane* plane = new Plane(Vec(0, 0, 1), Vec(0, 0, -1), Vec(30, 60, 90), 1, 1);
	Sphere* sphere =new Sphere(Vec(0, 0, 2), 1, Vec(0, 0, 3));
	Scene s;
	s.objects.push_back(plane);
	NaiveIntersection i;
	
	Intersection inters = i.FindIntersection(ray,s);
	float t = plane->Intersect(ray);
		
	cout << t <<endl;
	cout << "(x,y)  "<< (ray.v * t).toString() << endl;
	
	int a;
	cin >> a;
	
	return 0;
}