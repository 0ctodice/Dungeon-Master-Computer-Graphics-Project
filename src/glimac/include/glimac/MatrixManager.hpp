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