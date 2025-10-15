#include <SFML/Graphics.hpp>
#include <string>
#include "EulerSolver.h"
#include "RungeKuttaSolver.h"

#define SCREEN_WIDTH 2048u
#define SCREEN_HEIGHT 1024u

std::string displayData(Particle Sun, Particle Comet, double time) {
    std::string output = "";

    output += "Time (years):\t" + std::to_string(time / 3.16e7);

    double speed = sqrt(pow(Comet.vel.x, 2) + pow(Comet.vel.y, 2));
    output += "\nSpeed (m/s^):\t" + std::to_string(speed);

    double distance = sqrt(pow(Comet.pos.x - Sun.pos.x, 2) + pow(Comet.pos.y - Sun.pos.y, 2));
    output += "\nDistance (km):\t" + std::to_string(distance/1000);

    return output;
}

void runProgram(bool asteroid, bool traces)
{
    //Window initialisation
    auto window = sf::RenderWindow(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "AMA3011 Halley's Comet");
    //window.setFramerateLimit(144);

    //DE solver
    Solver* euler = new EulerSolver();
    Solver* rk = new RKSolver();
    double time = 0.0;
    double timestep = 8000.0;//(seconds)

    double initialDistance = 5.2e12;//Distance of halleys comet at apoapsis

    //Asteroid field
    double minDistance = 4.0e11;
    double maxDistance = 6.0e11;
    //This scales to a min and max radius by SCREENWIDTH/initialDistance
    double minAstRadius = (0.7 * SCREEN_WIDTH / initialDistance) * minDistance;
    double maxAstRadius = (0.7 * SCREEN_WIDTH / initialDistance) * maxDistance;

    
    //Particle system
    Particle Sun = { 1.988e30, Vector(0, 0), Vector(0, 0) };//Mass of sun: 1.998 * 10^30
    Particle RKComet = { 2.2e14, Vector(initialDistance, 0), Vector(0, -910)};//Mass of halleys comet: 2.2 * 10^14
    Particle EulerComet = RKComet;

    //Display Variables
    sf::CircleShape sunCircle(16.0f);
    sunCircle.setOrigin({ 16.0f, 16.0f });
    sunCircle.setFillColor(sf::Color(255, 255, 0));

    sf::CircleShape RKcometCircle(8.0f);
    RKcometCircle.setOrigin({ 8.0f, 8.0f });
    RKcometCircle.setFillColor(sf::Color(0, 255, 255));

    sf::CircleShape EulercometCircle(8.0f);
    EulercometCircle.setOrigin({ 8.0f, 8.0f });
    EulercometCircle.setFillColor(sf::Color(255, 0, 255));

    //Asteroid feild is a thin band with fixed width around the sun

    sf::CircleShape astCircle((float)maxAstRadius);
    astCircle.setOrigin({ (float)maxAstRadius, (float)maxAstRadius });
    astCircle.setOutlineThickness(-maxAstRadius / 3);
    astCircle.setFillColor(sf::Color::Transparent);
    astCircle.setOutlineColor(sf::Color(255, 255, 0));


    sf::Font font;
    if (!font.openFromFile("Fonts/ARLRDBD.ttf"))//Requires Font folder stored in exe build folder
    {
        window.close();
    }
    sf::Text textData(font);
    textData.setCharacterSize(32);
    textData.setFillColor(sf::Color(255, 255, 255));


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
        for (int i = 0; i < 10; i++) {

            if (asteroid) {
                euler->updateAsteroid(&Sun, &EulerComet, minDistance, maxDistance, timestep);
                rk->updateAsteroid(&Sun, &RKComet, minDistance, maxDistance, timestep);
            }
            else {
                rk->update(&Sun, &RKComet, timestep);
                euler->update(&Sun, &EulerComet, timestep);
            }
            time += timestep;
        }
        
        bool inAsteroid = true;
        if (EulerComet.pos.mag() < minDistance) inAsteroid = false;
        if (EulerComet.pos.mag() > maxDistance) inAsteroid = false;
        //Show this as asteroid field
        if (inAsteroid) astCircle.setOutlineColor(sf::Color(255, 255, 255));
        else astCircle.setOutlineColor(sf::Color(255, 0, 0));

        //___________________________Drawing to the screen___________________________
        if (!traces) {
            window.clear();
        }
         

        //Scales to screen-space from real position, using the initial maxima as scale

        //Asteroids
        if (asteroid) {
            astCircle.setPosition({ (float)(0.2 * SCREEN_WIDTH + (Sun.pos.x * SCREEN_WIDTH * 0.7 / initialDistance)),
                                    (float)(0.5 * SCREEN_HEIGHT + (Sun.pos.y * SCREEN_WIDTH * 0.7 / initialDistance)) });
            window.draw(astCircle);
        }
        

        //Sun
        sunCircle.setPosition({ (float)(0.2 * SCREEN_WIDTH + (Sun.pos.x * SCREEN_WIDTH * 0.7 / initialDistance)),
                                (float)(0.5 * SCREEN_HEIGHT + (Sun.pos.y * SCREEN_WIDTH * 0.7 / initialDistance)) });
        window.draw(sunCircle);


        //Comet Runge-Kutta
        RKcometCircle.setPosition({ (float)(0.2 * SCREEN_WIDTH + (RKComet.pos.x * SCREEN_WIDTH * 0.7 / initialDistance)),
                                (float)(0.5 * SCREEN_HEIGHT + (RKComet.pos.y * SCREEN_WIDTH * 0.7 / initialDistance)) });
        window.draw(RKcometCircle);

        //Comet Euler
        EulercometCircle.setPosition({ (float)(0.2 * SCREEN_WIDTH + (EulerComet.pos.x * SCREEN_WIDTH * 0.7 / initialDistance)),
                                (float)(0.5 * SCREEN_HEIGHT + (EulerComet.pos.y * SCREEN_WIDTH * 0.7 / initialDistance)) });
        window.draw(EulercometCircle);

        std::cout << EulerComet.pos.x << "\n";
        //Displays Data
        textData.setString(displayData(Sun, EulerComet, time));
        if (!traces) window.draw(textData);

        window.display();
        
    }
}





int main() {

    runProgram(true, false);

    return 0;
}
