#include "texture.h"
#include <gl/glew/glew.h>
#include <iostream>

Texture2D::Texture2D()
    : Width(0), Height(0), Internal_Format(GL_RGB), Image_Format(GL_RGB), Wrap_S(GL_REPEAT), Wrap_T(GL_REPEAT), Filter_Min(GL_LINEAR), Filter_Max(GL_LINEAR)
{
    // SFML handles texture creation internally
}

void Texture2D::Generate(unsigned int width, unsigned int height, unsigned char* data)
{
    this->Width = width;
    this->Height = height;

    if (!this->Texture.create(width, height)) {
        std::cerr << "Failed to create texture" << std::endl;
        return;
    }

    this->Texture.update(data);
}

void Texture2D::Bind() const
{
    // SFML binds textures automatically when they are drawn
}
