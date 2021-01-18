#include <SFML/Window/Keyboard.hpp>
#include <iostream>
#include <math.h>

#include "camera.h"
#include "cube.h"


Camera::Camera(sf::RenderWindow *window){
    this->window = window;

    roty = 0;
    recalculate();

    std::cout << "Camera\n";

	font.loadFromFile("Retro Gaming.ttf");
}

void Camera::render(sf::RenderWindow &window){

}

void Camera::update(float delta){
    
	/*
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::R))
    {
        position = Point(0,0,0);
        roty = 0;
        recalculate();
    }

    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Left))
    {
        position = Point::add( position, Point::scale(right, -delta));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Right))
    {
        position = Point::add( position, Point::scale(right, delta));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Up))
    {
        position = Point::add( position, Point::scale(forward, -delta));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Down))
    {
        position = Point::add( position, Point::scale(forward, delta));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::E))
    {
        position = Point::add( position, Point::scale(Point(0,1,0), delta));
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::Q))
    {
        position = Point::add( position, Point::scale(Point(0,1,0), -delta));
    }
    
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::A ))
    {
        roty += delta;
        recalculate();
    }
    if(sf::Keyboard::isKeyPressed(sf::Keyboard::D ))
    {
        roty -= delta;
        recalculate();
    }
	*/
	gameTime += delta;
}

void Camera::recalculate(){
        siny = sin(roty);
        cosy = cos(roty);
        forward = Point( siny, 0, cosy);
        right = Point( -cosy, 0, siny);
}

void Camera::drawLine(Point a, Point b){

	drawLine(a, b, sf::Color(255,255,255));
}

void Camera::drawLine(Point a, Point b, sf::Color color)
{
	drawLine(a, b, color, color);
}

void Camera::drawLine(Point a, Point b, sf::Color colora, sf::Color colorb)
{
    Point camSpaceA = worldToCamSpace(a);
    Point camSpaceB = worldToCamSpace(b);

    sf::Vertex line[] =
    {
        pointToScreenSpace(camSpaceA),
        pointToScreenSpace(camSpaceB),
    };

	line[0].color = colora;
	line[1].color = colorb; //sf::Color(0, 200, 0)

    if(camSpaceA.z > 0 && camSpaceB.z > 0){
        window->draw(line, 2, sf::Lines);
    }
}

Point Camera::worldToCamSpace(Point p){
    Point l = Point::add(p, position);
    return Point(
            l.x * cosy - l.z * siny, 
            -l.y,
            l.z * cosy + l.x * siny);
}

sf::Vertex Camera::pointToScreenSpace(Point p){

    float x =400 * (1+((p.x + p.z*p.z*-.000f) / (p.z)));
    float y =400 * (1+((p.y + p.z*p.z*-.006f * distortiony) / (p.z)));

    return sf::Vertex(sf::Vector2f(x, y));

}

void Camera::drawCube(Point a){
    Cube c(a);
    c.render(this);
}

void Camera::drawText(sf::Text text)
{
	text.setFont(font);
	window->draw(text);
}




