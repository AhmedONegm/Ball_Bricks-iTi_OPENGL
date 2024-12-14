#include "OpenGLSFML/include/gl/glew/glew.h"

#include <SFML/Window.hpp>
#include <SFML/OpenGL.hpp>
#include "game.h"
#include<iostream>

// The Width of the screen
const unsigned int SCREEN_WIDTH = 800;
// The height of the screen
const unsigned int SCREEN_HEIGHT = 600;

Game Breakout(SCREEN_WIDTH, SCREEN_HEIGHT);
GLuint makeShader(const char* ShaderSourceCode, GLenum SHADER_TYPE);

int main()
{
    // Create a window with SFML
    sf::RenderWindow window(sf::VideoMode(SCREEN_WIDTH, SCREEN_HEIGHT), "Breakout", sf::Style::Close);
    window.setFramerateLimit(60);
    glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

    // Initialize GLEW
    glewExperimental = GL_TRUE;
    if (glewInit() != GLEW_OK)
    {
        std::cerr << "Failed to initialize GLEW" << std::endl;
        return -1;
    }

    // OpenGL settings 
    glEnable(GL_DEPTH_TEST); 
    glDepthFunc(GL_LEQUAL); 
    glEnable(GL_BLEND); 
    glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

    // Initialize game
    Breakout.Init();

    // DeltaTime variables
    sf::Clock clock;
    float deltaTime = 0.0f;
    
    // Load and compile shaders
    //Shader shader = ResourceManager::LoadShader("vertex_shader.glsl", "fragment_shader.glsl", nullptr, "sprite");
    //shader.Use();

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
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        Breakout.Render(window);
        window.display();
    }

    return 0;
}
