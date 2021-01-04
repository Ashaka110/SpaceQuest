#pragma once
#include "point.h"
#include "camera.h"
class PolyAsteroid
{
    public:
		PolyAsteroid();
		void render(Camera *camera);
		void update(float delta);
		void spawn(Point pos);

		bool alive;

		Point direction;
		Point position;
	private:

};

