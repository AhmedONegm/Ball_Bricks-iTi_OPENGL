#include "ball_object.h"

BallObject::BallObject()
    : GameObject(), Radius(12.5f), Stuck(true) {
}

BallObject::BallObject(sf::Vector2f pos, float radius, sf::Vector2f velocity, Texture2D sprite)
    : GameObject(pos, sf::Vector2f(radius * 2.0f, radius * 2.0f), sprite, sf::Color::White, velocity), Radius(radius), Stuck(true) {
}

sf::Vector2f BallObject::Move(float dt, unsigned int window_width)
{
    // if not stuck to player board
    if (!this->Stuck)
    {
        // move the ball
        this->Position += this->Velocity * dt;
        // then check if outside window bounds and if so, reverse velocity and restore at correct position
        if (this->Position.x <= 0.0f)
        {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = 0.0f;
        }
        else if (this->Position.x + this->Size.x >= window_width)
        {
            this->Velocity.x = -this->Velocity.x;
            this->Position.x = window_width - this->Size.x;
        }
        if (this->Position.y <= 0.0f)
        {
            this->Velocity.y = -this->Velocity.y;
            this->Position.y = 0.0f;
        }
    }
    return this->Position;
}

// Resets the ball to initial stuck position (if ball is outside window bounds)
void BallObject::Reset(sf::Vector2f position, sf::Vector2f velocity)
{
    this->Position = position;
    this->Velocity = velocity;
    this->Stuck = true;
}
