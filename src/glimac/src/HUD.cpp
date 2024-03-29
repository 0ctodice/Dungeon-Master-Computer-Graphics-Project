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

#include <glimac/HUD.hpp>
#include <glimac/MatrixManager.hpp>
#include <string>

namespace glimac
{
  HUD::HUD(int width, int height, std::pair<Treasure, Treasure> *inv, int *money, int *maxH, int *H) : window{std::make_pair(width, height)}, playerInventory{inv}, playerMoney{money}, playerMaxHealth{maxH}, playerCurrentHealth{H} {}

  HUD::~HUD()
  {
    playerInventory = nullptr;
    playerMoney = nullptr;
    playerMaxHealth = nullptr;
    playerCurrentHealth = nullptr;
    delete (playerInventory);
    delete (playerMoney);
    delete (playerMaxHealth);
    delete (playerCurrentHealth);
  }

  void HUD::draw(GLuint uTextureLocation,
                 GLuint uMVMatrixLocation,
                 GLuint uMVPMatrixLocation,
                 GLuint uNormalMatrixLocation,
                 GLuint uLightPosLocation,
                 glm::mat4 *globalPMatrix,
                 glm::mat4 globalMVMatrix) const
  {
    int lbLevel = std::ceil((float)(*playerCurrentHealth * 6) / (float)*playerMaxHealth);

    MatrixManager lbMatrix{globalPMatrix, globalMVMatrix};
    lbMatrix.scale(glm::vec3{.75f});
    lbMatrix.translate(glm::vec3(-1.f, .8f, 0.f));
    lifeBar[lbLevel].bind();
    lbMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
    lifeBar[lbLevel].unbind();

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
    coinMatrix.scale(glm::vec3(.25f));
    coinMatrix.translate(glm::vec3(0.f, -1.75f, 0.f));
    coinMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
    coin.unbind();

    std::string val = std::to_string(*playerMoney);

    MatrixManager numberCoinMatrix{globalPMatrix, globalMVMatrix};

    numberCoinMatrix.scale(glm::vec3(.1f));
    numberCoinMatrix.translate(glm::vec3(0.f, -6.25f, 0.f));

    drawNumber(val, numberCoinMatrix, uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix);

    sword.bind();
    MatrixManager offMatrix{globalPMatrix, globalMVMatrix};
    offMatrix.scale(glm::vec3(.4f));
    offMatrix.translate(glm::vec3(-1.25f, -1.4f, 0.f));
    offMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
    sword.unbind();

    val = std::to_string(playerInventory->first.getValue());

    MatrixManager numberOffMatrix{globalPMatrix, globalMVMatrix};

    numberOffMatrix.scale(glm::vec3(.2f));
    numberOffMatrix.translate(glm::vec3(-2.5f, -2.8f, -1.f));

    drawNumber(val, numberOffMatrix, uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix);

    shield.bind();
    MatrixManager defMatrix{globalPMatrix, globalMVMatrix};
    defMatrix.scale(glm::vec3(.4f));
    defMatrix.translate(glm::vec3(1.25f, -1.4f, 0.f));
    defMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
    shield.unbind();

    val = std::to_string(playerInventory->second.getValue());

    MatrixManager numberDefMatrix{globalPMatrix, globalMVMatrix};

    numberDefMatrix.scale(glm::vec3(.2f));
    numberDefMatrix.translate(glm::vec3(2.5f, -2.8f, -1.f));

    drawNumber(val, numberDefMatrix, uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix);
  }

  void HUD::drawSplashScreen(int splashScreenId,
                             GLuint uTextureLocation,
                             GLuint uMVMatrixLocation,
                             GLuint uMVPMatrixLocation,
                             GLuint uNormalMatrixLocation,
                             GLuint uLightPosLocation,
                             glm::mat4 *globalPMatrix,
                             glm::mat4 globalMVMatrix) const
  {
    splashScreen[splashScreenId].bind();
    MatrixManager screenMatrix{globalPMatrix, globalMVMatrix};
    screenMatrix.scale(glm::vec3{2.1f});
    screenMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
    splashScreen[splashScreenId].unbind();
  }

  void HUD::drawNumber(std::string parsedValue,
                       MatrixManager numberMatrix,
                       GLuint uTextureLocation,
                       GLuint uMVMatrixLocation,
                       GLuint uMVPMatrixLocation,
                       GLuint uNormalMatrixLocation,
                       GLuint uLightPosLocation,
                       glm::mat4 *globalPMatrix) const
  {
    float offset = std::ceil((float)parsedValue.size() / 2.f);
    offset = parsedValue.size() % 2 == 0 ? offset + 0.5f : offset;
    numberMatrix.translate(glm::vec3(-.75f * offset, 0.f, 0.f));
    std::for_each(parsedValue.begin(), parsedValue.end(), [this, &offset, &numberMatrix, &uTextureLocation, &uMVMatrixLocation, &uMVPMatrixLocation, &uNormalMatrixLocation, &uLightPosLocation, &globalPMatrix](const char &i)
                  {
                    numberMatrix.translate(glm::vec3(.75f,0.f, 0.f));
                    numbers[static_cast<int>(i - '0')].bind();
                    numberMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
                    numbers[static_cast<int>(i - '0')].unbind(); });
  }

  void HUD::clean()
  {
    playerInventory = nullptr;
    playerMoney = nullptr;
    playerMaxHealth = nullptr;
    playerCurrentHealth = nullptr;
    delete (playerInventory);
    delete (playerMoney);
    delete (playerMaxHealth);
    delete (playerCurrentHealth);
    hud.deleteTexture();
    coin.deleteTexture();
    sword.deleteTexture();
    shield.deleteTexture();
    std::for_each(numbers.begin(), numbers.end(), [](Texture &t)
                  { t.deleteTexture(); });
    std::for_each(lifeBar.begin(), lifeBar.end(), [](Texture &t)
                  { t.deleteTexture(); });
    std::for_each(splashScreen.begin(), splashScreen.end(), [](Texture &t)
                  { t.deleteTexture(); });
  }
}