#include <SFML/Graphics.hpp>
#include "game.h"
#include "resource_manager.h"

// The Width of the screen
const unsigned int SCREEN_WIDTH = 800;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 600;

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);

int main(int argc, char* argv[])
{
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Breakout");
    window.setFramerateLimit(60);

    // Initialize game
    Breakout.Init();

    // DeltaTime variables
    sf::Clock clock;
    float deltaTime = 0.0f;

    while (window.isOpen())
    {
        // Calculate delta time
        sf::Time elapsed = clock.restart();
        deltaTime = elapsed.asSeconds();

        sf::Event event;
        while (window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                window.close();
            if (event.type == sf::Event::KeyPressed)
            {
                if (event.key.code == sf::Keyboard::Escape)
                    window.close();
                if (event.key.code >= 0 && event.key.code < sf::Keyboard::KeyCount)
                    Breakout.Keys[event.key.code] = true;
            }
            if (event.type == sf::Event::KeyReleased)
            {
                if (event.key.code >= 0 && event.key.code < sf::Keyboard::KeyCount)
                    Breakout.Keys[event.key.code] = false;
            }
        }

        // Manage user input
        Breakout.ProcessInput(deltaTime);

        // Update game state
        Breakout.Update(deltaTime);

        // Render
        window.clear(sf::Color::Black);
        Breakout.Render(window);
        window.display();
    }

    // Delete all resources as loaded using the resource manager
    ResourceManager::Clear();

    return 0;
}
