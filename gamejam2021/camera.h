#ifndef CAMERA_H
#define CAMERA_H

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Vertex.hpp>
#include "point.h"

class Camera{
    public:
        Camera(sf::RenderWindow *window);
        void render(sf::RenderWindow &window);
        void update(float delta);

        void drawLine(Point a, Point b);
        void drawCube(Point a);

    private:

        Point position;
        Point forward;
        Point right;

        sf::RenderWindow *window;

        void recalculate();

        Point worldToCamSpace(Point p);
        sf::Vertex pointToScreenSpace(Point p);

        float roty;

        float siny, cosy;


};

#endif // CAMERA_H
