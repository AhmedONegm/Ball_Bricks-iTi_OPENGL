#ifndef SPRITE_RENDERER_H
#define SPRITE_RENDERER_H

#include <SFML/Graphics.hpp>
#include "texture.h"

class SpriteRenderer
{
public:
    SpriteRenderer();
    ~SpriteRenderer();

    void DrawSprite(Texture2D& texture, sf::RenderWindow& window, sf::Vector2f position, sf::Vector2f size, float rotate = 0.0f, sf::Color color = sf::Color::White);

private:
    void initRenderData();
};

#endif
