#include "PolyMissile.h"

PolyMissile::PolyMissile()
{
	active = false;
	lifetime = 0;
}

void PolyMissile::render(Camera * camera)
{
	


	if (active) {
		float xscale = 0.1f;
		float yscale = 0.1f;
		float zscale = 1.0f;

		sf::Color color = sf::Color(200, 0, 0);

		Point verts[8] = {
			Point(.5, .5, .5),
			Point(.5, .5,-.5),
			Point(.5,-.5, .5),
			Point(.5,-.5,-.5),
			Point(-.5, .5, .5),
			Point(-.5, .5,-.5),
			Point(-.5,-.5, .5),
			Point(-.5,-.5,-.5),
		};

		for (int i = 0; i < 8; i++)
		{
			verts[i] = Point(verts[i].x*xscale, verts[i].y*yscale, verts[i].z*zscale);
		}
		Point::Translate(verts, 8, position);

		camera->drawLine(verts[0], verts[1], color);
		camera->drawLine(verts[2], verts[3], color);
		camera->drawLine(verts[4], verts[5], color);
		camera->drawLine(verts[6], verts[7], color);

		camera->drawLine(verts[0], verts[2], color);
		camera->drawLine(verts[1], verts[3], color);
		camera->drawLine(verts[4], verts[6], color);
		camera->drawLine(verts[5], verts[7], color);

		camera->drawLine(verts[0], verts[4], color);
		camera->drawLine(verts[1], verts[5], color);
		camera->drawLine(verts[2], verts[6], color);
		camera->drawLine(verts[3], verts[7], color);

		//camera->drawLine(position, Point::add(position, direction), sf::Color(200, 0, 0));
	}
}

void PolyMissile::update(float delta)
{
	if (active) {
		position = Point::add(position, Point::scale(direction, delta*20));
		lifetime += delta;
		//if (lifetime > 1.5f) {
			//active = false;
		//}
		if (position.z < -5 || position.z > 40) {
			active = false;
		}
	}
}

void PolyMissile::launch(Point Position, Point Direction)
{
	active = true;
	lifetime = 0;
	direction = Direction;
	position = Position;
}
