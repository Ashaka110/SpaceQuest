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
#include "PolyEnemy.h"
#include "PolyAsteroid.h"

#define PLAYER_MISSILES 5
#define MAX_ENEMIES 20

class TestScene{
    public:
        TestScene();
        void render(Camera *c);
		void update(float delta, sf::Window* window, Camera *c);

    private:
		sf::Text startText;
		sf::Text versionText;
		sf::Text scoreText;
		sf::Text highScoreText;
		sf::Text livesText;
		sf::Text gameOverText;

		void updateMovement(float delta, sf::Window* window, Camera *c);
		void updateShoot(float delta);
		void updateEnemySpawn(float delta);

        //Cube cubes[5][5][5];
        //CubeGrid grid;
		PolyShip ship;
		PolyGrid grid;
		PolyGrid gridtop;
		PolyMissile playerMissiles[PLAYER_MISSILES];
		PolyEnemy enemy[MAX_ENEMIES];
		//PolyAsteroid asteroids[MAX_ENEMIES];

		float gameTimer;
		float fireCooldown;
		float restartTimer;
		bool mousedown;

		float enemySpawnCooldown;

		bool inMenu;
		int score;
		int highscore;
		int lives;

};

#endif // TESTSCENE_H
