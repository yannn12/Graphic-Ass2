#include "Scene.h"
#include "Object.h"
#include <vector>


Scene::Scene(IntersectionEngine* intersection, AmbientLight* ambientLight) :intersectionFinder(intersection), ambientLight(ambientLight)
{
	objects = std::vector <Object*>();
	lightSources = std::vector<LightSource *>();
}


Scene::Scene()
{
	objects = std::vector <Object*>();
	lightSources = std::vector<LightSource *>();
	ambientLight = 0;
	intersectionFinder = 0;
}


Scene::~Scene()
{
	for (std::vector<Object*>::iterator it = objects.begin(); it != objects.end(); ++it){

		delete *it;
	}

	for (std::vector<LightSource *>::iterator it = lightSources.begin(); it != lightSources.end(); ++it){

		delete *it;
	}

	delete ambientLight;
	delete intersectionFinder;
	delete camera;

}
