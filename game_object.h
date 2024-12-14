#ifndef GAME_OBJECT_H
#define GAME_OBJECT_H

#include <SFML/Graphics.hpp>
#include "texture.h"
#include "sprite_renderer.h"

class GameObject
{
public:
    sf::Vector2f Position, Size, Velocity;
    sf::Color Color;
    float Rotation;
    bool IsSolid;
    bool Destroyed;
    Texture2D Sprite;

    GameObject();

    GameObject(sf::Vector2f pos, sf::Vector2f size, Texture2D sprite);
    GameObject(sf::Vector2f pos, sf::Vector2f size, Texture2D sprite, sf::Color color);
    GameObject(sf::Vector2f pos, sf::Vector2f size, Texture2D sprite, sf::Color color , sf::Vector2f velocity );

    virtual void Draw(SpriteRenderer& renderer, sf::RenderWindow& window);
};

#endif
