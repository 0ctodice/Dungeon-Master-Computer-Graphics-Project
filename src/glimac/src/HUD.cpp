#include <glimac/common.hpp>
#include <glimac/HUD.hpp>
#include <glimac/MatrixManager.hpp>

namespace glimac
{
    HUD::HUD(int width, int height) : window{std::make_pair(width, height)} {}
    void HUD::draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix) const
    {
        texture.bind();

        MatrixManager topMatrix{globalPMatrix, globalMVMatrix};
        topMatrix.scale(glm::vec3(.25f));
        topMatrix.translate(glm::vec3(-3.5f, 1.75f, 0.f));
        topMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
        for (int i = 0; i < 7; i++)
        {
            topMatrix.translate(glm::vec3(1.f, 0.f, 0.f));
            topMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
        }

        for (int i = 0; i < 4; i++)
        {
            topMatrix.translate(glm::vec3(-1.f, 0.f, 0.f));
            topMatrix.translate(glm::vec3(0.f, -1.f, 0.f));
            topMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
            topMatrix.translate(glm::vec3(1.f, 0.f, 0.f));
            topMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
        }

        // MatrixManager sideMatrix{globalPMatrix, globalMVMatrix};
        // sideMatrix.scale(glm::vec3(.44f));
        // sideMatrix.translate(glm::vec3(1.77f, .21f, 0.f));
        // sideMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
        // sideMatrix.translate(glm::vec3(0.f, -1.f, 0.f));
        // sideMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);

        texture.unbind();
    }
    void HUD::deleteTexture()
    {
        texture.deleteTexture();
    }
}