#pragma once
#include "PolyEnemy.h"
class PolyHealthUp : public PolyEnemy
{
    public:
		PolyHealthUp();
		void render(Camera *camera);
		void update(float delta);

		bool tryHit(Point pos);
		bool canHit(Point pos);
		int getPointValue();

		void spawn(Point pos);

		int health;
		float collectionTimer;

		//Point direction;
		//Point position;
	private:
		float animationTimer;
};

