#define _CRT_SECURE_NO_DEPRECATE

#include <stdio.h>
#include <iostream>
#include <math.h>
 
#include "SceneParser.h"
#include "Display.h"
#include "glut.h"
#include "Camera.h"
#include "Scene.h"
#include "Plane.h"
#include "sphere.h"
#include "NaiveIntersection.h"
#include "Intersection.h"
#include "DirectionalLight.h"

#include <time.h>

using namespace std;



IntersectionEngine *intersectionFinder;
Scene* scene;
int width = 512, height = 512;
//Vec CamPos(0, 0, 0), Up(0, 1, 0), Forward(0, 0, 1);
//
//const int width = 320, height = 240,dpi =1;
//
//float PlaneDist = 30.0f;

void createSceneFromFile(){
	scene = new Scene();
	ParseScene("scene.txt",*scene);
	scene->intersectionFinder = new  NaiveIntersection();

 
}


void createScene(){

	Vec CamPos(0, 0, 0), Up(0, 1, 0), Forward(0, 0, -1);
	
	
	AmbientLight* ambient;
	DirectionalLight* directional;
	DirectionalLight* directional2;
	SpotLight* spot;
	
	 
	float PlaneDist = 3; 
	ambient = new AmbientLight(Vec(0.0, 0.0, 0));
	directional = new DirectionalLight(Vec(0, -1,-1), Vec(0., 0.5, 0.5));
	directional2 = new DirectionalLight(Vec(1, 0, 0), Vec(0.8, 0.5, 0.2));
	//directional2 = new DirectionalLight(Vec(-1, -1, 0), Vec50.1, 0.4, 0.2));
	float f = 20.0f / 180.0f * M_PI;
	spot = new SpotLight(Vec(0, 10, -13 ), Vec(0, -1, 0), Vec(0.5, 0.5, 0.5), f);

	intersectionFinder = new  NaiveIntersection();
	scene =new Scene(intersectionFinder, ambient);
	scene->camera = new Camera(CamPos, Up, Forward, ViewPlane(width, height, PlaneDist),2);
	
	Material material(Vec(0.5, 0.5, 0.5), Vec(0.5, 0.5, 0.5), Vec(1, 0.8, 1),Vec(1,1,1), 50),
		material2(Vec(0.5, 0.5, 0), Vec(0, 0.7, 0.7), Vec(0.5, 0.8, 1), 1),
		material3(Vec(0.1, 0.6, 0.3), Vec(0.4, 0.8, 0.4), Vec(0, 0.5, 0.5), Vec(1, 1, 1), 5),
		material4(Vec(0.5, 0, 0.5), Vec(0, 0.8, 0.3), Vec(.7, 0.2, 0.8), 20),
		material5(Vec(0.5, 1, 0.5), Vec(0, 0.8, 0.3), Vec(.7, 0.2, 0.8), 20),
		material6(Vec(0.2, 0.3, 0.8), Vec(1, 0.8, 0.3), Vec(.7, 0.2, 0.8), 20);
	
	Sphere* sphere = new Sphere(Vec(0, 1 , -13), 1, material);
	Sphere* sphere2 = new Sphere(Vec(0, 2, -14), 0.5, material4);
	Sphere* sphere3 = new Sphere(Vec(-1, 2, -12), 0.5, material5);
	Sphere* sphere4 = new Sphere(Vec(1, 1, -12), 0.5, material6);
	Plane* plane = new Plane(Vec(0, -1, -13), Vec(0, 1, 0), 200 ,200, material2);
	Plane* plane2 = new Plane(Vec(5, 0, -14), Vec(-1, 0, 1), 5, 5, material3);
	Plane* plane3 = new Plane(Vec(-5, 0, -19), Vec(1, 0,  1), 5, 10, material3);


	scene->objects.push_back(plane);
	scene->objects.push_back(plane2);
	scene->objects.push_back(plane3);
	scene->objects.push_back(sphere);
	scene->objects.push_back(sphere2);
	scene->objects.push_back(sphere3);
	scene->objects.push_back(sphere4);
	scene->lightSources.push_back(directional);
	scene->lightSources.push_back(directional2);
	scene->lightSources.push_back(spot);


 
}

int main(int  argc, char** argv)
{

	GLubyte *pic;

	


	createSceneFromFile();
	time_t start;
	time_t end;

	time(&start);
	pic = scene->camera->getPicture(*scene, *intersectionFinder);
	time(&end);

	double diff = difftime(end, start);
	printf("Rendering time in seconds: %lf\n", diff);

	Display display(width, height, "RayTracing");
	display.setPicture(pic);
	display.show();


	delete intersectionFinder;
	delete pic;
	delete scene;
	return 0;


	Vec a(-1, -1, 0);
	Vec n(0, 1, 0);
	a.normalize();
	n.normalize();
	Vec r = (a - 2 * ((a) * n) * n);
	float c = 0;
	while (c < M_PI / 2){
		Vec r = (a*c - 2 * ( (a*c) * n) * n);
		r.normalize();
		c += 0.1;
		if (n*r<=0){
			c += 0;
		}
	}
	
	return 0;
}