#include <SFML/Graphics.hpp>
#include "EulerSolver.h"
#include "RungeKuttaSolver.h"
#include "CentralFieldEqs.h"
#include "AsteroidDragEqs.h"
#include "AsteroidDeflectEqs.h"

#define SCREEN_WIDTH 2048u
#define SCREEN_HEIGHT 1024u

void runProgram(bool asteroid, bool traces, Vector(*dxdt)(Vector, Vector), Vector(*dvdt)(Vector, Vector))
{
    //Window initialisation
    auto window = sf::RenderWindow(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "AMA3011 Halley's Comet");

    //DE solver
    Solver* euler = new EulerSolver();
    Solver* rungekutta = new RKSolver();

    double time = 0.0;
    double timestep = 80000.0;//(seconds)

    double initialDistance = 5.25687e12;//Distance of halleys comet at apoapsis
    double ScreenScaleFactor = 0.8 * SCREEN_WIDTH / initialDistance;

    
    //Particle system
    Particle EulerComet = {Vector(initialDistance, 0), Vector(0, -900)};
    Particle RungeKComet = EulerComet;

    //Display Variables
    sf::CircleShape sunCircle(16.0f);
    sunCircle.setOrigin({ 16.0f, 16.0f });
    sunCircle.setFillColor(sf::Color(255, 255, 0));

    sf::CircleShape eulerCometCircle(4.0f);
    eulerCometCircle.setOrigin({ 4.0f, 4.0f });
    eulerCometCircle.setFillColor(sf::Color(255, 255, 255));

    sf::CircleShape rungeKCometCircle(4.0f);
    rungeKCometCircle.setOrigin({ 4.0f, 4.0f });
    rungeKCometCircle.setFillColor(sf::Color(255, 255, 255));

    sf::CircleShape asteroidCircle((float)maxAstRadius * ScreenScaleFactor);
    asteroidCircle.setOrigin({ (float)(maxAstRadius * ScreenScaleFactor), (float)(maxAstRadius * ScreenScaleFactor)});
    asteroidCircle.setOutlineThickness(-(1.0 / 3.0) * maxAstRadius * ScreenScaleFactor);
    asteroidCircle.setOutlineColor(sf::Color(255, 0, 0));
    asteroidCircle.setFillColor(sf::Color::Transparent);

    //Draws sun and asteroid as background

    //Sun
    sunCircle.setPosition({ (float)(0.1 * SCREEN_WIDTH), (float)(0.5 * SCREEN_HEIGHT) });
    
    //Asteroid
    asteroidCircle.setPosition({ (float)(0.1 * SCREEN_WIDTH), (float)(0.5 * SCREEN_HEIGHT) });

    //'Hack' to have comets leave a trace. This method should not be used in a more complex program
    if (traces) {
        window.draw(sunCircle);
        if (asteroid) window.draw(asteroidCircle);
        window.display();
        window.draw(sunCircle);
        if (asteroid) window.draw(asteroidCircle);
        window.display();
    }
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

        //Used for recording full revolutions
        bool positiveYBefore = RungeKComet.pos.y > 0;
        //Updates positions and velocities
        for (int i = 0; i < 1; i++) {

            euler->update(timestep, &EulerComet, dxdt, dvdt);
            rungekutta->update(timestep, &RungeKComet, dxdt, dvdt);
            time += timestep;

        }
        //Records time for one revolution (when pos.y changes from negative to positive)
        if (positiveYBefore && RungeKComet.pos.y <= 0) {
            //Exact frame of one full orbit. Present data here
            std::cout << "Orbit complete in " << time / 3.154e7 << " years. " << std::endl;
            time = 0.0;
        }

        //___________________________Drawing to the screen___________________________ 

        if (!traces) {
            window.clear(sf::Color::Black);
            window.draw(sunCircle);
            if (asteroid) window.draw(asteroidCircle);
        }
        
        //Scales to screen-space from real position, using the initial maxima as scale

        //Comet Euler
        eulerCometCircle.setPosition({ (float)(0.1 * SCREEN_WIDTH + (EulerComet.pos.x * ScreenScaleFactor)),
                                (float)(0.5 * SCREEN_HEIGHT + (EulerComet.pos.y * ScreenScaleFactor)) });
        //window.draw(eulerCometCircle);

        //Comet RungeKutta
        rungeKCometCircle.setPosition({ (float)(0.1 * SCREEN_WIDTH + (RungeKComet.pos.x * ScreenScaleFactor)),
                                (float)(0.5 * SCREEN_HEIGHT + (RungeKComet.pos.y * ScreenScaleFactor)) });
        window.draw(rungeKCometCircle);

        window.display();
        
    }
}





int main() {

    runProgram(false, true, CentralField::dxdt, CentralField::dvdt);

    return 0;
}
