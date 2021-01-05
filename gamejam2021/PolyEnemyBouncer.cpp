#include "PolyEnemyBouncer.h"

PolyEnemyBouncer::PolyEnemyBouncer()
{
	direction = Point(1, 1, -1);
	color = sf::Color(200,200,0);
}

void PolyEnemyBouncer::update(float delta)
{
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
		if (fireCooldown > 0) {
			fireCooldown -= delta;
		} else {
			fireCooldown = 2;

			for (int i = 0; i < 5; i++)
			{
				if (!missles[i].active) {
					missles[i].launch(position, Point(0, 0, -1));
					break;
				}
			}
		}

	}
	if (deathTimer > 0) {
		deathTimer -= delta;
		for (int i = 0; i < 12; i++)
		{
			Point a = shipdestroy[i * 2];
			Point b = shipdestroy[i * 2 + 1];

			Point center = Point::getCenter(a, b);
			Point offset = Point::scale(Point::add(center, Point::scale(position, -1)), delta * 2);
			shipdestroy[i * 2] = Point::add(a, offset);
			shipdestroy[i * 2 + 1] = Point::add(b, offset);
			shipdestroy[i * 2] = Point::RotateAroundZ(shipdestroy[i * 2], center, (delta + i * .05) * (i % 2 == 1 ? -1 : 1));
			shipdestroy[i * 2 + 1] = Point::RotateAroundZ(shipdestroy[i * 2 + 1], center, (delta + i * .05) * (i % 2 == 1 ? -1 : 1));
		}
	}

	for (int i = 0; i < 5; i++)
	{
		missles[i].update(delta);
	}

}

bool PolyEnemyBouncer::tryHit(Point pos)
{
	if (alive) {
		if (Point::sqrDistance(pos, position) < .5) {
			onDie();
			return true;
		}
	}
	return false;
}

int PolyEnemyBouncer::getPointValue()
{
	return 200;
}
