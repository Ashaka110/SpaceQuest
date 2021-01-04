#pragma once

#include "point.h"
#include "camera.h"

class PolyShip
{
    public:
		PolyShip();
		void render(Camera *camera);
		void update(float delta);

		bool isAlive();

		void startRespawn();

		Point targetPosition;
		Point position;
	private:
		float angle;
		float targetAngle;

		float respawnTimer;
		bool visible;

		Point shipdestroy[24];
};

