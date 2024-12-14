#ifndef GAME_H
#define GAME_H

#include <SFML/Graphics.hpp>
#include "sprite_renderer.h"
#include "game_object.h"
#include "game_level.h"
#include "ball_object.h"
#include <vector>

// Represents the current state of the game
enum GameState {
    GAME_ACTIVE,
    GAME_MENU,
    GAME_WIN
};

enum Direction {
    UP,
    RIGHT,
    DOWN,
    LEFT
};

typedef std::tuple<bool, Direction, sf::Vector2f> Collision;


class Game
{
public:
    GameState State;
    bool Keys[sf::Keyboard::KeyCount];
    unsigned int Width, Height;
    GameLevel Level;
    std::vector<GameLevel> Levels;
    unsigned int CurrentLevel;
    std::vector<GameObject> Blocks;

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
    GameObject Player;
    BallObject Ball;

    void DoCollisions();
    void ResetLevel();
    void ResetPlayer();

    // Collision detection functions
    bool CheckCollision(GameObject& one, GameObject& two);
    Collision CheckCollision(BallObject& one, GameObject& two);
    Direction VectorDirection(sf::Vector2f closest);
    float clamp(float value, float min, float max);

    // Utility functions for vector operations
    static float length(const sf::Vector2f& vector);
    static sf::Vector2f normalize(const sf::Vector2f& vector);
    static float dot(const sf::Vector2f& vector1, const sf::Vector2f& vector2);
};

#endif
