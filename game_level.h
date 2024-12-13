#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <vector>
#include <SFML/Graphics.hpp>
#include "game_object.h"
#include "sprite_renderer.h"

class GameLevel
{
public:
    std::vector<GameObject> Bricks;

    GameLevel() {}

    void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);
    void Draw(SpriteRenderer& renderer, sf::RenderWindow& window);
    bool IsCompleted();

private:
    void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};

#endif
