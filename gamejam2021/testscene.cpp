#include <iostream>
#include "testscene.h"
#include "PolyBarrier.h"
#include "PolyEnemyBouncer.h"
#include "PolyBoss.h"

TestScene::TestScene(){
    //std::cout << "TestScene\n";

	fireCooldown = 0;
	mousedown = false;

	//enemy[0].position = Point(0, -2, 10);

	enemySpawnCooldown = 5;
	gridtop = PolyGrid(16, 5);
	gameTimer = 0;


	startText.setString("---CLICK TO START---");
	startText.setCharacterSize(20); // in pixels, not points!
	startText.setFillColor(sf::Color::White);
	startText.setPosition(270, 380);

	pausedText.setString("---Paused---");
	pausedText.setCharacterSize(20); // in pixels, not points!
	pausedText.setFillColor(sf::Color::White);
	pausedText.setPosition(320, 380);

	versionText.setString("Version: 2.1");
	versionText.setCharacterSize(20); // in pixels, not points!
	versionText.setFillColor(sf::Color::White);
	versionText.setPosition(10, 760);

	scoreText.setString("Score: 00000000");
	scoreText.setCharacterSize(20); // in pixels, not points!
	scoreText.setFillColor(sf::Color::White);
	scoreText.setPosition(550, 10);

	highScoreText.setString("High Score: 00000000");
	highScoreText.setCharacterSize(20); // in pixels, not points!
	highScoreText.setFillColor(sf::Color::White);
	highScoreText.setPosition(500, 10);

	livesText.setString("Lives: 3");
	livesText.setCharacterSize(20); // in pixels, not points!
	livesText.setFillColor(sf::Color::White);
	livesText.setPosition(10, 760);

	gameOverText.setString("GAME OVER");
	gameOverText.setCharacterSize(20); // in pixels, not points!
	gameOverText.setFillColor(sf::Color::White);
	gameOverText.setPosition(335, 380);

	shootSound.loadFromFile("Resources/SFX_20.wav");
	confirmSound.loadFromFile("Resources/SFX_4.wav");
	deathSound.loadFromFile("Resources/SFX_3.wav");
	startupSound.loadFromFile("Resources/SFX_1.wav");
	gameMusic.loadFromFile("Resources/JDB_Wicked.wav");
	menuMusic.loadFromFile("Resources/JDB_Wicked_Reprise.wav");
	bossMusic.loadFromFile("Resources/JDB_City_of_Night.wav");
	

	music.setVolume(10);
	soundfx.setVolume(10);
	inMenu = true;

	//enemy[0].spawn(Point(0, 0, 30));
	PolyAsteroid ast;
	enemy[1] = &ast;

	for (int i = 0; i < 10; i++)
	{
		enemy[i] = new PolyEnemy();//&ast;
	}
	enemy[10] = new PolyEnemyBouncer();//&ast;
	enemy[11] = new PolyEnemyBouncer();//&ast;
	enemy[12] = new PolyEnemyBouncer();//&ast;
	enemy[13] = new PolyEnemyBouncer();//&ast;
	for (int i = 14; i < 20; i++)
	{
		enemy[i] = new PolyBarrier();//&ast;
	}
	for (int i = 20; i < 30; i++)
	{
		enemy[i] = new PolyAsteroid();//&ast;
	}
	enemy[30] = new PolyBoss(1);//&ast;
	enemy[31] = new PolyBoss(2);//&ast;

	//enemy[30]->spawn(Point(0, 0, 30));

	normalEnemySpawn = true;
	enemySpawnRate = 2;
}

void TestScene::render(Camera *camera){

	grid.render(camera);
	gridtop.render(camera);

	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		enemy[i]->render(camera);
	}

	for (int i = 0; i < PLAYER_MISSILES; i++)
	{
		playerMissiles[i].render(camera);
	}
	ship.render(camera);

	enemy[1]->render(camera);

	if (restartTimer > 0) {
		camera->drawText(gameOverText);
	}else if (inMenu) {
		camera->drawText(startText);
		camera->drawText(versionText);
		camera->drawText(highScoreText);
	}
	else {
		camera->drawText(scoreText);
		camera->drawText(livesText);
	}
	if (paused) {
		camera->drawText(pausedText);
	}
}

