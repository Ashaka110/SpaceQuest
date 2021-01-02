#include <iostream>
#include "point.h"

void Point::print(){
    std::cout << "Printing\n";
}

Point::Point(float x, float y, float z){
    this->x = x;
    this->y = y;
    this->z = z;
}
Point Point::add(Point a, Point b){
    return Point(a.x+b.x, a.y+b.y, a.z+b.z);
}
Point Point::scale(Point a, float s){
    return Point(a.x*s, a.y*s, a.z*s);
}

void Point::Translate(Point p[], int arraySize, Point translate)
{
	for (int i = 0; i < arraySize; i++)
	{
		p[i] = add(p[i], translate);
	}
}

void Point::RotateZ(Point p[], int arraySize, float angle)
{
	float sina = sin(angle);
	float cosa = cos(angle);

	for (int i = 0; i < arraySize; i++)
	{
		p[i] = Point(p[i].x * sina + p[i].y * cosa, p[i].x * cosa - p[i].y * sina, p[i].z);
	}

}
