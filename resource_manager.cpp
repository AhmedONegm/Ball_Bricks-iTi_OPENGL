#include "resource_manager.h"
#include<iostream>

std::map<std::string, Texture2D> ResourceManager::Textures;

Texture2D& ResourceManager::GetTexture(const std::string& name) {
    return Textures.at(name);
}

void ResourceManager::LoadTexture(const std::string& name, const std::string& filePath) {
    Texture2D texture;
    if (!texture.Texture.loadFromFile(filePath)) {
        std::cerr << "Error: Could not load texture from file " << filePath << std::endl;
    }
    else {
        Textures[name] = texture;
    }
}

void ResourceManager::Clear() {
    Textures.clear();
}
