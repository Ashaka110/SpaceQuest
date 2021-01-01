#include <iostream>
#include "cube.h"

Cube::Cube(Point pos){
    this->Position = pos;

    //std::cout << "Cube\n";

}

void Cube::render(Camera *camera){
    float xscale = 1.0f;
    float yscale = 1.0f;
    float zscale = 1.0f;

    Point verts[8] = {
        Point( .5, .5, .5),
        Point( .5, .5,-.5),
        Point( .5,-.5, .5),
        Point( .5,-.5,-.5),
        Point(-.5, .5, .5),
        Point(-.5, .5,-.5),
        Point(-.5,-.5, .5),
        Point(-.5,-.5,-.5),
    };

    drawSegment(camera, verts[0], verts[1]);
    drawSegment(camera, verts[2], verts[3]);
    drawSegment(camera, verts[4], verts[5]);
    drawSegment(camera, verts[6], verts[7]);

    drawSegment(camera, verts[0], verts[2]);
    drawSegment(camera, verts[1], verts[3]);
    drawSegment(camera, verts[4], verts[6]);
    drawSegment(camera, verts[5], verts[7]);

    drawSegment(camera, verts[0], verts[4]);
    drawSegment(camera, verts[1], verts[5]);
    drawSegment(camera, verts[2], verts[6]);
    drawSegment(camera, verts[3], verts[7]);
}

void Cube::drawSegment(Camera *camera, Point a, Point b){

    camera->drawLine(Point::add(a, Position), Point::add(b, Position));
}

void Cube::update(float delta){
    
}
