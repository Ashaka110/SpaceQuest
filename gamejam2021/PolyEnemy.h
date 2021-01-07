#pragma once
#include "point.h"
#include "camera.h"
#include "PolyMissile.h"
class PolyEnemy
{
    public:
		PolyEnemy();
		virtual void render(Camera *camera);
		virtual void update(float delta);

		virtual bool tryHit(Point pos);
		virtual bool canHit(Point pos);

		virtual int getPointValue();

		virtual void spawn(Point pos);

		Point position;
		Point direction;

		bool alive;
	protected:
		float angle;
		sf::Color color;
		Point shipdestroy[24];
		PolyMissile missles[5];
		float fireCooldown;

		float deathTimer;
		virtual void onDie();
	private:


};

