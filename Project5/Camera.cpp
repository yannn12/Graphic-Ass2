#include "Camera.h"
#include "NaiveIntersection.h"
#include "Intersection.h"
#include "Const.h" 
#include "Vector3f.h"

inline void castRay(Vec& cameraPos, Vec& pointOnPlane, int index, GLubyte* pic, Scene& scene, int recursive);
inline void putColor(GLubyte *pic, int index, Vec color);
inline Vec calcRecursiveColor(Scene& scene, Ray& ray, Vec& cameraPos, int recursive);

Camera::Camera(Vec& position, Vector3f& up, Vector3f& forward, ViewPlane& viewPlane, float pixelwidth) :
up(up), forward(forward), right( forward ^up), position(position), viewPlane(viewPlane), pixelwidth(pixelwidth)
{
	

	this->up.normalize();
	this->forward.normalize();
	this->right.normalize();

}

Camera::Camera(Vec& position, Vector3f& up, int width, int height, Vec& centerOfViewPlane, float pixelwidth):
	up(up), position(position), pixelwidth(pixelwidth)
{
	forward=(centerOfViewPlane - position);
	right=(up ^ forward);
	viewPlane = ViewPlane(width, height, forward.getLength());

	this->up.normalize();
	this->forward.normalize();
	this->right.normalize();
	
}

Camera::Camera() :
up(Vec::zero()), forward(Vec::zero()), right(Vec::zero()), position(Vec::zero()), viewPlane(), pixelwidth(1)
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
 
	float w = this->pixelwidth;
	float Rx = w / viewPlane.width;
	float Ry = w / viewPlane.height;

	for (int y = 0; y <viewPlane.height-1; y++){
		for (int x = 0; x < viewPlane.width-1; x++){

			
			index = y * viewPlane.width + x;
			Vec p = pCenter + (x - xCenter)*Rx*right + (y - yCenter)*Ry*up;
		//	printf("%s\n", p.toString().c_str());
			castRay(position, p, index, pic, scene,2);


		}

	}
	/*for (int y = 0; y < yCenter; y++){
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
		
	}*/
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

/**********************  util ********************/
inline void putColor(GLubyte *pic, int index, Vec color){

		
	pic[index * 3	 ] = color.x;
	pic[index * 3 + 1] = color.y;
	pic[index * 3 + 2] = color.z;

}


inline bool ocluded(Scene& scene, Vec& pointOfIntersection, Vec& DirectionOfLight, Object* currentObject){

	Ray ray(pointOfIntersection, DirectionOfLight);

	Intersection intersection = scene.intersectionFinder->FindIntersection(ray, scene);

	return (!intersection.object == NULL &&  intersection.object != currentObject);

}

Vec normPrec(0,0,0);

inline Vec calcColor(Scene& scene, Ray& ray, Intersection& intersection, Vec& cameraPos , int index, int recursive)
{
	
	Vec pointOfIntersection = ray.getPoint(intersection.t);
	Object* obj = intersection.object;

	Vec diffuse = Vec::zero();
	Vec specular = Vec::zero();
	
	Vec kd = obj->Kd(pointOfIntersection);
	Vec ks = obj->Ks(pointOfIntersection);
	Vec kt = obj->Kt(pointOfIntersection);
	Vec norm = obj->normal(pointOfIntersection);
	int specExp = obj->getSpecularExponent();


	for (std::vector<LightSource *>::iterator it = scene.lightSources.begin(); it != scene.lightSources.end(); ++it){


		LightImpact impact = (LightImpact ) (*it)->lightImpact(pointOfIntersection);
		
		if (!impact.IsHit )
			continue;
		if (ocluded(scene, pointOfIntersection, (impact.Direction) ,obj))
			continue;

		float dir = (impact.Direction)*norm;
		
		if (dir > 0 )
			diffuse+=(dir * (impact.Lcolor));
			
		
		Vec R = ((impact.Direction) - 2 * ((impact.Direction) * norm) * norm);
		Vec V = cameraPos - pointOfIntersection;
		V.normalize();

		float spec =(R * V);
		spec = pow(spec, specExp);
		if (spec > 0 && dir>0){
			
			specular+=(spec * (impact.Lcolor));
		}
	
 
	}
	Vec rec;
	if (!kt.isZero() )
		rec = calcRecursiveColor(scene, Ray(pointOfIntersection + norm * 2 * zeroTolerance, norm), cameraPos, recursive - 1);
	//			ambient														
	Vec color = ((*obj).Ka(pointOfIntersection) % scene.ambientLight->Icolor
		//	diffuse 	
		+ kd % diffuse
		//			Specular
		+ ks % specular

		+ kt % rec
		//				to RGB
		) % Vec(255, 255, 255);
	color.LimValue(255);
	return color;

}

inline Vec calcRecursiveColor(Scene& scene, Ray& ray, Vec& cameraPos, int recursive)
{
	if (recursive == 0){
		return BACKGROUND_COLOR;
	}
	Intersection intersection = scene.intersectionFinder->FindIntersection(ray, scene);
	if (intersection.object == 0){
		return BACKGROUND_COLOR;
	}
	Vec pointOfIntersection = ray.getPoint(intersection.t);
	Object* obj = intersection.object;

	Vec diffuse = Vec::zero();
	Vec specular = Vec::zero();

	Vec kd = obj->Kd(pointOfIntersection);
	Vec ks = obj->Ks(pointOfIntersection);
	Vec kt = obj->Kt(pointOfIntersection);
	Vec norm = obj->normal(pointOfIntersection);
	int specExp = obj->getSpecularExponent();


	for (std::vector<LightSource *>::iterator it = scene.lightSources.begin(); it != scene.lightSources.end(); ++it){


		LightImpact impact = (LightImpact)(*it)->lightImpact(pointOfIntersection);

		if (!impact.IsHit)
			continue;
		if (ocluded(scene, pointOfIntersection, (impact.Direction), obj))
			continue;

		float dir = (impact.Direction)*norm;

		if (dir > 0)
			diffuse += (dir * (impact.Lcolor));


		Vec R = ((impact.Direction) - 2 * ((impact.Direction) * norm) * norm);
		Vec V = cameraPos - pointOfIntersection;
		V.normalize();

		float spec = (R * V);
		spec = pow(spec, specExp);
		if (spec > 0 && dir>0){

			specular += (spec * (impact.Lcolor));
		}


	}
	Vec rec = Vec::zero();
	if (!kt.isZero())
		rec = calcRecursiveColor(scene, Ray(pointOfIntersection + norm * 2 * zeroTolerance, norm), cameraPos, recursive - 1);
	//			ambient														
	Vec color = ((*obj).Ka(pointOfIntersection) % scene.ambientLight->Icolor
		//	diffuse 	
		+ kd % diffuse
		//			Specular
		+ ks % specular

		+ kt % rec
		//				to RGB
		);
	color.LimValue(1);
	return color;

}

inline void castRay(Vec& cameraPos, Vec& pointOnPlane, int index, GLubyte* pic, Scene& scene,int recursive){

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

		color = calcColor(scene, ray, intersection, cameraPos, index, recursive);
	}
	 
	putColor(pic, index, color);

}



