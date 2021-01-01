#include <SFML/Graphics.hpp>
#include "point.h"
#include "testscene.h"
#include "camera.h"


int main()
{
    sf::RenderWindow window(sf::VideoMode(800, 800), "SFML works!");
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

        c.update(elapsed.asSeconds());
        
        window.clear();
        t.render(&c);


        window.display();
    }

    return 0;
}
