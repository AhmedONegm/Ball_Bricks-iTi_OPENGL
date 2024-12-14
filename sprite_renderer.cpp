#include "sprite_renderer.h"

SpriteRenderer::SpriteRenderer()
{
    this->initRenderData();
}

SpriteRenderer::~SpriteRenderer()
{
    // SFML handles resource management, so no need for manual cleanup
}

void SpriteRenderer::DrawSprite(Texture2D& texture, sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, float rotate, sf::Color color)
{
    // Create an SFML sprite
    sf::Sprite sprite;
    sprite.setTexture(texture.Texture);
    sprite.setPosition(position);
    sprite.setRotation(rotate);
    sprite.setScale(size.x / texture.Texture.getSize().x, size.y / texture.Texture.getSize().y);
    sprite.setColor(color);

    // Draw the sprite
    window.draw(sprite);
}

void SpriteRenderer::initRenderData()
{
    // Nothing needed here for SFML, but keep the method if additional setup is required later
}
