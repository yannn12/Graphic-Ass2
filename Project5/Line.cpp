#include "Line.h"
#include <math.h>
 
using namespace std;

Line::Line(Vec &p, Vec &v) : p(p), v(v)
{
	this->v.normalize();
}

Line::Line(const Line& line) : p(line.p), v(line.v)
{}

Line::~Line(){}

/*
	compute disatnce between 2 lines by the  formula     |(p1-p2) * (v1 X v2)| / |v1 X v2|
	if lines are linearly depended (i.e v1 x v2 = 0 ) the distance is calculated by (p1-p2)
*/
float Line::distance(const Line& line)   
{
	Vec	cross = (v ^ line.v);	 

	if (cross.isZero()){	
		return (p - line.p).getLength();
	}

	return  abs(cross * (p - line.p)) / cross.getLength();
}

std::string Line::toString()
{
	return  "Line< p: " + p.toString() + ", v: " + v.toString() +">";

}

Vec Line::getPoint(float t)
{
	return (p + v * t);
}