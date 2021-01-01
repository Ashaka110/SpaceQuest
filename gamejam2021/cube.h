#ifndef CUBE_H
#define CUBE_H

#include <SFML/Graphics.hpp>
#include "point.h"
#include "camera.h"

class Cube{
    public:
        Cube(){};
        Cube(Point pos);
        void render(Camera *camera);
        void update(float delta);
        Point Position;

    private:

        void drawSegment(Camera *camera, Point a, Point b);

};

#endif // CUBE_H