void TestScene::update(float delta, sf::Window* window, Camera* c) {
	if(!paused)
		gameTimer += delta;



	if (inMenu) {		//Menu

		c->position = Point(0, 0, 0);
		ship.targetPosition = Point(0, -3, 4);

		c->distortiony = 0;

		if (!window->hasFocus()) {
			music.pause();
			
		}else if (music.getStatus() != sf::Sound::Status::Playing) {
			music.setBuffer(menuMusic);
			music.play();
		}


		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && window->hasFocus()) {
			score = 0;
			lives = 5;
			gameTimer = 0;
			enemySpawnCooldown = 8;
			enemySpawnRate = 2;
			maxBounceEnemies = 2;
			music.stop();
			soundfx.setBuffer(confirmSound);
			soundfx.play();
			paused = false;
			inMenu = false;
		}
	}
	else if(restartTimer > 0){ //Game Over screen
		restartTimer -= delta;
		music.stop();
		ship.targetPosition = Point(0, -3, 0);

		float currentSpeed = grid.scrollSpeed;
		float scrollSpeedtarget = 1;
		float newSpeed = currentSpeed + (scrollSpeedtarget - currentSpeed)*delta;
		gridtop.scrollSpeed = newSpeed;
		grid.scrollSpeed = newSpeed;

		c->distortiony = c->distortiony + ( -c->distortiony)*delta * .5f;

		if (restartTimer <= 0) {
			if (score > highscore) {
				highscore = score;
			}

			for (int i = 0; i < MAX_ENEMIES; i++)
			{
				enemy[i]->alive = false;
			}

			window->setMouseCursorVisible(true);
			inMenu = true;
		}

	}
	else { //Game specific
		if (paused) {
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)) {
				if (!pausebuttonDown) {
					pausebuttonDown = true;
					window->setMouseCursorVisible(false);
					paused = false;
					if (music.getStatus() == sf::Sound::Status::Paused) {
						music.play();
					}
				}
			}
			else {
				pausebuttonDown = false;
			}
		}
		else {
			updateMovement(delta, window, c);
			updateShoot(delta);
			updateEnemySpawn(delta);


			//update Scroll speed
			float currentSpeed = grid.scrollSpeed;
			float newSpeed = currentSpeed + (scrollSpeedtarget - currentSpeed)*delta;
			gridtop.scrollSpeed = newSpeed;
			grid.scrollSpeed = newSpeed;


			if (gameTimer > 7 && !(gameTimer>80 && gameTimer< 185))
			{
				if (music.getStatus() != sf::Sound::Status::Playing) {
					music.setBuffer(gameMusic);
					music.play();
				}
				scrollSpeedtarget = 2;
			}
				
			if (gameTimer > 2 && gameTimer < 7) {
				if (music.getStatus() != sf::Sound::Status::Playing && gameTimer < 4) {
					music.setBuffer(startupSound);
					music.play();

					for (int i = 0; i < MAX_ENEMIES; i++)
					{
						enemy[i]->alive = false;
					}

				}

				scrollSpeedtarget = 12;
				//float scrollSpeed = (gameTimer - 2)*2.5 + 1;
				//gridtop.scrollSpeed = scrollSpeed;
				//grid.scrollSpeed = scrollSpeed;
			}


			//spawn defs
			normalEnemySpawn = true;
			bounceEnemySpawn = false;
			asteroidSpawn = false;
			barrierSpawn = false;

			if (gameTimer > 15 && gameTimer < 38) {
				gameTimer = 80;
			}

			if (gameTimer > 30 && gameTimer < 38) {
				normalEnemySpawn = false;
				bounceEnemySpawn = true;
			}
			if (gameTimer > 38 && gameTimer < 42) {
				bounceEnemySpawn = true;
			}

			if (gameTimer > 60 && gameTimer < 75) {
				asteroidSpawn = true;
			}


			//
			//
			//Boss 1
			if (gameTimer > 80 && gameTimer < 191) {
				normalEnemySpawn = false;
			}
			if (gameTimer > 83 && gameTimer < 85) {
				music.stop();
			}
			if (gameTimer > 85 && gameTimer < 93) {
				c->distortiony = (gameTimer - 85.0f) / 8.0f;
				scrollSpeedtarget = 12;

				if (music.getStatus() != sf::Sound::Status::Playing && gameTimer < 87) {
					music.setBuffer(startupSound);
					music.play();
				}
			}

			if (gameTimer > 95 && gameTimer < 105) {
				enemy[31]->spawn(Point(0, 0, 30));
				gameTimer = 120;

			}

			if (gameTimer > 120 && gameTimer < 125) {
				if (music.getStatus() != sf::Sound::Status::Playing) {
					music.setBuffer(bossMusic);
					music.play();
				}

				if (enemy[31]->alive) {
					gameTimer = 121;
				}
				else {
					gameTimer = 175;
				}
			}

			if (gameTimer > 175 && gameTimer < 183) {
				music.stop();
				c->distortiony = 1.0f - (gameTimer - 175.0f) / 8.0f;
				scrollSpeedtarget = 8;
			}
			//
			//
			//
			if (gameTimer > 185 && gameTimer < 225) {
				asteroidSpawn = true;
				bounceEnemySpawn = true;
				normalEnemySpawn = false;
			}

			if (gameTimer > 235 && gameTimer < 250) {
				barrierSpawn = true;
			}


			if (gameTimer > 255 && gameTimer < 260) {
				enemy[31]->spawn(Point(0, 0, 30));
				gameTimer = 265;
			}

			if (gameTimer > 260 && gameTimer < 269) {
				normalEnemySpawn = false;
				if (enemy[31]->alive) {
					gameTimer = 160;
				}
				else {
					gameTimer = 170;
				}
			}

			if (gameTimer > 270) {
				normalEnemySpawn = false;
				music.stop();
			}
			if (gameTimer > 273) {
				enemySpawnRate *= .8;
				gameTimer = 0;
				maxBounceEnemies = 4;
				lives++;
				enemySpawnCooldown = 8;
			}

			
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape) || !window->hasFocus()) {
				if (!pausebuttonDown) {
					window->setMouseCursorVisible(true);
					pausebuttonDown = true;
					paused = true;
					music.pause();
				}
			}
			else {
				pausebuttonDown = false;
			}
		}

	}

	if (!paused) {


		grid.update(delta);
		gridtop.update(delta);
		ship.update(delta);

		for (int i = 0; i < PLAYER_MISSILES; i++)
		{
			playerMissiles[i].update(delta);
			if (playerMissiles[i].active)
				for (int j = 0; j < MAX_ENEMIES; j++)
				{
					if (enemy[j]->tryHit(playerMissiles[i].position)) {
						playerMissiles[i].active = false;
						soundfx.setBuffer(deathSound);
						soundfx.play();
						score += enemy[j]->getPointValue();
					}

				}
		}

		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			enemy[i]->update(delta);
			if (ship.isAlive()) {
				if (enemy[i]->canHit(ship.position)) {
					ship.startRespawn();
					lives -= 1;
					soundfx.setBuffer(deathSound);
					soundfx.play();
					if (lives == 0) {
						restartTimer = 5;
					}
				}
			}
		}

		scoreText.setString("Score: " + std::to_string(score));
		livesText.setString("Lives: " + std::to_string(lives));
		highScoreText.setString("High Score: " + std::to_string(highscore));
	}
}

