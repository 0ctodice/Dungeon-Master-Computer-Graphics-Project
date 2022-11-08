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
        Texture(std::string path, bool antialiasing)
        {
            std::unique_ptr<Image> texturePtr;

            if ((texturePtr = loadImage(FilePath(path))) == NULL)
            {
                std::cerr << "TEXTURE NOT LOADED" << std::endl;
            }

            glGenTextures(1, &texture);
            glBindTexture(GL_TEXTURE_2D, texture);
            glTexImage2D(GL_TEXTURE_2D, 0, GL_RGBA, texturePtr->getWidth(), texturePtr->getHeight(), 0, GL_RGBA, GL_FLOAT, texturePtr->getPixels());
            if (antialiasing)
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_LINEAR);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_LINEAR);
            }
            else
            {
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
                glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
            }

            glBindTexture(GL_TEXTURE_2D, 0);
        }

        void bind() const { glBindTexture(GL_TEXTURE_2D, texture); }
        void unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }
        void deleteTexture() { glDeleteTextures(1, &texture); }
    };
}