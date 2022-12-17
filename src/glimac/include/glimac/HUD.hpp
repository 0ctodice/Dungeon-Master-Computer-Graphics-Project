#pragma once

#include "glm.hpp"
#include <glimac/Texture.hpp>
#include <glimac/Treasure.hpp>
#include <glimac/Texture.hpp>
#include <vector>

namespace glimac
{
    class HUD
    {
    private:
        std::pair<int, int> window;
        std::pair<Treasure, Treasure> *playerInventory;
        int *playerMoney;
        int *playerMaxHealth;
        int *playerCurrentHealth;
        std::vector<Texture> numbers = {
            {"numbers/0.png", true},
            {"numbers/1.png", true},
            {"numbers/2.png", true},
            {"numbers/3.png", true},
            {"numbers/4.png", true},
            {"numbers/5.png", true},
            {"numbers/6.png", true},
            {"numbers/7.png", true},
            {"numbers/8.png", true},
            {"numbers/9.png", true},
        };
        std::vector<Texture> lifeBar = {
            {"dungeon/lifebar/lb_0.png", true},
            {"dungeon/lifebar/lb_1.png", true},
            {"dungeon/lifebar/lb_2.png", true},
            {"dungeon/lifebar/lb_3.png", true},
            {"dungeon/lifebar/lb_4.png", true},
            {"dungeon/lifebar/lb_5.png", true},
            {"dungeon/lifebar/lb_6.png", true}};

        Texture hud{"dungeon/hud.png", true};
        Texture coin{"dungeon/coin.png", true};
        Texture sword{"dungeon/swordicon.png", true};
        Texture shield{"dungeon/shieldicon.png", true};

        void drawNumber(std::string parsedValue,
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

    public:
        HUD(int width, int height, std::pair<Treasure, Treasure> *invn, int *money, int *maxH, int *H);
        ~HUD();
        void draw(GLuint uTextureLocation,
                  GLuint uMVMatrixLocation,
                  GLuint uMVPMatrixLocation,
                  GLuint uNormalMatrixLocation,
                  GLuint uLightPosLocation,
                  glm::mat4 *globalPMatrix,
                  glm::mat4 globalMVMatrix = glm::mat4(1.f)) const;
        void clean();
    };
}