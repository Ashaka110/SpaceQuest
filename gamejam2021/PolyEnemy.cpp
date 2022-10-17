#include "PolyEnemy.h"

PolyEnemy::PolyEnemy()
{
	angle = 0;
	fireCooldown = 1;
	color = sf::Color(200, 50, 0);
}


void PolyEnemy::render(Camera * camera)
{
	if (deathTimer > 0) {
		for (int i = 0; i < 12; i++)
		{
			camera->drawLine(shipdestroy[i*2], shipdestroy[(i * 2)+1], color);
		}
	}

	for (int i = 0; i < 5; i++)
	{
		missles[i].render(camera);
	}

	// 1			2
	//
	//		 0
	//
	//		4 5
	//       
	//       3

	if (alive) {

	Point verts[6] = {
		Point(0,0,0),
		Point(-1,0,.5),
		Point(1,0,.5),
		Point(0,0,-1),
		Point(0, -.25f, -.3f),
		Point(0, .25f, -.3f)
	};

	Point::RotateZ(verts, 6, angle);
	Point::Translate(verts, 6, position);


	camera->drawLine(verts[0], verts[1], color);
	camera->drawLine(verts[0], verts[2], color);
	camera->drawLine(verts[3], verts[1], color);
	camera->drawLine(verts[3], verts[2], color);
	camera->drawLine(verts[4], verts[1], color);
	camera->drawLine(verts[4], verts[2], color);
	camera->drawLine(verts[5], verts[1], color);
	camera->drawLine(verts[5], verts[2], color);
	camera->drawLine(verts[0], verts[4], color);
	camera->drawLine(verts[0], verts[5], color);
	camera->drawLine(verts[3], verts[4], color);
	camera->drawLine(verts[3], verts[5], color);
	}
}

void PolyEnemy::update(float delta)
{
	if (alive) {
		angle += delta;
		position = Point::add(position, Point(0, 0, -6 * delta));
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
			Point offset = Point::scale(Point::add(center, Point::scale(position, -1)), delta * 3);
			shipdestroy[i * 2] = Point::add(a, offset);
			shipdestroy[i * 2 + 1] = Point::add(b, offset);
			shipdestroy[i * 2] = Point::RotateAroundZ(shipdestroy[i * 2], center, .3f* (delta + i * .05) * (i % 2 == 1 ? -1 : 1));
			shipdestroy[i * 2 + 1] = Point::RotateAroundZ(shipdestroy[i * 2 + 1], center, .3f*(delta + i * .05) * (i % 2 == 1 ? -1 : 1));
		}
	}

	for (int i = 0; i < 5; i++)
	{
		missles[i].update(delta);
	}

}

bool PolyEnemy::tryHit(Point pos)
{
	if (alive) {
		if (Point::sqrDistance(pos, position) < .5) {
			onDie();
			return true;
		}
	}
	return false;
}

bool PolyEnemy::canHit(Point pos)
{
	for (int i = 0; i < 5; i++)
	{
		if (missles[i].active) {
			if (Point::sqrDistance(pos, missles[i].position) < 1) {
				missles[i].active = false;
				return true;
			}
		}

	}
	if (alive) {
		if (Point::sqrDistance(pos, position) < 1) {
			onDie();
			return true;
		}
	}

	return false;
}

bool PolyEnemy::spawnsShield()
{
	return rand()%15 == 1;
}

bool PolyEnemy::spawnsHealth()
{
	return rand()%200 == 1;
}

int PolyEnemy::getPointValue()
{
	return 100;
}



void PolyEnemy::spawn(Point pos)
{
	alive = true;
	position = pos;
}

void PolyEnemy::onDie()
{
	deathTimer = .6;

	alive = false;

	shipdestroy[0] = Point(0, 0, 0);	//0
	shipdestroy[1] = Point(-1, 0, .5);    //1
	shipdestroy[2] = Point(0, 0, 0);	//0
	shipdestroy[3] = Point(1, 0, .5);    //2
	shipdestroy[4] = Point(0, 0, -1);    //3
		void onDie();
	shipdestroy[5] = Point(-1, 0, .5);    //1
	shipdestroy[6] = Point(0, 0, -1);    //3
	shipdestroy[7] = Point(1, 0, .5);    //2

	shipdestroy[8] = Point(0, -.25f, -.3f);    //4
	shipdestroy[9] = Point(-1, 0, .5);    //1
	shipdestroy[10] = Point(0, -.25f, -.3f);    //4
	shipdestroy[11] = Point(1, 0, .5);    //2
	shipdestroy[12] = Point(0, .25f, -.3f);    //5
	shipdestroy[13] = Point(-1, 0, .5);    //1
	shipdestroy[14] = Point(0, .25f, -.3f);    //5
	shipdestroy[15] = Point(1, 0, .5);    //2

	shipdestroy[16] = Point(0, 0, 0);	//0
	shipdestroy[17] = Point(0, -.25f, -.3f);    //4
	shipdestroy[18] = Point(0, 0, 0);	//0
	shipdestroy[19] = Point(0, .25f, -.3f);    //5
	shipdestroy[20] = Point(0, 0, -1);    //3
	shipdestroy[21] = Point(0, -.25f, -.3f);    //4
	shipdestroy[22] = Point(0, 0, -1);    //3
	shipdestroy[23] = Point(0, .25f, -.3f);    //5

	Point::RotateZ(shipdestroy, 24, angle  + 3.141/2);
	Point::Translate(shipdestroy, 24, position);
}


