#include "game.h"
#include "resource_manager.h"
#include <sstream>
#include <fstream>
#include <iostream>
#include <algorithm>
#include <gl/glew/glew.h>

// Initial velocity and player size constants
const sf::Vector2f PLAYER_SIZE(100.0f, 20.0f);
const float PLAYER_VELOCITY = 500.0f;
const sf::Vector2f INITIAL_BALL_VELOCITY(100.0f, -350.0f);
const float BALL_RADIUS = 12.5f;

// Constructor/Destructor
Game::Game(unsigned int width, unsigned int height)
    : Width(width), Height(height), State(GAME_MENU), Renderer(nullptr) {
    std::fill(std::begin(Keys), std::end(Keys), false);
}

Game::~Game() {
    if (Renderer)
        delete Renderer;
}

void Game::Init() {
    // Load textures
    ResourceManager::LoadTexture("background","textures/background.png");
    ResourceManager::LoadTexture("player","textures/player.png");
    ResourceManager::LoadTexture("block","textures/block.png");
    ResourceManager::LoadTexture("block_solid","textures/block_solid.png");
    ResourceManager::LoadTexture("ball","textures/ball.png");

    // Initialize renderer
    Renderer = new SpriteRenderer();

    // Initialize OpenGL state
        glEnable(GL_DEPTH_TEST);
        glDepthFunc(GL_LEQUAL);
        glEnable(GL_BLEND);
        glBlendFunc(GL_SRC_ALPHA, GL_ONE_MINUS_SRC_ALPHA);

        // Other initialization code...

    // Load levels
    GameLevel one; one.Load("levels/one.lvl", this->Width, this->Height / 2);
    GameLevel two; two.Load("levels/two.lvl", this->Width, this->Height / 2);
    GameLevel three; three.Load("levels/three.lvl", this->Width, this->Height / 2);
    GameLevel four; four.Load("levels/four.lvl", this->Width, this->Height / 2);
    this->Levels.push_back(one);
    this->Levels.push_back(two);
    this->Levels.push_back(three);
    this->Levels.push_back(four);
    this->CurrentLevel = 0;

    // Configure game objects
    sf::Vector2f playerPos(this->Width / 2.0f - PLAYER_SIZE.x / 2.0f, this->Height - PLAYER_SIZE.y);
    Player = GameObject(playerPos, PLAYER_SIZE, ResourceManager::GetTexture("player"));
    sf::Vector2f ballPos = playerPos + sf::Vector2f(PLAYER_SIZE.x / 2.0f - BALL_RADIUS, -BALL_RADIUS * 2.0f);
    Ball = BallObject(ballPos, BALL_RADIUS, INITIAL_BALL_VELOCITY, ResourceManager::GetTexture("ball"));

    // Read from map.txt
    std::ifstream file("map.txt");
    if (!file.is_open()) {
        std::cerr << "Failed to open map.txt" << std::endl;
        return;
    }

    std::string line;
    int row = 0;

    while (std::getline(file, line)) {
        std::cout << "Line " << row << ": " << line << std::endl; // Debug: Print each line
        for (int j = 0; j < static_cast<int>(Width / 100) && j < static_cast<int>(line.length()); ++j) {
            if (line[j] == '1') {
                std::cout << "Creating block at (" << 100.0f * j << ", " << 100.0f * row << ")" << std::endl; // Debug: Print block creation
                GameObject block = GameObject(sf::Vector2f(100.0f * j, 100.0f * row), sf::Vector2f(100.0f, 20.0f), ResourceManager::GetTexture("block"));
                Blocks.push_back(block);
            }
        }
        ++row;
    }

    file.close();
}

void Game::ProcessInput(float dt) {
    // Move player bar
    float velocity = 500.0f;  // Adjust as needed
    if (Keys[sf::Keyboard::A] && Player.Position.x >= 0.0f) {
        Player.Position.x -= velocity * dt;
    }
    if (Keys[sf::Keyboard::D] && Player.Position.x <= Width - Player.Size.x) {
        Player.Position.x += velocity * dt;
    }

    // Launch ball
    if (Keys[sf::Keyboard::Space]) {
        Ball.Stuck = false;
    }
}

void Game::Update(float dt) {
    Ball.Move(dt, this->Width);
    this->DoCollisions();
    // Keep ball on top of the player if stuck
    if (Ball.Stuck) {
        Ball.Position.x = Player.Position.x + Player.Size.x / 2.0f - Ball.Size.x / 2.0f;
        Ball.Position.y = Player.Position.y - Ball.Size.y;
    }
}

