#include <SFML/Graphics.hpp>
#include "EulerSolver.h"

int main()
{
    //Window initialisation
    auto window = sf::RenderWindow(sf::VideoMode({1024u, 1024u}), "AMA3011 Halley's Comet");
    window.setFramerateLimit(144);

    //DE solver
    Solver* euler = new EulerSolver();

    //Particle system
    Particle Sun = { true, 10000000000, 512, 512, 0, 0 };
    Particle Comet = { false, 10000000, 768, 512, 0, 5 };

    //Display Variables
    sf::CircleShape sunCircle(100.0f);
    sunCircle.setOrigin({ 100.0f, 100.0f });
    sunCircle.setFillColor(sf::Color(255, 255, 0));

    sf::CircleShape cometCircle(10.0f);
    cometCircle.setOrigin({ 10.0f, 10.0f });
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

        //Updates positions and velocities
        euler->update(&Sun, &Comet, 0.01);

        window.clear();
        //Displays Sun and Comet as circles

        sunCircle.setPosition({ (float)Sun.x, (float)Sun.y });
        window.draw(sunCircle);

        cometCircle.setPosition({ (float)Comet.x, (float)Comet.y });
        window.draw(cometCircle);

        window.display();
    }
}
