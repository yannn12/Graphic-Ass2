#include "Camera.h"
#include "NaiveIntersection.h"
#include "Intersection.h"
#include "Const.h" 


inline void castRay(Vec& cameraPos, Vec& pointOnPlane, int index, GLubyte* pic, Scene& scene);
inline void putColor(GLubyte *pic, int index, Vec color);

Camera::Camera(Vec& position, Vector3f& up, Vector3f& forward, ViewPlane& viewPlane, int dpi) :
up(up), forward(forward), right(up ^ forward), position(position), viewPlane(viewPlane), dpi(dpi)
{
	

	this->up.normalize();
	this->forward.normalize();
	this->right.normalize();

}

Camera::Camera() :
up(Vec::zero()), forward(Vec::zero()), right(Vec::zero()), position(Vec::zero()), viewPlane(), dpi(0)
{}

Camera::~Camera()
{
	
}

GLubyte* Camera::getPicture(Scene& scene, IntersectionEngine& intersectionFinder){  // dpi is not counted 

	GLubyte* pic = (GLubyte*)malloc(sizeof(GLubyte)* 3 * viewPlane.width * viewPlane.height);
	Vec pointOnViewPlane, horizontal, vertical ,color;
	int index;
 
	int yCenter = (viewPlane.height / 2 );
	int xCenter = (viewPlane.width / 2 );
	// vector from the camera to the center of the viewing plane 
	Vec pCenter = position + forward * viewPlane.dist; 
 
	unsigned int count=0;

	for (int y = 0; y < yCenter; y++){
		for (int x = 0; x < xCenter; x++){
				
			horizontal  = right * (xCenter - x);
			vertical	=	up * (yCenter - y);
			
			
			Vec Qul = pCenter - horizontal + vertical;
			Vec Qdl = pCenter - horizontal - vertical;
			Vec Qur = pCenter + horizontal + vertical;
			Vec Qdr = pCenter + horizontal - vertical;
			
			index = y * viewPlane.width + x;
			castRay(position, Qdl, index, pic, scene);
			
			index = y * viewPlane.width + (viewPlane.width -1 - x);
			castRay(position, Qdr, index, pic, scene );
			
			index = (viewPlane.height -1- y) * viewPlane.width + x;
			castRay(position, Qul, index, pic, scene );
			
			index = (viewPlane.height -1 - y) * viewPlane.width+  (viewPlane.width -1 - x);
			castRay(position, Qur, index, pic, scene);
			
		}
		
	}
	//printf("hit count: %d", count);
	return pic;
}




/**************   View Plane *******************/

ViewPlane::ViewPlane(int width, int height, float dist) : width(width), height(height), dist(dist)
{}

ViewPlane::ViewPlane( ) :
				width(0),
				height(0),
				dist(0)
{}

ViewPlane::~ViewPlane()
{}
 
ViewPlane::ViewPlane(ViewPlane& p) : width(p.width), height(p.height), dist(p.dist)

{}


inline void putColor(GLubyte *pic, int index, Vec color){

		
	pic[index * 3	 ] = color.x;
	pic[index * 3 + 1] = color.y;
	pic[index * 3 + 2] = color.z;

}


inline bool ocluded(Scene& scene, Vec& pointOfIntersection, Vec& DirectionOfLight){

	Ray ray(pointOfIntersection, DirectionOfLight);

	Intersection intersection = scene.intersectionFinder->FindIntersection(ray, scene);

	return (intersection.object !=NULL);

}

inline Vec calcColor(Scene& scene, Ray& ray, Intersection& intersection, Vec& cameraPos , int index)
{
	
	Vec pointOfIntersection = ray.getPoint(intersection.t);
	Object* obj = intersection.object;

	Vec diffuse = Vec::zero();
	Vec specular = Vec::zero();
	
	Vec kd = obj->Kd(pointOfIntersection);
	Vec ks = obj->Ks(pointOfIntersection);
	Vec norm = obj->normal(pointOfIntersection);
	int specExp = obj->getSpecularExponent();


	for (std::vector<LightSource *>::iterator it = scene.lightSources.begin(); it != scene.lightSources.end(); ++it){


		LightImpact impact = (LightImpact ) (*it)->lightImpact(pointOfIntersection);
		
		if (!impact.IsHit )
			continue;
		if (ocluded(scene, pointOfIntersection, (impact.Direction) ))
			continue;

		float dir = (impact.Direction)*norm;
		if (dir > 0)
			diffuse += dir * (impact.Lcolor);

		Vec R = ((impact.Direction) - 2 * ((impact.Direction) * norm) * norm);
		Vec V = cameraPos - pointOfIntersection;
		V.normalize();
		float spec = pow ( (R * V) ,1);

		if (spec > 0)
			specular += spec * (impact.Lcolor);
 
	}


	//			ambient														
	Vec color =((*obj).Ka(pointOfIntersection) % scene.ambientLight->Icolor
		//			diffuse 	
		+ kd % diffuse
		//			Specular
		+ks % specular
		//				to RGB
		) % Vec(255, 255, 255);
	 														
	return Vec(fminf(color.x, 255), fminf(color.y, 255), fminf(color.z, 255));

}


inline void castRay(Vec& cameraPos, Vec& pointOnPlane, int index, GLubyte* pic, Scene& scene){

	// vector  from the camera to the postion 
	Vec vector = (pointOnPlane - cameraPos);
	vector.normalize();
	Ray ray(cameraPos, vector);
	 
	Vec color;
	Intersection intersection= (*scene.intersectionFinder).FindIntersection(ray, scene);
	if (intersection.object == NULL)
	{
		color= BACKGROUND_COLOR;
	}
	else {

		color = calcColor(scene, ray,intersection , cameraPos, index);
	}
	 
	putColor(pic, index, color);

}



