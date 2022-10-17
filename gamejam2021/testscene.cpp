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

	pausedText.setString("---Paused---");
	pausedText.setCharacterSize(20); // in pixels, not points!
	pausedText.setFillColor(sf::Color::White);

	versionText.setString("Version: 2.4");
	versionText.setCharacterSize(20); // in pixels, not points!
	versionText.setFillColor(sf::Color::White);

	scoreText.setString("Score: 00000000");
	scoreText.setCharacterSize(20); // in pixels, not points!
	scoreText.setFillColor(sf::Color::White);

	highScoreText.setString("High Score: 00000000");
	highScoreText.setCharacterSize(20); // in pixels, not points!
	highScoreText.setFillColor(sf::Color::White);

	livesText.setString("Lives: 3");
	livesText.setCharacterSize(20); // in pixels, not points!
	livesText.setFillColor(sf::Color::White);

	gameOverText.setString("GAME OVER");
	gameOverText.setCharacterSize(20); // in pixels, not points!
	gameOverText.setFillColor(sf::Color::White);

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

	for (int i = 0; i < MAX_POWERUPS; i++)
	{
		HealthUp[i] = new PolyHealthUp();
		ShieldUp[i] = new PolyShieldUp();
	}

}

void TestScene::render(Camera *camera){

	updateUIPositions(camera);

	grid.render(camera);
	gridtop.render(camera);

	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		enemy[i]->render(camera);
	}
	for (int i = 0; i < MAX_POWERUPS; i++)
	{
		HealthUp[i]->render(camera);
		ShieldUp[i]->render(camera);
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

void TestScene::updateUIPositions(Camera *camera)
{
    sf::Vector2u size = camera->window->getSize();

    int offset = ((int)size.x - (int)size.y) / 2;
    int xoffset = offset > 0? offset:0;
    int yoffset = offset < 0? -offset:0;
    int boxsize = size.x > size.y ? size.y : size.x;

	startText.setPosition(size.x/2 - 130, size.y/2 - 20);
	pausedText.setPosition(size.x/2 - 80, size.y/2 - 20);
	gameOverText.setPosition(size.x/2 - 65, size.y/2 - 20);

	versionText.setPosition(xoffset + 10, yoffset + boxsize - 40);
	livesText.setPosition(xoffset + 10, yoffset + boxsize - 40);

	scoreText.setPosition(xoffset + boxsize - 250,yoffset + 10);
	highScoreText.setPosition(xoffset + boxsize - 300, yoffset + 10);
}

void TestScene::update(float delta, sf::Window* window, Camera* c) {
	if(!paused)
		gameTimer += delta;



	if (inMenu) {		//Menu

		c->position = Point(0, 0, 0);
		ship.targetPosition = Point(0, -3, 4);
		ship.hasShield = false;

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
			if (sf::Keyboard::isKeyPressed(sf::Keyboard::Escape)&& window->hasFocus()) {
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


			if (gameTimer > 7 && !(gameTimer>80 && gameTimer< 180) && !(gameTimer>280 && gameTimer< 380))
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

					//ship.hasShield = true;
					//ship.shieldSpawnTimer = 3;
					for (int i = 0; i < MAX_ENEMIES; i++)
					{
						enemy[i]->alive = false;
					}

				}

				//gameTimer = 80;
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

			if (gameTimer > 8 && gameTimer < 9) {
				//HealthUp[0]->spawn(Point(0, 0, 15));
			}

			if (gameTimer > 15 && gameTimer < 38) {
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
			if (gameTimer > 85 && gameTimer < 90) {
				c->distortiony = (gameTimer - 85.0f) / 8.0f;
				scrollSpeedtarget = 12;

				if (music.getStatus() != sf::Sound::Status::Playing && gameTimer < 87) {
					music.setBuffer(startupSound);
					music.play();
				}
			}

			if (gameTimer > 90 && gameTimer < 105) {
				enemy[30]->spawn(Point(0, 0, 30));
				gameTimer = 120;

			}

			if (gameTimer > 120 && gameTimer < 125) {
				if (music.getStatus() != sf::Sound::Status::Playing) {
					music.setBuffer(bossMusic);
					music.play();
				}

				if (enemy[30]->alive) {
					gameTimer = 121;
				}
				else {
					gameTimer = 165;
				}
			}

			if (gameTimer > 165 && gameTimer < 174) {
				music.stop();
				scrollSpeedtarget = 4;
			}

			if (gameTimer > 165 && gameTimer < 166) {
				ShieldUp[2]->spawn(Point(2, 0, 25));
				HealthUp[2]->spawn(Point(-2, 0, 25));
			}

			if (gameTimer > 175 && gameTimer < 180) {
				c->distortiony = 1.0f - (gameTimer - 172.0f) / 8.0f;
				scrollSpeedtarget = 12;

				if (music.getStatus() != sf::Sound::Status::Playing && gameTimer < 176) {
					music.setBuffer(startupSound);
					music.play();
				}
			}
			//
			//
			//
			if (gameTimer > 180 && gameTimer < 225) {
				asteroidSpawn = true;
				bounceEnemySpawn = true;
				normalEnemySpawn = false;
			}

			if (gameTimer > 235 && gameTimer < 250) {
				barrierSpawn = true;
			}


//////

			if (gameTimer > 280 && gameTimer < 391) {
				normalEnemySpawn = false;
			}
			if (gameTimer > 283 && gameTimer < 285) {
				music.stop();
			}
			if (gameTimer > 285 && gameTimer < 290) {
				c->distortiony = -((gameTimer - 285.0f) / 8.0f);
				scrollSpeedtarget = 12;

				if (music.getStatus() != sf::Sound::Status::Playing && gameTimer < 287) {
					music.setBuffer(startupSound);
					music.play();
				}
			}

			if (gameTimer > 290 && gameTimer < 305) {
				enemy[31]->spawn(Point(0, 0, 30));
				gameTimer = 320;

			}

			if (gameTimer > 320 && gameTimer < 325) {
				if (music.getStatus() != sf::Sound::Status::Playing) {
					music.setBuffer(bossMusic);
					music.play();
				}

				if (enemy[31]->alive) {
					gameTimer = 321;
				}
				else {
					gameTimer = 365;
				}
			}

			if (gameTimer > 365 && gameTimer < 374) {
				music.stop();
				scrollSpeedtarget = 4;
			}
			if (gameTimer > 365 && gameTimer < 366) {
				HealthUp[0]->spawn(Point(2, 0, 25));
				HealthUp[1]->spawn(Point(-2, 0, 25));
			}

			if (gameTimer > 375 && gameTimer < 380) {
				c->distortiony = -(1.0f - (gameTimer - 372.0f) / 8.0f);
				scrollSpeedtarget = 12;

				if (music.getStatus() != sf::Sound::Status::Playing && gameTimer < 376) {
					music.setBuffer(startupSound);
					music.play();
				}
			}
			if (gameTimer > 380) {
				enemySpawnRate *= .8;
				gameTimer = 7;
				maxBounceEnemies = 4;
				//lives++;
				enemySpawnCooldown = 8;
			}


//////
/*
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

*/
			
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

						if (!enemy[j]->alive) {

							if (enemy[j]->spawnsShield()) {
								for (int k = 0; k < MAX_POWERUPS; k++)
								{
									if (!ShieldUp[k]->alive) {
										ShieldUp[k]->spawn(enemy[j]->position);
										break;
									}
								}
							}else if (enemy[j]->spawnsHealth()) {
								for (int k = 0; k < MAX_POWERUPS; k++)
								{
									if (!HealthUp[k]->alive) {
										HealthUp[k]->spawn(enemy[j]->position);
										break;
									}
								}
							}
						}

					}

				}
		}

		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			enemy[i]->update(delta);
			if (ship.isAlive()) {
				if (enemy[i]->canHit(ship.position)) {
					if (ship.hasShield) {
						ship.hasShield = false;
					} else {
						ship.startRespawn();
						lives -= 1;
					}
					soundfx.setBuffer(deathSound);
					soundfx.play();
					if (lives == 0) {
						restartTimer = 5;
					}
				}
			}
		}

		for (int i = 0; i < MAX_POWERUPS; i++)
		{
			HealthUp[i]->update(delta);
			if (ship.isAlive()) {
				if (HealthUp[i]->canHit(ship.position)) {
					lives++;
					HealthUp[i]->collectionTimer = 1;
					score += HealthUp[i]->getPointValue();
					soundfx.setBuffer(confirmSound);
					soundfx.play();
				}
			}
		}
		for (int i = 0; i < MAX_POWERUPS; i++)
		{
			ShieldUp[i]->update(delta);
			if (ship.isAlive()) {
				if (ShieldUp[i]->canHit(ship.position)) {
					if (!ship.hasShield) {
						ship.hasShield = true;
						ship.shieldSpawnTimer = 1;
					}
					ShieldUp[i]->collectionTimer = 1;
					score += ShieldUp[i]->getPointValue();
					soundfx.setBuffer(confirmSound);
					soundfx.play();
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
