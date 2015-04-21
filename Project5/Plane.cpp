#include "Plane.h"


Plane::Plane(Vec& center, Vec& n, Vec& color, float width, float length) 
				: center(center), n(n), color(color), width(width), length(length)
{
	// if x is a point on the plane then (x-center).n=0  ===>  x.n + (-x.n)=0 --->  we bring it to the form p.n +d =0
	//also we normalize the values so that the plane eqaution n.p+d=0 becomes n.p / |n|  + d /|n| =0
	
	d = center * n;
	float l = this->n.normalize();
	d = -d / l;

	//tmp vectors for creating the plane edges
	Vec v1(0,0,0);
	Vec v2;

	 //if the x in the normal is 0 so we ser v1 to be parallel to z  i.e the plane is parallel to z axis  
	 // it is true for all axis, 2 coordinate can be 0 but we select the first one
	
	int zeroIndex = 0; // x coord
	
	if (n.x == 0){

	}
	else {
		if (n.y == 0) {
			zeroIndex = 1;
		}
		else {
			if (n.z == 0)
			{
				zeroIndex = 2;
			}
		}
	}
	
	v1.p[zeroIndex] += length;
	//v2 should be orthogonal to v1 and n , with the size of the width ;
	v2 = (v1 ^ n);  
	v2.normalize(); 
	v2 =  v2* width;
	
	p1 = center + v1 + v2;   
	p2 = center + v1 - v2;
	p3 = center - v1 - v2;
	p4 = center - v1 + v2;

	

	
	this->color = color;
}




Plane::~Plane()
{}


	
Vector3f Plane::normal(Vector3f& point){
		
	return n;

}



inline bool checkIntersaction(Vec& vertex1, Vec& vertex2, Vec& pp0, Vec& RayOrigin){

	Vec u1 = vertex1 - RayOrigin;
	Vec u2 = vertex2 - RayOrigin;
	Vec n = u1 ^ u2;
	n.normalize();
	return (pp0 *n) >= 0;


}

inline bool intersactTriangle(Vec&  a, Vec& b , Vec& c, Vec& PointonPlane, Vec& RayOrigin){

	Vec pp0=(PointonPlane - RayOrigin);

	return  checkIntersaction(a, b, pp0, RayOrigin) &&
			checkIntersaction(a, c, pp0, RayOrigin) &&
			checkIntersaction(b, c, pp0, RayOrigin);
	
}

//returns negative number  if there are  no intersactions or the ray is orthogonal
float Plane::Intersect(Ray& ray)
{
	float dot = (n * ray.v);
	if (dot == 0) // ray is orthogonal
		return -1;
	float t = -(n*ray.p + d) / dot;
	Vec pointOnPlane = ray.p + ray.v * t;

	if ( !intersactTriangle(p1, p2, p3, pointOnPlane, ray.p) && !intersactTriangle(p1, p3, p4, pointOnPlane, ray.p))
		return -1;

	return t;
}