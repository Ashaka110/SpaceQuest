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
        void drawLine(Point a, Point b, sf::Color color);
        void drawLine(Point a, Point b, sf::Color colora, sf::Color colorb);
        void drawCube(Point a);
		void drawText(sf::Text text);

        Point position;
		float distortiony = 0 ;
        sf::RenderWindow *window;
    private:

        Point forward;
        Point right;
		sf::Font font;

		

        void recalculate();

        Point worldToCamSpace(Point p);
        sf::Vertex pointToScreenSpace(Point p);

        float roty;

        float siny, cosy;

		float gameTime = 0;

};

#endif // CAMERA_H
