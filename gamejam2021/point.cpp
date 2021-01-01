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
