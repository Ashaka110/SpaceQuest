#include <iostream>
#include "testscene.h"
#include "PolyBarrier.h"
#include "PolyEnemyBouncer.h"

TestScene::TestScene(){
    std::cout << "TestScene\n";

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

	versionText.setString("Version: 1.2");
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
		enemy[i] = new PolyAsteroid();//&ast;
	}
	for (int i = 20; i < 30; i++)
	{
		enemy[i] = new PolyAsteroid();//&ast;
	}
	for (int i = 30; i < 32; i++)
	{
		enemy[i] = new PolyAsteroid();//&ast;
	}
	//enemy[10]->spawn(Point(0, 0, 30));

	normalEnemySpawn = true;
	enemySpawnRate = 2;
}

void TestScene::render(Camera *camera){

	grid.render(camera);
	gridtop.render(camera);

	PolyBarrier barrier(Point(), 0);
	//PolyAsteroid ast(Point(0, 0, 10), 0);
	//barrier.render(camera);
	//ast.render(camera);

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
}

void TestScene::update(float delta, sf::Window* window, Camera* c) {

	gameTimer += delta;



	if (inMenu) {		//Menu

		c->position = Point(0, 0, 0);
		ship.targetPosition = Point(0, -3, 4);

		if (music.getStatus() != sf::Sound::Status::Playing) {
			music.setBuffer(menuMusic);
			music.play();
		}

		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left) && window->hasFocus()) {
			score = 0;
			lives = 5;
			gameTimer = 0;
			enemySpawnCooldown = 7;
			enemySpawnRate = 2;
			music.stop();
			soundfx.setBuffer(confirmSound);
			soundfx.play();
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

		if (restartTimer <= 0) {
			if (score > highscore) {
				highscore = score;
			}

			for (int i = 0; i < MAX_ENEMIES; i++)
			{
				enemy[i]->alive = false;
			}

			inMenu = true;
		}

	}
	else { //Game specific
		updateMovement(delta, window, c);
		updateShoot(delta);
		updateEnemySpawn(delta);

		if (gameTimer > 6)
		{
			if (music.getStatus() != sf::Sound::Status::Playing) {
				music.setBuffer(gameMusic);
				music.play();

			}
				float currentSpeed = grid.scrollSpeed;
				float scrollSpeedtarget = 2;
				float newSpeed = currentSpeed + (scrollSpeedtarget - currentSpeed)*delta;
				gridtop.scrollSpeed = newSpeed;
				grid.scrollSpeed = newSpeed;
		}
		else if (gameTimer > 2) {
			if (music.getStatus() != sf::Sound::Status::Playing && gameTimer < 4) {
				music.setBuffer(startupSound);
				music.play();

				for (int i = 0; i < MAX_ENEMIES; i++)
				{
					enemy[i]->alive = false;
				}

			}

			float scrollSpeed = (gameTimer-2)*2.5 + 1;
			gridtop.scrollSpeed = scrollSpeed;
			grid.scrollSpeed = scrollSpeed;
		}

		//spawn defs
		normalEnemySpawn = true;
		bounceEnemySpawn = false;
		asteroidSpawn = false;


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

		if (gameTimer > 90 && gameTimer < 125) {
			asteroidSpawn = true;
			bounceEnemySpawn = true;
			normalEnemySpawn = false;
		}

		if (gameTimer > 135 && gameTimer < 150) {
			barrierSpawn = true;
		}

		if (gameTimer > 160) {
			normalEnemySpawn = false;
		}
		if (gameTimer > 165) {
			gameTimer = 0;
			lives++;
			music.stop();
			enemySpawnRate *= .8;
			enemySpawnCooldown = 7;
		}

	}

	grid.update(delta);
	gridtop.update(delta);
	ship.update(delta);

	for (int i = 0; i < PLAYER_MISSILES; i++)
	{
		playerMissiles[i].update(delta);
		if(playerMissiles[i].active)
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

	scoreText.setString("Score: " + std::to_string( score));
	livesText.setString("Lives: " + std::to_string( lives));
    highScoreText.setString("High Score: " + std::to_string( highscore));
}

void TestScene::updateMovement(float delta, sf::Window * window, Camera* c)
{
	//window. c
	sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
	std::cout << localPosition.x <<	" " << localPosition.y << std::endl;
	sf::Vector2i offset = localPosition - sf::Vector2i(400,400);
	//sf::Mouse::setPosition(sf::Vector2i(400, 400), *window);


	float posx = (localPosition.x - 400)/400.0f;
	posx = posx < 1 ? posx>-1?posx:-1 :1;
	posx = posx * 4;

	float posy = (-localPosition.y + 400)/400.0f;
	posy = posy < 1 ? posy>-1?posy:-1 :1;
	posy = posy * 4;
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
					std::cout << "Launched!" << std::endl;
					
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
			for (int i = 10; i < 14; i++)
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
