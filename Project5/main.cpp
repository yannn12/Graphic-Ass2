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
int width = 512, height = 512;
//Vec CamPos(0, 0, 0), Up(0, 1, 0), Forward(0, 0, 1);
//
//const int width = 320, height = 240,dpi =1;
//
//float PlaneDist = 30.0f;

IntersectionEngine *intersectionFinder = new  NaiveIntersection();

void createScene(){

	Vec CamPos(0, 0, -2), Up(0, 1, 0), Forward(0, 0, 1);

	float PlaneDist = 10;

	camera = Camera(CamPos, Up, Forward, ViewPlane(width, height, PlaneDist), 1);
	//for (int i = 0; i < 10; i++){
	//Sphere* sphere = new Sphere(Vec(-100 + i*50, i*100, 20+i*10), 15+i*2, Vec(30+i*10, 60, 90));
		Sphere* sphere = new Sphere(Vec(-20, 20, 20), 20, Vec(40, 20, 80));
		Plane* plane = new Plane(Vec(0, 0, 100), Vec(0, -1, -1), Vec(30, 60, 90), 0.5, 0.5);
		scene.objects.push_back(sphere);
		scene.objects.push_back(plane);
	//}
	//scene.objects.push_back(sphere2);
	//scene.objects.push_back(floor);
}

int main(int  argc, char** argv)
{
	
	GLubyte *pic;
	

	

	createScene();
	pic =camera.getPicture(scene, *intersectionFinder);

	Display display(width, height, "RayTracing");
	display.setPicture(pic);
	display.show();
 
	delete intersectionFinder;
	delete pic;
	return 0;
	
	
	
	Ray ray(Vec(0, 0, 0), Vec(0, 0.53, 1));
	
	cout << ray.toString() << endl;
	cout << "length" <<ray.v.getLength() << endl;
	
	

	Sphere* sphere =new Sphere(Vec(0, 0, 2), 1, Vec(0, 0, 3));
	Scene s;
	s.objects.push_back(sphere);
	NaiveIntersection i;
	
	Intersection inters = i.FindIntersection(ray,s);
	float t = inters.t;

	cout << t <<endl;
	cout << "(x,y)  "<< (ray.v * t).toString() << endl;
	int a;
	cin >> a;
	
	return 0;
}