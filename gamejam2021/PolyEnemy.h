#pragma once
#include "point.h"
#include "camera.h"
#include "PolyMissile.h"
class PolyEnemy
{
    public:
		PolyEnemy();
		void render(Camera *camera);
		void update(float delta);

		bool tryHit(Point pos);
		bool canHit(Point pos);
		void spawn(Point pos);

		Point position;
		Point direction;

		bool alive;
	private:
		float angle;

		float fireCooldown;

		void onDie();
		float deathTimer;
		Point shipdestroy[24];
		PolyMissile missles[5];
};

