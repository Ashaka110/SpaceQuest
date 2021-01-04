#include "PolyBarrier.h"

PolyBarrier::PolyBarrier(Point position, float Angle)
{
	this->position = position;
	angle = Angle;
}

#define NUM_VERTS 8
void PolyBarrier::render(Camera * camera)
{
	Point topverts[NUM_VERTS] = {
		Point(  1,0,  0),
		Point( .7,0, .7),
		Point(  0,0,  1),
		Point(-.7,0, .7),
		Point( -1,0,  0),
		Point(-.7,0,-.7),
		Point(  0,0, -1),
		Point( .7,0,-.7),
	};
	Point endverts[NUM_VERTS] = {
		Point(  1,0,  0),
		Point( .7,0, .7),
		Point(  0,0,  1),
		Point(-.7,0, .7),
		Point( -1,0,  0),
		Point(-.7,0,-.7),
		Point(  0,0, -1),
		Point( .7,0,-.7),
	};

	Point::Translate(topverts, 8, Point(0, 10, 10));
	Point::Translate(endverts, 8, Point(0,-10, 10));
	sf::Color color = sf::Color(200, 0, 0);

	for (int i = 0; i < NUM_VERTS; i++)
	{
		camera->drawLine(topverts[i], topverts[(i+1)%8], color);
		camera->drawLine(endverts[i], endverts[(i+1)%8], color);
		camera->drawLine(topverts[i], endverts[i], color);
	}
}

void PolyBarrier::update(float delta)
{

}
