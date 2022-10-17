#pragma once
#include "point.h"
#include "camera.h"
#include "PolyEnemy.h"
class PolyAsteroid : public PolyEnemy
{
    public:
		PolyAsteroid();
		void render(Camera *camera);
		void update(float delta);

		bool tryHit(Point pos);
		bool canHit(Point pos);
		int getPointValue();
		virtual bool spawnsShield();
		virtual bool spawnsHealth();

		void spawn(Point pos);

		int health;

		//Point direction;
		//Point position;
	private:
		float hitTimer;

};

