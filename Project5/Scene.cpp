#include "Scene.h"
#include "Object.h"
#include <vector>

Scene::Scene()
{
	objects = std::vector <Object*>();
}


Scene::~Scene()
{
	for (std::vector<Object*>::iterator it = objects.begin(); it != objects.end(); ++it){

		delete *it;
	}
}
