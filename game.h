#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "sprite_renderer.h"
#include "game_object.h"
#include "game_level.h"
#include "ball_object.h"

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

class Game
{
public:
    GameState State;
    bool Keys[sf::Keyboard::KeyCount];
    unsigned int Width, Height;

    // Constructor/Destructor
    Game(unsigned int width, unsigned int height);
    ~Game();

    // Initialize game state (load all shaders/textures/levels)
    void Init();

    // Game loop
    void ProcessInput(float dt);
    void Update(float dt);
    void Render(sf::RenderWindow& window);

private:
    SpriteRenderer* Renderer;
    GameObject Player, Bar, Brick;
    GameLevel Level;
    BallObject Ball;
};

#endif
