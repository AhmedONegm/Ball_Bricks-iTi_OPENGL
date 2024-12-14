#ifndef GAME_LEVEL_H
#define GAME_LEVEL_H

#include <vector>
#include "game_object.h"
#include "sprite_renderer.h"

class GameLevel
{
public:
    std::vector<GameObject> Bricks;

    // Constructor
    GameLevel() {}

    // Loads level from file
    void Load(const char* file, unsigned int levelWidth, unsigned int levelHeight);

    // Render level
    void Draw(SpriteRenderer& renderer, sf::RenderWindow& window);

    // Check if the level is completed (all non-solid tiles are destroyed)
    bool IsCompleted();

private:
    // Initialize level from tile data
    void init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight);
};

#endif