void Game::Render(sf::RenderWindow& window)
{
        if (Renderer) {
            Renderer->DrawSprite(ResourceManager::GetTexture("background"),window, sf::Vector2f(0.0f, 0.0f), sf::Vector2f(this->Width, this->Height));
            Level.Draw(*Renderer,window); // Draw level
            Player.Draw(*Renderer, window); // Draw player
            Ball.Draw(*Renderer, window); // Draw ball
            for (GameObject& block : Blocks) {
                block.Draw(*Renderer, window); // Draw block
            }
        }


}

    // Utility functions for vector operations
    float Game::length(const sf::Vector2f& vector)
    {
        return std::sqrt(vector.x * vector.x + vector.y * vector.y);
    }

    sf::Vector2f Game::normalize(const sf::Vector2f& vector)
    {
        float len = length(vector);
        if (len != 0)
            return sf::Vector2f(vector.x / len, vector.y / len);
        else
            return vector;
    }

    float Game::dot(const sf::Vector2f& vector1, const sf::Vector2f& vector2)
    {
        return vector1.x * vector2.x + vector1.y * vector2.y;
    }

    // Check for collisions
    void Game::DoCollisions() {
        for (GameObject& block : Blocks) {
            if (!block.Destroyed) {
                Collision collision = CheckCollision(Ball, block);
                if (std::get<0>(collision)) // If collision is true
                {
                    // Destroy block if not solid
                    if (!block.IsSolid)
                        block.Destroyed = true;

                    // Collision resolution
                    Direction dir = std::get<1>(collision);
                    sf::Vector2f diff_vector = std::get<2>(collision);
                    if (dir == LEFT || dir == RIGHT) // Horizontal collision
                    {
                        Ball.Velocity.x = -Ball.Velocity.x; // Reverse horizontal velocity
                        // Relocate
                        float penetration = Ball.Radius - std::abs(diff_vector.x);
                        if (dir == LEFT)
                            Ball.Position.x += penetration; // Move ball to right
                        else
                            Ball.Position.x -= penetration; // Move ball to left
                    }
                    else // Vertical collision
                    {
                        Ball.Velocity.y = -Ball.Velocity.y; // Reverse vertical velocity
                        // Relocate
                        float penetration = Ball.Radius - std::abs(diff_vector.y);
                        if (dir == UP)
                            Ball.Position.y -= penetration; // Move ball back up
                        else
                            Ball.Position.y += penetration; // Move ball back down
                    }
                }
            }
        }

        // Check collision with player pad (unless stuck)
        Collision result = CheckCollision(Ball, Player);
        if (!Ball.Stuck && std::get<0>(result)) {
            // Check where it hit the board, and change velocity based on where it hit the board
            float centerBoard = Player.Position.x + Player.Size.x / 2.0f;
            float distance = (Ball.Position.x + Ball.Radius) - centerBoard;
            float percentage = distance / (Player.Size.x / 2.0f);
            // Then move accordingly
            float strength = 2.0f;
            sf::Vector2f oldVelocity = Ball.Velocity;
            Ball.Velocity.x = INITIAL_BALL_VELOCITY.x * percentage * strength;
            Ball.Velocity = normalize(Ball.Velocity) * length(oldVelocity); // Keep speed consistent over both axes (multiply by length of old velocity, so total strength is not changed)
            // Fix sticky paddle
            Ball.Velocity.y = -1.0f * abs(Ball.Velocity.y);
        }
    }

    void Game::ResetLevel()
    {
    }

    void Game::ResetPlayer()
    {
    }

    bool Game::CheckCollision(GameObject& one, GameObject& two) // AABB - AABB collision
    {
        // Collision x-axis?
        bool collisionX = one.Position.x + one.Size.x >= two.Position.x &&
            two.Position.x + two.Size.x >= one.Position.x;
        // Collision y-axis?
        bool collisionY = one.Position.y + one.Size.y >= two.Position.y &&
            two.Position.y + two.Size.y >= one.Position.y;
        // Collision only if on both axes
        return collisionX && collisionY;
    }

    Collision Game::CheckCollision(BallObject& one, GameObject& two) // AABB - Circle collision
    {
        // Get center point circle first 
        sf::Vector2f center = one.Position + sf::Vector2f(one.Radius, one.Radius);
        // Calculate AABB info (center, half-extents)
        sf::Vector2f aabb_half_extents(two.Size.x / 2.0f, two.Size.y / 2.0f);
        sf::Vector2f aabb_center(
            two.Position.x + aabb_half_extents.x,
            two.Position.y + aabb_half_extents.y
        );
        // Get difference vector between both centers
        sf::Vector2f difference = center - aabb_center;
        sf::Vector2f clamped = sf::Vector2f(clamp(difference.x, -aabb_half_extents.x, aabb_half_extents.x),
            clamp(difference.y, -aabb_half_extents.y, aabb_half_extents.y));
        // Add clamped value to AABB_center and we get the value of box closest to circle
        sf::Vector2f closest = aabb_center + clamped;
        // Retrieve vector between center circle and closest point AABB and check if length < radius
        difference = closest - center;

        if (length(difference) < one.Radius) // not <= since in that case a collision also occurs when object one exactly touches object two, which they are at the end of each collision resolution stage.
            return std::make_tuple(true, VectorDirection(difference), difference);
        else
            return std::make_tuple(false, UP, sf::Vector2f(0.0f, 0.0f));
    }

    Direction Game::VectorDirection(sf::Vector2f target) {
        sf::Vector2f compass[] = {
            sf::Vector2f(0.0f, 1.0f),    // up
            sf::Vector2f(1.0f, 0.0f),    // right
            sf::Vector2f(0.0f, -1.0f),   // down
            sf::Vector2f(-1.0f, 0.0f)    // left
        };
        float max = 0.0f;
        unsigned int best_match = -1;
        for (unsigned int i = 0; i < 4; i++)
        {
            float dot_product = dot(normalize(target), compass[i]);
            if (dot_product > max)
            {
                max = dot_product;
                best_match = i;
            }
        }
        return (Direction)best_match;
    }

    float Game::clamp(float value, float min, float max) {
        return std::max(min, std::min(max, value));
    }

