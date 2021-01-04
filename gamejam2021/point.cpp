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

Point Point::getCenter(Point a, Point b)
{
	return Point((a.x+b.x)/2,(a.y+b.y)/2,(a.z+b.z)/2);
}


float Point::sqrDistance(Point a, Point b)
{
	Point diff = Point::add(a, Point::scale(b, -1));
	return diff.x*diff.x + diff.y*diff.y + diff.z*diff.z;
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
		p[i] = Point(p[i].x * sina + p[i].y * cosa, 
					 p[i].x * cosa - p[i].y * sina, 
				     p[i].z);
	}

}

Point Point::RotateAroundZ(Point p, Point center, float angle)
{
	float sina = sin(angle);
	float cosa = cos(angle);

	Point d = Point::add(p, scale(center, -1));
	Point rd = Point( (d.x) * cosa - (d.y) * sina,
					(d.x) * sina + (d.y) * cosa,
					d.z);
	return add(rd , center);
}