void TestScene::updateMovement(float delta, sf::Window * window, Camera* c)
{
	sf::Vector2u winsize = window->getSize();
	float halfx = (winsize.x / 2.0f);
	float halfy = (winsize.y / 2.0f);

	//window. c
	sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
	//std::cout << localPosition.x <<	" " << localPosition.y << std::endl;
	sf::Vector2i offset = localPosition - sf::Vector2i(halfx,halfy);
	sf::Mouse::setPosition(sf::Vector2i(halfx,halfy), *window);
	window->setMouseCursorVisible(false);
	float movespeed = 1.0f/50.0f;

	float posx = ship.targetPosition.x;
	posx += offset.x * movespeed;
	posx = posx < 4 ? posx>-4?posx:-4 :4;

	float posy = ship.targetPosition.y;
	posy -= offset.y * movespeed;
	posy = posy < 4 ? posy>-4?posy:-4 :4;
	//float posx = (localPosition.x - halfx)/ halfx;
	//posx = posx < 1 ? posx>-1?posx:-1 :1;
	//posx = posx * 4;

	//float posy = (-localPosition.y + halfy)/ halfy;
	//posy = posy < 1 ? posy>-1?posy:-1 :1;
	//posy = posy * 4;

	//ship.position = locak //Point::add(ship.position, Point(offset.x * delta, 0,0));

	ship.targetPosition = Point(posx, posy, 4);
	c->position = Point(-posx/2, -1+ -posy/2, 0);

}

