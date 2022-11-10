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
        MatrixManager(glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f))
        {
            globalProjectionMatrix = globalPMatrix;
            MVMatrix = globalMVMatrix;
        }

        void translate(glm::vec3 trans)
        {
            MVMatrix = glm::translate(MVMatrix, trans);
        }

        void rotate(float value, glm::vec3 rot)
        {
            MVMatrix = glm::rotate(MVMatrix, glm::radians(value), rot);
        }

        void scale(glm::vec3 sca)
        {
            MVMatrix = glm::scale(MVMatrix, sca);
        }

        void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation) const
        {
            glUniform1i(uTextureLocation, 0);
            glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
            glUniformMatrix4fv(uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(*globalProjectionMatrix * MVMatrix));
            glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
            glDrawArrays(GL_TRIANGLES, 0, 6);
        }

        void setMVMatrix(glm::mat4 matrix) { MVMatrix = matrix; }

        glm::mat4 getMVMatrix() const { return MVMatrix; }
    };
}