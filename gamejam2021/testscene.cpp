#include <iostream>
#include "testscene.h"
#include "PolyBarrier.h"

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

	versionText.setString("Version: 1.0");
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

	inMenu = true;
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
		enemy[i].render(camera);
	}

	for (int i = 0; i < PLAYER_MISSILES; i++)
	{
		playerMissiles[i].render(camera);
	}
	ship.render(camera);

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

void TestScene::update(float delta, sf::Window* window, Camera* c){

	gameTimer += delta;
	//if(gameTimer > 5)

	if (inMenu) {

		ship.targetPosition = Point(0, -3, 4);
		if (sf::Mouse::isButtonPressed(sf::Mouse::Button::Left)) {
			score = 0;
			lives = 5;
			enemySpawnCooldown = 5;
			inMenu = false;
		}
	}
	else if(restartTimer > 0){
		restartTimer -= delta;

		if (restartTimer <= 0) {
			if (score > highscore) {
				highscore = score;
			}
			inMenu = true;
		}

	}
	else {
		updateMovement(delta, window, c);
		updateShoot(delta);
		updateEnemySpawn(delta);
	}

	grid.update(delta);
	gridtop.update(delta);
	ship.update(delta);

	for (int i = 0; i < PLAYER_MISSILES; i++)
	{
		playerMissiles[i].update(delta);
		if(playerMissiles[i].active)
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			if (enemy[i].tryHit(playerMissiles[i].position)) {
				playerMissiles[i].active = false;
				score += 100;
			}

		}
	}

	for (int i = 0; i < MAX_ENEMIES; i++)
	{
		enemy[i].update(delta);
		if (ship.isAlive()) {
			if (enemy[i].canHit(ship.position)) {
				ship.startRespawn();
				lives -= 1;
				if (lives == 0) {
					restartTimer = 3;
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
		enemySpawnCooldown = 2;
		for (int i = 0; i < MAX_ENEMIES; i++)
		{
			if (!enemy[i].alive) {
				enemy[i].spawn(Point((rand() % 6) - 2.5, (rand() % 6) - 2.5, 30));
				break;
			}
		}
	}
}
