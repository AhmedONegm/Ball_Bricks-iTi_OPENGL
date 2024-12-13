#include "game.h"
#include "resource_manager.h"

// Constructor/Destructor
Game::Game(unsigned int width, unsigned int height)
    : Width(width), Height(height), State(GAME_MENU), Renderer(nullptr) {
    std::fill(std::begin(Keys), std::end(Keys), false);
    Renderer = new SpriteRenderer();
}

Game::~Game() {
    if (Renderer)
        delete Renderer;
}

void Game::Init() {
    ResourceManager::LoadTexture("background", "textures/background.png");
    ResourceManager::LoadTexture("player", "textures/player.png");
    ResourceManager::LoadTexture("block", "textures/block.png");
    ResourceManager::LoadTexture("block_solid", "textures/block_solid.png");
    ResourceManager::LoadTexture("ball", "textures/ball.png");
    ResourceManager::LoadTexture("bar", "textures/bar.png");
    ResourceManager::LoadTexture("brick", "textures/brick.png");

    // Initialize level
    Level.Load("levels/one.lvl", this->Width, this->Height / 2);

    // Initialize player
    Player = GameObject(sf::Vector2f(100.0f, 500.0f), sf::Vector2f(100.0f, 20.0f), ResourceManager::GetTexture("player"));

    // Initialize ball
    Ball = BallObject(sf::Vector2f(100.0f, 450.0f), 12.5f, sf::Vector2f(100.0f, -350.0f), ResourceManager::GetTexture("ball"));

    // Initialize brick
    Brick = GameObject(sf::Vector2f(0.0f, 0.0f), sf::Vector2f(100.0f, 100.0f), ResourceManager::GetTexture("brick"));

    // Initialize bar
    Bar = GameObject(sf::Vector2f(100.0f, 580.0f), sf::Vector2f(100.0f, 20.0f), ResourceManager::GetTexture("bar"));
}

void Game::ProcessInput(float dt) {
    // Process input (e.g., keyboard or mouse events)
}

void Game::Update(float dt) {
    Ball.Move(dt, this->Width);
    // Update game state
}

void Game::Render(sf::RenderWindow& window) {
    if (Renderer) {
        Renderer->DrawSprite(ResourceManager::GetTexture("background"), window, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(this->Width, this->Height));
        Level.Draw(*Renderer, window); // Draw level
        Player.Draw(*Renderer, window); // Draw player
        Ball.Draw(*Renderer, window); // Draw ball
        Bar.Draw(*Renderer, window);  // Draw bar
        Brick.Draw(*Renderer, window);  // Draw brick
    }
}
