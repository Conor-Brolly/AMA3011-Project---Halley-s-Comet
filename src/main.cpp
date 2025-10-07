#include <SFML/Graphics.hpp>
#include <string>
#include "EulerSolver.h"

#define SCREEN_WIDTH 2048u
#define SCREEN_HEIGHT 1024u

std::string displayData(Particle Sun, Particle Comet, double time) {
    std::string output = "";

    output += "Time (years):\t" + std::to_string(time / 3.16e7);

    double speed = sqrt(pow(Comet.Vx, 2) + pow(Comet.Vy, 2));
    output += "\nSpeed (m/s^):\t" + std::to_string(speed);

    double distance = sqrt(pow(Comet.x - Sun.x, 2) + pow(Comet.y - Sun.y, 2));
    output += "\nDistance (km):\t" + std::to_string(distance/1000);

    return output;
}

int main()
{
    //Window initialisation
    auto window = sf::RenderWindow(sf::VideoMode({SCREEN_WIDTH, SCREEN_HEIGHT}), "AMA3011 Halley's Comet");
    window.setFramerateLimit(144);

    //DE solver
    Solver* euler = new EulerSolver();
    double time = 0.0;
    double timestep = 50000;//(seconds)

    double initialDistance = 5.2e12;//Distance of halleys comet at apoapsis
    
    //Particle system
    Particle Sun = { 1.988e30, 0, 0, 0, 0 };//Mass of sun: 1.998 * 10^30
    Particle Comet = { 2.2e14, initialDistance, 0, 0, -910};//Mass of halleys comet: 2.2 * 10^14

    //Display Variables
    sf::CircleShape sunCircle(16.0f);
    sunCircle.setOrigin({ 16.0f, 16.0f });
    sunCircle.setFillColor(sf::Color(255, 255, 0));

    sf::CircleShape cometCircle(4.0f);
    cometCircle.setOrigin({ 4.0f, 4.0f });
    cometCircle.setFillColor(sf::Color(0, 255, 255));

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
        for (int i = 0; i < 1; i++) {
            euler->update(&Sun, &Comet, timestep);
            time += timestep;
        }
        
        
        //
        //___________________________Drawing to the screen___________________________
        window.clear();
         
        
        //Displays Sun and Comet as circles

        //Scales to screen-space from real position, using the initial maxima as scale
        sunCircle.setPosition({ (float)(0.1 * SCREEN_WIDTH + (Sun.x * SCREEN_WIDTH * 0.8 / initialDistance)),
                                (float)(0.5 * SCREEN_HEIGHT + (Sun.y * SCREEN_WIDTH * 0.8 / initialDistance)) });
        window.draw(sunCircle);

        cometCircle.setPosition({ (float)(0.1 * SCREEN_WIDTH + (Comet.x * SCREEN_WIDTH * 0.8 / initialDistance)),
                                (float)(0.5 * SCREEN_HEIGHT + (Comet.y * SCREEN_WIDTH * 0.8 / initialDistance)) });
        window.draw(cometCircle);

        //Displays Data
        textData.setString(displayData(Sun, Comet, time));
        window.draw(textData);

        window.display();
        
    }
}
