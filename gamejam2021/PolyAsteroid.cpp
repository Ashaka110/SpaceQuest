#include "PolyAsteroid.h"

PolyAsteroid::PolyAsteroid()
{
	direction = Point(0, 0, -1);
}

#define NUM_VERTS 8
void PolyAsteroid::render(Camera * camera)
{
	Point verts[32] = {
		Point(  .5, 1,  0),
		Point( .35, 1, .35),
		Point(   0, 1, .5),
		Point(-.35, 1, .35),
		Point( -.5, 1,  0),
		Point(-.35, 1,-.35),
		Point(   0, 1,-.5),
		Point( .35, 1,-.35),

		Point(  1,.5,  0),
		Point( .7,.5, .7),
		Point(  0,.5,  1),
		Point(-.7,.5, .7),
		Point( -1,.5,  0),
		Point(-.7,.5,-.7),
		Point(  0,.5, -1),
		Point( .7,.5,-.7),

		Point(  1,-.5,  0),
		Point( .7,-.5, .7),
		Point(  0,-.5,  1),
		Point(-.7,-.5, .7),
		Point( -1,-.5,  0),
		Point(-.7,-.5,-.7),
		Point(  0,-.5, -1),
		Point( .7,-.5,-.7),

		Point(  .5, -1,  0),
		Point( .35, -1, .35),
		Point(   0, -1, .5),
		Point(-.35, -1, .35),
		Point( -.5, -1,  0),
		Point(-.35, -1,-.35),
		Point(   0, -1,-.5),
		Point( .35, -1,-.35),
	};

	Point::Translate(verts, 32, position);
	sf::Color color = sf::Color(200, 0, 0);

	for (int i = 0; i < 8; i++)
	{
		camera->drawLine(verts[i], verts[(i+1)%8], color);
		camera->drawLine(verts[8+i], verts[8+(i+1)%8], color);
		camera->drawLine(verts[16+i], verts[16+(i+1)%8], color);
		camera->drawLine(verts[24 + i], verts[24 + (i+1)%8], color);

		camera->drawLine(verts[i], verts[i+8], color);
		camera->drawLine(verts[i+8], verts[i+16], color);
		camera->drawLine(verts[i+16], verts[i+24], color);
	}
}

void PolyAsteroid::update(float delta)
{
	if (alive) {
		//angle += delta;
		position = Point::add(position, Point(0, 0, -3 * delta));
		if (position.z < -5) {
			alive = false;
		}
	}
}

void PolyAsteroid::spawn(Point pos)
{
	alive = true;
	position = pos;
}
