#include <SFML/Graphics.hpp>
#include <string>
#include "EulerSolver.h"
#include "RungeKuttaSolver.h"
#include "CentralFieldEqs.h"
#include "AsteroidDragEqs.h"

#define SCREEN_WIDTH 2048u
#define SCREEN_HEIGHT 1024u

void runProgram(bool asteroid, bool traces)
{
    //Window initialisation
    auto window = sf::RenderWindow(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "AMA3011 Halley's Comet");

    //DE solver
    Solver* euler = new EulerSolver();
    Solver* rungekutta = new RKSolver();

    double time = 0.0;
    double timestep = 400000.0;//(seconds)

    double initialDistance = 5.2e12;//Distance of halleys comet at apoapsis
    double ScreenScaleFactor = 0.8 * SCREEN_WIDTH / initialDistance;

    
    //Particle system
    Particle EulerComet = {Vector(initialDistance, 0), Vector(0, -910)};
    Particle RungeKComet = EulerComet;

    //Display Variables
    sf::CircleShape sunCircle(16.0f);
    sunCircle.setOrigin({ 16.0f, 16.0f });
    sunCircle.setFillColor(sf::Color(255, 255, 0));

    sf::CircleShape eulerCometCircle(10.0f);
    eulerCometCircle.setOrigin({ 10.0f, 10.0f });
    eulerCometCircle.setFillColor(sf::Color(255, 255, 255));

    sf::CircleShape rungeKCometCircle(8.0f);
    rungeKCometCircle.setOrigin({ 8.0f, 8.0f });
    rungeKCometCircle.setFillColor(sf::Color(255, 0, 255));

    sf::CircleShape asteroidCircle((float)maxAstRadius * ScreenScaleFactor);
    asteroidCircle.setOrigin({ (float)(maxAstRadius * ScreenScaleFactor), (float)(maxAstRadius * ScreenScaleFactor)});
    asteroidCircle.setOutlineThickness(-(1.0 / 3.0) * maxAstRadius * ScreenScaleFactor);
    asteroidCircle.setOutlineColor(sf::Color(255, 0, 0));
    asteroidCircle.setFillColor(sf::Color::Transparent);


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
        for (int i = 0; i < 1; i++) {

            euler->update(timestep, &EulerComet, AsteroidDrag::dxdt, AsteroidDrag::dvdt);
            rungekutta->update(timestep, &RungeKComet, AsteroidDrag::dxdt, AsteroidDrag::dvdt);
            time += timestep;

        }
        

        //___________________________Drawing to the screen___________________________
        if (!traces) {
            window.clear();
        }
         

        //Scales to screen-space from real position, using the initial maxima as scale
  
        //Sun
        sunCircle.setPosition({ (float)(0.1 * SCREEN_WIDTH), (float)(0.5 * SCREEN_HEIGHT) });
        window.draw(sunCircle);

        asteroidCircle.setPosition({ (float)(0.1 * SCREEN_WIDTH), (float)(0.5 * SCREEN_HEIGHT) });
        window.draw(asteroidCircle);


        //Comet Euler
        eulerCometCircle.setPosition({ (float)(0.1 * SCREEN_WIDTH + (EulerComet.pos.x * ScreenScaleFactor)),
                                (float)(0.5 * SCREEN_HEIGHT + (EulerComet.pos.y * ScreenScaleFactor)) });
        window.draw(eulerCometCircle);

        //Comet RungeKutta
        rungeKCometCircle.setPosition({ (float)(0.1 * SCREEN_WIDTH + (RungeKComet.pos.x * ScreenScaleFactor)),
                                (float)(0.5 * SCREEN_HEIGHT + (RungeKComet.pos.y * ScreenScaleFactor)) });
        window.draw(rungeKCometCircle);

        window.display();
        
    }
}





int main() {

    runProgram(false, true);

    return 0;
}
