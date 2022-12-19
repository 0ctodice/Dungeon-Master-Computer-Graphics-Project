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
#include <glimac/Texture.hpp>

namespace glimac
{
    class MatrixManager
    {
    private:
        glm::mat4 *globalProjectionMatrix;
        glm::mat4 MVMatrix;

    public:
        MatrixManager() = delete;
        MatrixManager(glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f));
        ~MatrixManager();
        void translate(glm::vec3 trans);
        void rotate(float value, glm::vec3 rot);
        void scale(glm::vec3 sca);
        void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation) const;
        void setMVMatrix(glm::mat4 matrix);
        glm::mat4 getMVMatrix() const;
    };
}