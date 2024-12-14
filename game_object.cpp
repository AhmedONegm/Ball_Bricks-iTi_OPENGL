#include "game_object.h"

GameObject::GameObject()
    : Position(0.0f, 0.0f), Size(1.0f, 1.0f), Velocity(0.0f, 0.0f), Color(sf::Color::White), Rotation(0.0f), IsSolid(false), Destroyed(false) {
}
GameObject::GameObject(sf::Vector2f pos, sf::Vector2f size, Texture2D sprite)
    : Position(pos), Size(size), Sprite(sprite)
{
}
GameObject::GameObject(sf::Vector2f pos, sf::Vector2f size, Texture2D sprite, sf::Color color)
    : Position(pos), Size(size),Sprite(sprite), Color(color)
{
}



GameObject::GameObject(sf::Vector2f pos, sf::Vector2f size, Texture2D sprite, sf::Color color, sf::Vector2f velocity)
    : Position(pos), Size(size), Velocity(velocity), Color(color), Rotation(0.0f), Sprite(sprite), IsSolid(false), Destroyed(false) {
}

void GameObject::Draw(SpriteRenderer& renderer, sf::RenderWindow& window)
{
    renderer.DrawSprite(this->Sprite,window, this->Position, this->Size, this->Rotation, this->Color);
}