void TestScene::updateShoot(float delta)
{
	if (fireCooldown > 0) {
		fireCooldown -= delta;
	}

	if(ship.isAlive())
	if(sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) )
    {
		if (!mousedown || fireCooldown <= 0) {
			mousedown = true;
			for (int i = 0; i < PLAYER_MISSILES; i++)
			{
				if (!playerMissiles[i].active) {
					playerMissiles[i].launch(ship.position, Point(0, 0, 1));

					fireCooldown = .5f;
					//std::cout << "Launched!" << std::endl;
					
					if (gameTimer > 1) {

					soundfx.setBuffer(shootSound);
					soundfx.setVolume(10);
					soundfx.play();
					}

					break;
				}
			}
		}
	}
	else {
		mousedown = false;
	}
}

void TestScene::updateEnemySpawn(float delta)
{
	enemySpawnCooldown -= delta;
	if (enemySpawnCooldown <= 0) {
		enemySpawnCooldown = enemySpawnRate;
		if (normalEnemySpawn) {
			for (int i = 0; i < 10; i++)//MAX_ENEMIES; i++)
			{
				if (!enemy[i]->alive) {
					enemy[i]->spawn(Point((rand() % 6) - 2.5, (rand() % 6) - 2.5, 30));
					break;
				}
			}
		}
		if (bounceEnemySpawn) {
			for (int i = 10; i < 10+maxBounceEnemies; i++)
			{
				if (!enemy[i]->alive) {
					enemy[i]->spawn(Point((rand() % 6) - 2.5, (rand() % 6) - 2.5, 30));
					break;
				}
			}
		}
		if (barrierSpawn) {
			for (int i = 14; i < 20; i++)
			{
				if (!enemy[i]->alive) {
					enemy[i]->spawn(Point((rand() % 6) - 2.5, (rand() % 6) - 2.5, 30));
					break;
				}
			}
		}
		if (asteroidSpawn) {
			for (int i = 20; i < 30; i++)
			{
				if (!enemy[i]->alive) {
					enemy[i]->spawn(Point((rand() % 6) - 2.5, (rand() % 6) - 2.5, 30));
					break;
				}
			}
		}
		if (bossSpawn) {
			for (int i = 30; i < 32; i++)
			{
				if (!enemy[i]->alive) {
					enemy[i]->spawn(Point((rand() % 6) - 2.5, (rand() % 6) - 2.5, 30));
					break;
				}
			}
		}
	}
}
