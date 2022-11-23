#include <glimac/common.hpp>
#include <glimac/Texture.hpp>

namespace glimac
{
    Texture::Texture(std::string path, bool antialiasing)
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

    void Texture::bind() const { glBindTexture(GL_TEXTURE_2D, texture); }
    void Texture::unbind() const { glBindTexture(GL_TEXTURE_2D, 0); }
    void Texture::deleteTexture() { glDeleteTextures(1, &texture); }
}