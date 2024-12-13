#ifndef BALL_OBJECT_H
#define BALL_OBJECT_H

#include <SFML/Graphics.hpp>
#include "game_object.h"
#include "texture.h"

class BallObject : public GameObject
{
public:
    float Radius;
    bool Stuck;

    BallObject();
    BallObject(sf::Vector2f pos, float radius, sf::Vector2f velocity, Texture2D sprite);

    sf::Vector2f Move(float dt, unsigned int window_width);
    void Reset(sf::Vector2f position, sf::Vector2f velocity);
};

#endif
