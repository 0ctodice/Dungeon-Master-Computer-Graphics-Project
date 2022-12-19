/////////////////////////////////////////////////////////////////////////////////
//
// ------------------------------------------------------------------------------
//   _____      _            _ _
//  |  _  |    | |          | (_)
//  | |/' | ___| |_ ___   __| |_  ___ ___
//  |  /| |/ __| __/ _ \ / _` | |/ __/ _ \
//  \ |_/ / (__| || (_) | (_| | | (_|  __/
//   \___/ \___|\__\___/ \__,_|_|\___\___|
//
// ------------------------------------------------------------------------------
//
//  Projet de synthèse d'image du Master 2 Informatique spé. Sciences de l'image
//  ~ Thomas DUMONT A.K.A 0ctodice
//
// ------------------------------------------------------------------------------
//
/////////////////////////////////////////////////////////////////////////////////

#include <glimac/Texture.hpp>

namespace glimac
{
    Texture::Texture(std::string path, bool antialiasing)
    {
        if (path == "")
        {
            return;
        }

        std::unique_ptr<Image> texturePtr;

        if ((texturePtr = loadImage(FilePath("/home/thomas2dumont/Computer_Graphics/Dungeon-Master-Computer-Graphics-Project/assets/textures/" + path))) == NULL)
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