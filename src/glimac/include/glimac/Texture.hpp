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