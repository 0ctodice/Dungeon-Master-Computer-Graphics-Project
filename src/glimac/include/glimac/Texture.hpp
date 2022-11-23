#pragma once

#include "glm.hpp"
#include <GL/glew.h>
#include <iostream>
#include <glimac/Image.hpp>
#include <glimac/FilePath.hpp>

namespace glimac
{
    class Texture
    {
    private:
        GLuint texture;

    public:
        Texture() = delete;
        Texture(std::string path, bool antialiasing);

        void bind() const;
        void unbind() const;
        void deleteTexture();
    };
}