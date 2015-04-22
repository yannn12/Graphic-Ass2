#pragma once

class Scene;
 
#include "Object.h"
#include <vector>
#include "Camera.h"
#include "LightSource.h"


class Scene
{

	

public:
	
	Scene();
	~Scene();
	
	std::vector <Object*> objects;
	std::vector <LightSource*> LightSources;
	Camera *camera;


};



