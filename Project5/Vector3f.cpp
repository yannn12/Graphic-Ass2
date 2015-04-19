#include "Vector3f.h"
#include <math.h>  
#include <iostream>
#include <string>
 
#define lengthSQR(a,b,c) (a*a+b*b+c*c)

static const  Vector3f zero(0, 0, 0);

Vector3f::Vector3f() : x(0), y(0), z(0)
{}

Vector3f::Vector3f(f _x, f _y, f _z) : x(_x), y(_y), z(_z)
{}

Vector3f::Vector3f(const  Vector3f &vec) : x(vec.x), y(vec.y), z(vec.z)
{}


Vector3f::~Vector3f(){}



inline float Vector3f::length()
{
	return sqrt(lengthSQR(x, y, z));
}
inline void Vector3f::normlize()
{
	float l = sqrt(lengthSQR(x, y, z));
	x /= l;
	y /= l;
	z /= l;
}

inline Vector3f Vector3f::operator+(const Vector3f& v)
{
	return Vector3f(v.x + x, v.y + y, v.z + z);
}


inline Vector3f Vector3f::operator-(const Vector3f& v)
{
	return   Vector3f(x - v.x, y - v.y, z - v.z);
}
float Vector3f::operator*(const Vector3f& v)  
{
	return  x*v.x + y*v.y + z*v.z;
}

inline Vector3f Vector3f::operator%(f scalar){
	return  Vector3f(scalar * x, scalar * y, scalar * z);
}

inline Vector3f Vector3f::operator^(const Vector3f& v)
{
	return   Vector3f(-z * v.y + y * v.z, z * v.x - x * v.z, -y * v.x + x * v.y);
} 

inline int Vector3f::operator==(const Vector3f& v)
{
	return (x == v.x && y == v.y && z == v.z);
}

inline std::string Vector3f::toString(){

	return  "Vector3f< x: " + std::to_string(x) + ",y: " + std::to_string(y) + ", z: " + std::to_string(z) + " >";
}

inline int Vector3f::isZero(){

	return  x==0 && y==0 && z==0;

}