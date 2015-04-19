#include "Camera.h"
#include "NaiveIntersection.h"
#include "Intersection.h"
#include "Const.h" 


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
	Vec pointOnViewPlane, horizontal, vertical,color;
	int index;
	int pX, pY;
	int yCenter = (viewPlane.height / 2 - 1);
	int xCenter = (viewPlane.width / 2 - 1);
	// vector from the camera to the center of the viewing plane 
	Vec pCenter = position + forward * viewPlane.dist; 
	

	unsigned int count=0;

	for (int y = 0; y < yCenter; y++){
		for (int x = 0; x < xCenter; x++){
				
			horizontal	= right * x,
			vertical	= up * y;
				
			for (int v = -1; v <= 1; v += 2){
				for (int  h= -1; h <= 1; h += 2){	

						pointOnViewPlane = pCenter + (horizontal * h) + (vertical * v);
						pX = (v >0) ? 1 : 0;
						pY = (h >0) ? 1 : 0;
						index = ( yCenter + pY  + y * h)*viewPlane.width + ( xCenter + pX + x * v );
						if (index >= 480 * 640 || index < 0){
							printf(" i: %d   x: %d y: %d  h: %d v: %d  px: %d py: %d\n ", index, x, y, h, v, pX, pY);
							continue;
						}
						// vector  from the camera to the postion 
						Vec vector = (pointOnViewPlane - this->position);
						vector.normalize();
						Ray ray(position, vector);			
						Intersection intersection= intersectionFinder.FindIntersection(ray, scene);
						
						if (intersection.object == NULL)
							color = BACKGROUND_COLOR;
						else{
							color = intersection.object->getColor(ray.getPoint(intersection.t));
							count++;
						}
						putColor(pic, index, color);
				}
			}
		}
		
	}
	printf("hit count: %d", count);
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