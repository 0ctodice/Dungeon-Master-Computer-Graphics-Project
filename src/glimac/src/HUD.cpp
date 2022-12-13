#include <glimac/common.hpp>
#include <glimac/HUD.hpp>
#include <glimac/MatrixManager.hpp>

namespace glimac
{
    HUD::HUD(int width, int height, std::pair<Treasure, Treasure> *inv, float ratio) : window{std::make_pair(width, height)}, playerInventory{inv}, ratio{ratio}
    {
        std::cout << ratio << std::endl;
    }
    void HUD::draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix) const
    {
        playerInventory->first.getTexture().bind();
        MatrixManager offMatrix{globalPMatrix, globalMVMatrix};
        offMatrix.scale(glm::vec3(ratio));
        offMatrix.translate(glm::vec3(-3.5f, -2.25f, 0.f));
        offMatrix.rotate(45.f, glm::vec3(0.f, 0.f, 1.f));
        offMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
        playerInventory->first.getTexture().unbind();

        playerInventory->second.getTexture().bind();
        MatrixManager defMatrix{globalPMatrix, globalMVMatrix};
        defMatrix.scale(glm::vec3(ratio));
        defMatrix.translate(glm::vec3(0.f, -2.25f, 0.f));
        defMatrix.rotate(45.f, glm::vec3(0.f, 0.f, 1.f));
        defMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
        playerInventory->second.getTexture().unbind();
    }
    void HUD::clean()
    {
        playerInventory = nullptr;
        delete (playerInventory);
    }
}