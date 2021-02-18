#include "PolyBoss.h"

PolyBoss::PolyBoss(int level)
{
	this->level = level;
	angle = 0;
	fireCooldown = 1;
	direction = Point(1, 1.5, 0);
	position = Point(0, 0, -20);
	
}

void PolyBoss::render(Camera * camera)
{
	if (hitTimer > 0) {
		color = sf::Color(200, 0, 0);
		hit = false;
	}
	else {
		color = sf::Color(200, 200, 0);
	}

	if (deathTimer > 0) {
		for (int i = 0; i < 12; i++)
		{
			camera->drawLine(shipdestroy[i*2], shipdestroy[(i * 2)+1], color);
		}
	}

	for (int i = 0; i < 40; i++)
	{
		bmissles[i].render(camera);
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
	Point::Scale(verts, 6, 10);
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

void PolyBoss::update(float delta)
{
	hitTimer -= delta;
	if (alive) {
		if (spawntimer > .1f) {
			spawntimer -= spawntimer* delta;
			position.z = 30 + spawntimer *50;
			angle = 3.141 / 2;
		}
		else {
			if (position.x < -3 || position.x > 3) {
				direction.x *= -1;
			}
			if (position.y < -3 || position.y > 3) {
				direction.y *= -1;
			}

			position = Point::add(position, Point::scale(direction, delta));
			//position = Point(0, 0, 30);
			angle = 3.141 / 2;

			if (fireCooldown > 0) {
				fireCooldown -= delta;
			}
			else {
				fireCooldown = 1.2;

				float fireheight = ((rand() % 14) - 7) / 120.0;
				for (int i = 0; i < 10; i++)
				{
					float angle = (i / 10.0) * (3.141 / 4) - (3.141 / 8);
					fire(Point(sin(angle) / 1.5, fireheight, -cos(angle) / 1.5));
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

	for (int i = 0; i < 40; i++)
	{
		bmissles[i].update(delta);
	}
}

int PolyBoss::getPointValue()
{
	return 100;
}

bool PolyBoss::tryHit(Point pos)
{
	if (alive) {
		if (Point::sqrDistance(pos, position) < 5) {
			hit = true;
			health -= 1;
			hitTimer = .1f;
			if (health <= 0) {
				onDie();
				Point::Scale(shipdestroy, 24, 10);
			}
			return true;
		}
	}
	return false;
}

bool PolyBoss::canHit(Point pos)
{
	for (int i = 0; i < 40; i++)
	{
		if (bmissles[i].active) {
			if (Point::sqrDistance(pos, bmissles[i].position) < 1) {
				bmissles[i].active = false;
				return true;
			}
		}

	}
	if (alive) {
		if (Point::sqrDistance(pos, position) < 5) {
			hit = true;
			health -= 1;
			if (health <= 0) {
				onDie();
			}
			return true;
		}
	}

	return false;
}

void PolyBoss::spawn(Point pos)
{
	spawntimer = 5;
	alive = true;
	position = pos;
	health = 50;
	hit = false;
}

void PolyBoss::fire(Point direction)
{
	for (int i = 0; i < 40; i++)
	{
		if (!bmissles[i].active) {
			bmissles[i].launch(position, direction);
			break;
		}
	}
}

void PolyBoss::onDie()
{
	deathTimer = 5;

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
	Point::Scale(shipdestroy, 24, 10);
	Point::Translate(shipdestroy, 24, position);
}
