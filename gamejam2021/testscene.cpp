#include <iostream>
#include "testscene.h"

TestScene::TestScene(){
    std::cout << "TestScene\n";

	fireCooldown = 0;
	mousedown = false;
}

void TestScene::render(Camera *camera){

	grid.render(camera);
	ship.render(camera);

	for (int i = 0; i < PLAYER_MISSILES; i++)
	{
		playerMissiles[i].render(camera);
	}
}

void TestScene::update(float delta, sf::Window* window){

	sf::Vector2i localPosition = sf::Mouse::getPosition(*window);
	std::cout << localPosition.x <<	" " << localPosition.y << std::endl;
	sf::Vector2i offset = localPosition - sf::Vector2i(400,400);
	//sf::Mouse::setPosition(sf::Vector2i(400, 400), *window);

	float posx = (localPosition.x - 400)/400.0f;
	posx = posx < 1 ? posx>-1?posx:-1 :1;
	posx = posx * 3;

	float posy = (-localPosition.y + 400)/400.0f;
	posy = posy < 1 ? posy>-1?posy:-1 :1;
	posy = posy * 3;
	//ship.position = locak //Point::add(ship.position, Point(offset.x * delta, 0,0));

	ship.position = Point(posx, posy, 4);

	if (fireCooldown > 0) {
		fireCooldown -= delta;
	}

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

	grid.update(delta);
	ship.update(delta);

	for (int i = 0; i < PLAYER_MISSILES; i++)
	{
		playerMissiles[i].update(delta);
	}
}
