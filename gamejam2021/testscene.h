#ifndef TESTSCENE_H
#define TESTSCENE_H

#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
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
#define MAX_ENEMIES 32

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
		sf::Text pausedText;

		sf::SoundBuffer menuMusic;
		sf::SoundBuffer gameMusic;
		sf::SoundBuffer bossMusic;
		sf::SoundBuffer shootSound;
		sf::SoundBuffer deathSound;
		sf::SoundBuffer startupSound;
		sf::SoundBuffer confirmSound;

		sf::Sound music;
		sf::Sound soundfx;

		void updateMovement(float delta, sf::Window* window, Camera *c);
		void updateShoot(float delta);
		void updateEnemySpawn(float delta);

        //Cube cubes[5][5][5];
        //CubeGrid grid;
		PolyShip ship;
		PolyGrid grid;
		PolyGrid gridtop;
		PolyMissile playerMissiles[PLAYER_MISSILES];
		PolyEnemy* enemy[MAX_ENEMIES];
		//PolyAsteroid asteroids[MAX_ENEMIES];

		float gameTimer;
		float fireCooldown;
		float restartTimer;
		bool mousedown;

		float enemySpawnCooldown;
		float enemySpawnRate;

		float scrollSpeedtarget = 1;

		bool pausebuttonDown;
		bool paused;
		bool inMenu;
		int score;
		int highscore;
		int lives;

		bool normalEnemySpawn;
		bool bounceEnemySpawn;
		int maxBounceEnemies;
		bool asteroidSpawn;
		bool barrierSpawn;
		bool bossSpawn;
};

#endif // TESTSCENE_H
