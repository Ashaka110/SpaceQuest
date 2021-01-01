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
}

void Camera::render(sf::RenderWindow &window){

}

void Camera::update(float delta){
    
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
}

void Camera::recalculate(){
        siny = sin(roty);
        cosy = cos(roty);
        forward = Point( siny, 0, cosy);
        right = Point( -cosy, 0, siny);
}

void Camera::drawLine(Point a, Point b){

    Point camSpaceA = worldToCamSpace(a);
    Point camSpaceB = worldToCamSpace(b);

    sf::Vertex line[] =
    {
        pointToScreenSpace(camSpaceA),
        pointToScreenSpace(camSpaceB),
    };


    if(camSpaceA.z > 0 && camSpaceB.z > 0){
        window->draw(line, 2, sf::Lines);
    }
}

Point Camera::worldToCamSpace(Point p){
    Point l = Point::add(p, position);
    return Point(
            l.x * cosy - l.z * siny, 
            l.y,
            l.z * cosy + l.x * siny);
}

sf::Vertex Camera::pointToScreenSpace(Point p){

    float x =400 * (1+( p.x / (p.z)));
    float y =400 * (1+(p.y / (p.z)));

    return sf::Vertex(sf::Vector2f(x, y));

}

void Camera::drawCube(Point a){
    Cube c(a);
    c.render(this);
}




