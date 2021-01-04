#pragma once
#include "point.h"
#include "camera.h"

class PolyMissile
{
    public:
		PolyMissile();
		void render(Camera *camera);
		void update(float delta);

		void launch(Point Position, Point Direction);

		bool active;

		Point position;
	private:
		Point direction;

		float lifetime;
};

