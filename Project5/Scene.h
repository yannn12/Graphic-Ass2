#pragma once

 
 
#include "Object.h"
#include <vector>
#include "Camera.h"

#include "AmbientLight.h"
#include "Intersection.h"

class Scene
{

	

public:
	

	IntersectionEngine * intersectionFinder;

	Scene(IntersectionEngine* intersectionFinderFinder, AmbientLight* ambientLight);
	Scene();
	~Scene();
	
	
	Camera * camera;
	std::vector <Object*> objects;
	std::vector <LightSource*> lightSources;
	
	AmbientLight* ambientLight;
	


};



