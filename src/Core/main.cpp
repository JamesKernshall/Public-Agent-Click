#include <iostream>
#include <SFML/Graphics.hpp>
#include "Game.h"
#include "Data.h"
#include <fstream>

int main()
{
    std::cout << "You should see a window that opens as well as this writing to console..."
        << std::endl;
    std::cout << "Reading Resolution File..."
        << std::endl;

    int DefaultResolutionX = 1080;
    int DefaultResolutionY = 720;

    Data game_data; // Initialising singleton

    std::ifstream resolutionRead("Data/settings.txt");
    int resolutionX = DefaultResolutionX;
    int resolutionY = DefaultResolutionY;
    resolutionRead >> resolutionX;
    resolutionRead >> resolutionY;

    resolutionRead.close();

    // create window and set up
    sf::RenderWindow window(sf::VideoMode(resolutionX, resolutionY), "Agent Click", sf::Style::Default);
    window.setFramerateLimit(60);
    window.setView(sf::View(sf::FloatRect(0, 0, DefaultResolutionX, DefaultResolutionY)));

    //Passes a pointer to window to global Data class to allow any object to render to screen
    game_data.window = &window;

    // A Clock starts counting as soon as it's created
    sf::Clock clock;

    //initialise an instance of the game class
    Game game(window);

    //run the init function of the game class and check it all initialises ok
    if (!game.init())
    {
        return 0;
    }


    // Game loop: run the program as long as the window is open
    while (window.isOpen())
    {
        // check all the window's events that were triggered since the last iteration of the loop
        sf::Event event;

        //calculate delta time
        sf::Time time = clock.restart();
        float dt = time.asSeconds();
        if (dt > 0.5f) // Clamp DeltaTime for debugging purposes
        {
            dt = 0.5f;
        }

        //'process inputs' element of the game loop
        while (window.pollEvent(event))
        {

            if (event.type == sf::Event::KeyPressed)
            {
                game.keyPressed(event);
            }
            if (event.type == sf::Event::KeyReleased)
            {
                game.keyReleased(event);
            }
            if (event.type == sf::Event::MouseButtonPressed || event.type == sf::Event::MouseButtonReleased)
            {
                game.mouseClicked(event);
            }


            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }


        //'update' element of the game loop
        game.update(dt);

        window.clear(sf::Color::Black);

        //'render' element of the game loop
        game.render();
        window.display();
    }

    std::ofstream resolutionWrite("Data/settings.txt");
    resolutionWrite << resolutionX << " " << resolutionY << "\n";

    resolutionWrite.close();
    return 0;
}