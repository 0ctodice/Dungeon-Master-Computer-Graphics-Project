#include <glimac/common.hpp>
#include <glimac/HUD.hpp>
#include <glimac/MatrixManager.hpp>
#include <string>

namespace glimac
{
  HUD::HUD(int width, int height, std::pair<Treasure, Treasure> *inv, int *money) : window{std::make_pair(width, height)}, playerInventory{inv}, playerMoney{money} {}
  void HUD::draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix) const
  {
    MatrixManager hudMatrix{globalPMatrix, globalMVMatrix};
    hudMatrix.scale(glm::vec3(.3f));
    hudMatrix.translate(glm::vec3(-3.9f, -1.9f, 1.f));
    hud.bind();
    for (int i = 0; i < 7; i++)
    {
      hudMatrix.translate(glm::vec3(1.f, 0.f, 0.f));
      hudMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
    }
    hud.unbind();

    coin.bind();
    MatrixManager coinMatrix{globalPMatrix, globalMVMatrix};
    coinMatrix.scale(glm::vec3(.15f));
    coinMatrix.translate(glm::vec3(3.f, -3.75f, 0.f));
    coinMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
    coin.unbind();

    auto val = std::to_string(*playerMoney);

    MatrixManager numberOffMatrix{globalPMatrix, globalMVMatrix};

    numberOffMatrix.scale(glm::vec3(.125f));
    numberOffMatrix.translate(glm::vec3(4.f, -4.5f, 0.f));

    std::for_each(val.begin(), val.end(), [this, &numberOffMatrix, &uTextureLocation, &uMVMatrixLocation, &uMVPMatrixLocation, &uNormalMatrixLocation, &uLightPosLocation, &globalPMatrix, &globalMVMatrix](const char &i)
                  {
                    numberOffMatrix.translate(glm::vec3(.75f,0.f, 0.f));
                    numbers[static_cast<int>(i - '0')].bind();
                    numberOffMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
                    numbers[static_cast<int>(i - '0')].unbind(); });

    if (playerInventory->first.getName() != "fist")
    {
      playerInventory->first.getTexture().bind();
      MatrixManager offMatrix{globalPMatrix, globalMVMatrix};
      offMatrix.scale(glm::vec3(.25f));
      offMatrix.translate(glm::vec3(-3.5f, -2.25f, 0.f));
      offMatrix.rotate(45.f, glm::vec3(0.f, 0.f, 1.f));
      offMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
      playerInventory->first.getTexture().unbind();

      auto val = std::to_string(playerInventory->first.getValue());

      MatrixManager numberOffMatrix{globalPMatrix, globalMVMatrix};

      numberOffMatrix.scale(glm::vec3(.125f));
      numberOffMatrix.translate(glm::vec3(-6.f, -4.5f, 0.f));

      std::for_each(val.begin(), val.end(), [this, &numberOffMatrix, &uTextureLocation, &uMVMatrixLocation, &uMVPMatrixLocation, &uNormalMatrixLocation, &uLightPosLocation, &globalPMatrix, &globalMVMatrix](const char &i)
                    {
                    numberOffMatrix.translate(glm::vec3(.75f,0.f, 0.f));
                    numbers[static_cast<int>(i - '0')].bind();
                    numberOffMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
                    numbers[static_cast<int>(i - '0')].unbind(); });
    }

    if (playerInventory->second.getName() != "skin")
    {
      playerInventory->second.getTexture().bind();
      MatrixManager defMatrix{globalPMatrix, globalMVMatrix};
      defMatrix.scale(glm::vec3(.25f));
      defMatrix.translate(glm::vec3(-1.f, -2.25f, 0.f));
      defMatrix.rotate(45.f, glm::vec3(0.f, 0.f, 1.f));
      defMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
      playerInventory->second.getTexture().unbind();

      auto val = std::to_string(playerInventory->second.getValue());

      MatrixManager numberDefMatrix{globalPMatrix, globalMVMatrix};

      numberDefMatrix.scale(glm::vec3(.125f));
      numberDefMatrix.translate(glm::vec3(-1.f, -4.5f, 0.1f));

      std::for_each(val.begin(), val.end(), [this, &numberDefMatrix, &uTextureLocation, &uMVMatrixLocation, &uMVPMatrixLocation, &uNormalMatrixLocation, &uLightPosLocation, &globalPMatrix, &globalMVMatrix](const char &i)
                    {
                    numberDefMatrix.translate(glm::vec3(.75f,0.f, 0.f));
                    numbers[static_cast<int>(i - '0')].bind();
                    numberDefMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
                    numbers[static_cast<int>(i - '0')].unbind(); });
    }
  }
  void HUD::clean()
  {
    playerInventory = nullptr;
    delete (playerInventory);
    std::for_each(numbers.begin(), numbers.end(), [](Texture &t)
                  { t.deleteTexture(); });
  }
}