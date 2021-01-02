#include "PolyMissile.h"

PolyMissile::PolyMissile()
{
	active = false;
	lifetime = 0;
}

void PolyMissile::render(Camera * camera)
{
	if(active)
		camera->drawLine(position, Point::add(position, direction), sf::Color(200, 0, 0));
}

void PolyMissile::update(float delta)
{
	if (active) {
		position = Point::add(position, Point::scale(direction, delta*20));
		lifetime += delta;
		if (lifetime > 1.5f) {
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
