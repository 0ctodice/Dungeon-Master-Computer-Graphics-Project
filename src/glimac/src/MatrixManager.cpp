#include <glimac/common.hpp>
#include <glimac/MatrixManager.hpp>

namespace glimac
{
    MatrixManager::MatrixManager(glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix)
    {
        globalProjectionMatrix = globalPMatrix;
        MVMatrix = globalMVMatrix;
    }

    MatrixManager::~MatrixManager()
    {
        globalProjectionMatrix = nullptr;
        delete (globalProjectionMatrix);
    }

    void MatrixManager::translate(glm::vec3 trans) { MVMatrix = glm::translate(MVMatrix, trans); }

    void MatrixManager::rotate(float value, glm::vec3 rot) { MVMatrix = glm::rotate(MVMatrix, glm::radians(value), rot); }

    void MatrixManager::scale(glm::vec3 sca) { MVMatrix = glm::scale(MVMatrix, sca); }

    void MatrixManager::draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation) const
    {
        glUniform1i(uTextureLocation, 0);
        glUniformMatrix4fv(uMVMatrixLocation, 1, GL_FALSE, glm::value_ptr(MVMatrix));
        glUniformMatrix4fv(uMVPMatrixLocation, 1, GL_FALSE, glm::value_ptr(*globalProjectionMatrix * MVMatrix));
        glUniformMatrix4fv(uNormalMatrixLocation, 1, GL_FALSE, glm::value_ptr(glm::transpose(glm::inverse(MVMatrix))));
        auto l = MVMatrix * glm::vec4(0.f);
        glUniform3f(uLightPosLocation, l.x, l.y, l.z);
        glDrawArrays(GL_TRIANGLES, 0, 6);
    }

    void MatrixManager::setMVMatrix(glm::mat4 matrix) { MVMatrix = matrix; }

    glm::mat4 MatrixManager::getMVMatrix() const { return MVMatrix; }
}