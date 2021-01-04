#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "point.h"
#include "testscene.h"
#include "camera.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "Space Quest");
    sf::Clock clock;


    TestScene t;
    Camera c(&window);


    while (window.isOpen())
    {

        
    	sf::Time elapsed = clock.restart();	
  		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
        }

		float delta = elapsed.asSeconds();

        c.update(delta);
        
        window.clear();
        t.render(&c);
		t.update(delta, &window, &c);

        window.display();
    }

    return 0;
}
