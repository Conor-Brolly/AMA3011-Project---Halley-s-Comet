#include <SFML/Graphics.hpp>
#include "EulerSolver.h"

int main()
{
    //Window initialisation
    auto window = sf::RenderWindow(sf::VideoMode({1024u, 1024u}), "AMA3011 Halley's Comet");
    window.setFramerateLimit(144);


    //Particle system
    Particle Sun = { true, 100, 256, 512, 0, 0 };
    Particle Comet = { false, 10, 768, 512, 0, 5 };

    //Display Variables
    sf::CircleShape sunCircle(Sun.mass);
    sunCircle.setOrigin({ (float)Sun.mass, (float)Sun.mass });
    sunCircle.setFillColor(sf::Color(255, 255, 0));

    sf::CircleShape cometCircle(Comet.mass);
    cometCircle.setOrigin({ (float)Comet.mass, (float)Comet.mass });
    cometCircle.setFillColor(sf::Color(0, 255, 255));
    //Main Loop
    while (window.isOpen())
    {
        while (const std::optional event = window.pollEvent())
        {
            if (event->is<sf::Event::Closed>())
            {
                window.close();
            }
        }



        window.clear();
        //Displays Sun and Comet as circles

        sunCircle.setPosition({ (float)Sun.x, (float)Sun.y });
        window.draw(sunCircle);

        cometCircle.setPosition({ (float)Comet.x, (float)Comet.y });
        window.draw(cometCircle);

        window.display();
    }
}
