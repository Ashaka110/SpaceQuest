#pragma once
#include "point.h"
#include "camera.h"
#include "PolyEnemy.h"
class PolyEnemyBouncer : public PolyEnemy
{
    public:
		PolyEnemyBouncer();
		void update(float delta);
		int getPointValue();
		bool tryHit(Point pos);

		//Point direction;
		//Point position;
	private:

};

