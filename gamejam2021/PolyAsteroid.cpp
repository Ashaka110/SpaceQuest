#include "PolyAsteroid.h"

PolyAsteroid::PolyAsteroid()
{
	direction = Point(.1, .1, -3);
	color = sf::Color(200,100,0);
	hitTimer = 0;
}

void PolyAsteroid::spawn(Point pos)
{
	health = 8;
	alive = true;
	position = pos;
}

#define NUM_VERTS 8
void PolyAsteroid::render(Camera * camera)
{
	if (hitTimer > 0) {
		color = sf::Color(200, 0, 0);
	} else {
		color = sf::Color(200,100,0);
	}
	if (alive) {
		Point verts[32] = {
			Point(.5, 1,  0),
			Point(.35, 1, .35),
			Point(0, 1, .5),
			Point(-.35, 1, .35),
			Point(-.5, 1,  0),
			Point(-.35, 1,-.35),
			Point(0, 1,-.5),
			Point(.35, 1,-.35),

			Point(1,.5,  0),
			Point(.7,.5, .7),
			Point(0,.5,  1),
			Point(-.7,.5, .7),
			Point(-1,.5,  0),
			Point(-.7,.5,-.7),
			Point(0,.5, -1),
			Point(.7,.5,-.7),

			Point(1,-.5,  0),
			Point(.7,-.5, .7),
			Point(0,-.5,  1),
			Point(-.7,-.5, .7),
			Point(-1,-.5,  0),
			Point(-.7,-.5,-.7),
			Point(0,-.5, -1),
			Point(.7,-.5,-.7),

			Point(.5, -1,  0),
			Point(.35, -1, .35),
			Point(0, -1, .5),
			Point(-.35, -1, .35),
			Point(-.5, -1,  0),
			Point(-.35, -1,-.35),
			Point(0, -1,-.5),
			Point(.35, -1,-.35),
		};

		Point::RotateZ(verts, 32, angle);
		Point::Translate(verts, 32, position);
		//sf::Color color = sf::Color(200, 100, 0);

		for (int i = 0; i < 8; i++)
		{
			camera->drawLine(verts[i], verts[(i + 1) % 8], color);
			camera->drawLine(verts[8 + i], verts[8 + (i + 1) % 8], color);
			camera->drawLine(verts[16 + i], verts[16 + (i + 1) % 8], color);
			camera->drawLine(verts[24 + i], verts[24 + (i + 1) % 8], color);

			camera->drawLine(verts[i], verts[i + 8], color);
			camera->drawLine(verts[i + 8], verts[i + 16], color);
			camera->drawLine(verts[i + 16], verts[i + 24], color);
		}
	}
}

void PolyAsteroid::update(float delta)
{
	hitTimer -= delta;
	if (alive) {
		angle += delta * 2;

		if (position.x < -3 || position.x > 3) {
			direction.x *= -1;
		}
		if (position.y < -3 || position.y > 3) {
			direction.y *= -1;
		}
		
		position = Point::add(position,Point::scale( direction, delta));

		if (position.z < -5) {
			alive = false;
		}
	}
}

bool PolyAsteroid::tryHit(Point pos)
{
	if (alive) {
		if (Point::sqrDistance(pos, position) < 2) {
			health -= 1;
			hitTimer = .1f;
			if (health <= 0) {
				alive = false;
			}

			return true;
		}
	}
	return false;
}

bool PolyAsteroid::canHit(Point pos)
{
	if (alive) {
		if (Point::sqrDistance(pos, position) < 2) {
			health -= 1;
			hitTimer = .1f;
			if (health <= 0) {
				alive = false;
			}
			return true;
		}
	}
	return false;
}

int PolyAsteroid::getPointValue()
{
	return 0;
}

bool PolyAsteroid::spawnsShield()
{
	return rand()%3 == 1;
}

bool PolyAsteroid::spawnsHealth()
{
	return rand()%50 == 1;
}

