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
		bool hasShield;

		float shieldSpawnTimer;
		Point targetPosition;
		Point position;
		Point shieldPosition;
	private:
		float angle;
		float targetAngle;

		float shieldAngle;
		float shieldTimer;


		float respawnTimer;
		bool visible;

		Point shipdestroy[24];
};

