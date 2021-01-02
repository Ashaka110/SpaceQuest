#ifndef TESTSCENE_H
#define TESTSCENE_H

#include <SFML/Graphics.hpp>
#include "cube.h"
#include "camera.h"
#include "point.h"
#include "cubeGrid.h"
#include "PolyShip.h"
#include "PolyGrid.h"
#include "PolyMissile.h"

#define PLAYER_MISSILES 5

class TestScene{
    public:
        TestScene();
        void render(Camera *c);
		void update(float delta, sf::Window* window);



    private:
        //Cube cubes[5][5][5];
        //CubeGrid grid;
		PolyShip ship;
		PolyGrid grid;
		PolyMissile playerMissiles[PLAYER_MISSILES];

		float fireCooldown;
		bool mousedown;

};

#endif // TESTSCENE_H
