#ifndef TEXTURE_H
#define TEXTURE_H

#include <SFML/Graphics.hpp>

class Texture2D
{
public:
    sf::Texture Texture;
    unsigned int Width, Height;

    Texture2D();
    void Generate(unsigned int width, unsigned int height, unsigned char* data);
    void Bind() const; // Not required for SFML, but kept for compatibility

private:
    unsigned int Internal_Format;
    unsigned int Image_Format;
    unsigned int Wrap_S;
    unsigned int Wrap_T;
    unsigned int Filter_Min;
    unsigned int Filter_Max;
};

#endif
