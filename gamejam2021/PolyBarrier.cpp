#include "PolyBarrier.h"

PolyBarrier::PolyBarrier()
{
	direction = Point(0, 0, -3);
	color = sf::Color(200,0,200);
	alive = false;
}

#define NUM_VERTS 8
void PolyBarrier::render(Camera * camera)
{
	if (alive) {
		float colorProgress = ((30 - position.z) * 200)/15;
		colorProgress = colorProgress > 200 ? 200 : colorProgress;

		color = sf::Color(colorProgress, 0, colorProgress);

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


	Point::Scale(topverts, 8, .25);
	Point::Scale(endverts, 8, .25);
	Point::Translate(topverts, 8, Point(0, 10, 0));
	Point::Translate(endverts, 8, Point(0,-10, 0));
	Point::RotateZ(topverts, 8, angle);
	Point::RotateZ(endverts, 8, angle);
	Point::Translate(topverts, 8, position);
	Point::Translate(endverts, 8, position);

	for (int i = 0; i < NUM_VERTS; i++)
	{
		camera->drawLine(topverts[i], topverts[(i+1)%8], color);
		camera->drawLine(endverts[i], endverts[(i+1)%8], color);
		camera->drawLine(topverts[i], endverts[i], color);
	}
	}
}

void PolyBarrier::update(float delta)
{
	if (alive) {
		
		position = Point::add(position,Point::scale( direction, delta));

		if (position.z < -10) {
			alive = false;
		}
		//position = Point(0, 0, 10);
		angle += delta/2;
	}
}

bool PolyBarrier::tryHit(Point pos)
{
	if (alive) {
	//Point diff = Point::add(pos, Point::scale(position, -1));
	Point rot = Point::RotateAroundZ(pos, position, angle);
	float dist = Point::sqrDistance(Point(rot.x, 0, rot.z), Point(position.x, 0, position.z));
	return dist < .5;
	}
	return false;
}

bool PolyBarrier::canHit(Point pos)
{
	if (alive) {
	Point rot = Point::RotateAroundZ(pos, position, angle);
	float dist = Point::sqrDistance(Point(rot.x, 0, rot.z), Point(position.x, 0, position.z));
	return dist < .5;
	}
	return false;
}

int PolyBarrier::getPointValue()
{
	return 0;
}

void PolyBarrier::spawn(Point pos)
{
	alive = true;
	position = pos;
	angle = rand();
}
