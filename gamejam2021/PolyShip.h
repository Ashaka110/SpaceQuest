#pragma once

#include "point.h"
#include "camera.h"

class PolyShip
{
    public:
		PolyShip();
		void render(Camera *camera);
		void update(float delta);

		Point position;
	private:
		float angle;
};

