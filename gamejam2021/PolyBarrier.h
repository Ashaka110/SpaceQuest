#pragma once
#include "point.h"
#include "camera.h"
class PolyBarrier
{
    public:
		PolyBarrier(Point position, float Angle);
		void render(Camera *camera);
		void update(float delta);

		Point position;
	private:
		float angle;
};

