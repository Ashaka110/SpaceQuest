#pragma once
#include "point.h"
#include "camera.h"
#include "PolyEnemy.h"
class PolyBarrier : public PolyEnemy
{
    public:
		PolyBarrier();
		void render(Camera *camera);
		void update(float delta);

		bool tryHit(Point pos);
		bool canHit(Point pos);
		int getPointValue();

		virtual void spawn(Point pos);
	private:
};

