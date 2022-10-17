#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "point.h"
#include "testscene.h"
#include "camera.h"


int main()
{
    int screenwidth = sf::VideoMode::getDesktopMode().width;
    int screenheigth = sf::VideoMode::getDesktopMode().height;
    int screensize = screenwidth > screenheigth ? screenheigth:screenwidth ;


    sf::RenderWindow window(sf::VideoMode(1280,720), "Space Quest");
    sf::Clock clock;

    TestScene t;
    Camera c(&window);


    while (window.isOpen())
    {

        //window.setSize(sf::Vector2u(500,500));
        //window.
        
    	sf::Time elapsed = clock.restart();	
  		sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::Resized) {
                sf::View View(sf::FloatRect(0, 0, event.size.width, event.size.height));
                window.setView(View);
            }
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
