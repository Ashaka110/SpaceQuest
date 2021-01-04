#pragma once
#include "point.h"
#include "camera.h"
#include "PolyMissile.h"
class PolyBoss
{
    public:
		PolyBoss();
		void render(Camera *camera);
		void update(float delta);

		Point position;

	private:
		bool active;

		PolyMissile missles[40];
};

