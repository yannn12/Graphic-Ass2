#include "Camera.h"
#include "NaiveIntersection.h"
#include "Intersection.h"
#include "Const.h" 


inline void castRay(Vec& cameraPos, Vec& pointOnPlane, int index, GLubyte* pic, IntersectionEngine& intersectionFinder, Scene& scene);
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
	int pX, pY;
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
			castRay(position, Qdl , index, pic, intersectionFinder, scene);
			
			index = y * viewPlane.width + (viewPlane.width -1 - x);
			castRay(position, Qdr, index, pic, intersectionFinder, scene);
			
			index = (viewPlane.height -1- y) * viewPlane.width + x;
			castRay(position, Qul , index, pic, intersectionFinder, scene);
			
			index = (viewPlane.height -1 - y) * viewPlane.width+  (viewPlane.width -1 - x);
			castRay(position, Qur, index, pic, intersectionFinder, scene);
			
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


inline void castRay(Vec& cameraPos, Vec& pointOnPlane, int index, GLubyte* pic, IntersectionEngine& intersectionFinder,Scene& scene){

	// vector  from the camera to the postion 
	Vec vector = (pointOnPlane - cameraPos);
	vector.normalize();
	Ray ray(cameraPos, vector);
	Intersection intersection = intersectionFinder.FindIntersection(ray, scene);
	Vec color;

	if (intersection.object == NULL)
		color = BACKGROUND_COLOR;
	else{
		color = intersection.object->getColor(ray.getPoint(intersection.t));
		//	printf(" x: %d  , y: %d\n", xCenter + pX + x * v, yCenter + pY + y * h);
	}
	putColor(pic, index, color);

}
