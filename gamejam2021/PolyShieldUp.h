#pragma once
#include "PolyEnemy.h"
class PolyShieldUp : public PolyEnemy
{
    public:
		PolyShieldUp();
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

