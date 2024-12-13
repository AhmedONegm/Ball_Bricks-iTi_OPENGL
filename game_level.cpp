#include "game_level.h"
#include <fstream>
#include <sstream>
#include "resource_manager.h"

void GameLevel::Load(const char* file, unsigned int levelWidth, unsigned int levelHeight)
{
    // Clear old data
    this->Bricks.clear();
    // Load from file
    unsigned int tileCode;
    std::string line;
    std::ifstream fstream(file);
    std::vector<std::vector<unsigned int>> tileData;
    if (fstream)
    {
        while (std::getline(fstream, line)) // Read each line from level file
        {
            std::istringstream sstream(line);
            std::vector<unsigned int> row;
            while (sstream >> tileCode) // Read each word separated by spaces
                row.push_back(tileCode);
            tileData.push_back(row);
        }
        if (tileData.size() > 0)
            this->init(tileData, levelWidth, levelHeight);
    }
}

void GameLevel::Draw(SpriteRenderer& renderer, sf::RenderWindow& window)
{
    for (GameObject& tile : this->Bricks)
        if (!tile.Destroyed)
            tile.Draw(renderer, window);
}

bool GameLevel::IsCompleted()
{
    for (GameObject& tile : this->Bricks)
        if (!tile.IsSolid && !tile.Destroyed)
            return false;
    return true;
}

void GameLevel::init(std::vector<std::vector<unsigned int>> tileData, unsigned int levelWidth, unsigned int levelHeight)
{
    // Calculate dimensions
    unsigned int height = tileData.size();
    unsigned int width = tileData[0].size(); // Note we can index vector at [0] since this function is only called if height > 0
    float unit_width = levelWidth / static_cast<float>(width), unit_height = levelHeight / static_cast<float>(height);

    // Initialize level tiles based on tileData
    for (unsigned int y = 0; y < height; ++y)
    {
        for (unsigned int x = 0; x < width; ++x)
        {
            // Check block type from level data (2D level array)
            if (tileData[y][x] == 1) // Solid
            {
                sf::Vector2f pos(unit_width * x, unit_height * y);
                sf::Vector2f size(unit_width, unit_height);
                GameObject obj(pos, size, ResourceManager::GetTexture("block_solid"), sf::Color(204, 204, 179)); // Equivalent to glm::vec3(0.8f, 0.8f, 0.7f)
                obj.IsSolid = true;
                this->Bricks.push_back(obj);
            }
            else if (tileData[y][x] > 1) // Non-solid; now determine its color based on level data
            {
                sf::Color color = sf::Color::White; // Original: white
                if (tileData[y][x] == 2)
                    color = sf::Color(51, 153, 255); // Equivalent to glm::vec3(0.2f, 0.6f, 1.0f)
                else if (tileData[y][x] == 3)
                    color = sf::Color(0, 179, 0); // Equivalent to glm::vec3(0.0f, 0.7f, 0.0f)
                else if (tileData[y][x] == 4)
                    color = sf::Color(204, 204, 102); // Equivalent to glm::vec3(0.8f, 0.8f, 0.4f)
                else if (tileData[y][x] == 5)
                    color = sf::Color(255, 128, 0); // Equivalent to glm::vec3(1.0f, 0.5f, 0.0f)

                sf::Vector2f pos(unit_width * x, unit_height * y);
                sf::Vector2f size(unit_width, unit_height);
                this->Bricks.push_back(GameObject(pos, size, ResourceManager::GetTexture("block"), color));
            }
        }
    }
}
