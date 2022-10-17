#pragma once
#include "point.h"
#include "camera.h"
#include "PolyMissile.h"
#include "PolyEnemy.h"
class PolyBoss : public PolyEnemy
{
    public:
		PolyBoss(int level);
		void render(Camera *camera);
		void update(float delta);

		virtual int getPointValue();
		virtual bool spawnsShield();
		virtual bool spawnsHealth();

		bool tryHit(Point pos);
		bool canHit(Point pos);

		void spawn(Point pos);
protected:
		void onDie();
	private:

		float spawntimer;
		float hitTimer;
		void fire(Point direction);
		int health;
		PolyMissile bmissles[40];
		bool hit;
		int level;
};

