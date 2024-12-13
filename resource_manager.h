#pragma once

#include <map>
#include <string>
#include "texture.h"

class ResourceManager {
public:
    static Texture2D& GetTexture(const std::string& name);
    static void LoadTexture(const std::string& name, const std::string& filePath);
    static void Clear();

private:
    static std::map<std::string, Texture2D> Textures;
};
