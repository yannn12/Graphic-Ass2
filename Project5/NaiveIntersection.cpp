#include "NaiveIntersection.h"
#include "Ray.h"
#include "Scene.h"
#include "Intersection.h"
#include <float.h>
#include <vector>
#include "Const.h"


 

NaiveIntersection::NaiveIntersection()
{}


NaiveIntersection::~NaiveIntersection()
{

}



Intersection NaiveIntersection::FindIntersection(Ray& ray, Scene& scene)
{	
	float min_t = FLT_MAX;
	Object* min_primitive = NULL;
	for (std::vector<Object*>::iterator obj = scene.objects.begin(); obj != scene.objects.end(); ++obj)
	{
		float t = (*obj)->Intersect(ray);
		if (t < min_t && t > zeroTolerance)
		{
			min_primitive = (Object*)(*obj);
			min_t = t;
		
		}
	}

	return Intersection(min_t, min_primitive);
}
