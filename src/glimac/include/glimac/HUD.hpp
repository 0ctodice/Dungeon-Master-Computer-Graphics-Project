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

        std::vector<Texture> splashScreen = {
            {"splash_screen/gamestart.png", true},
            {"splash_screen/treasure.png", true},
            {"splash_screen/gameover.png", true},
            {"splash_screen/theend.png", true}};

        Texture hud{"dungeon/hud.png", true};
        Texture coin{"dungeon/coin.png", true};
        Texture sword{"dungeon/swordicon.png", true};
        Texture shield{"dungeon/shieldicon.png", true};

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

        void drawSplashScreen(int splashScreenId,
                              GLuint uTextureLocation,
                              GLuint uMVMatrixLocation,
                              GLuint uMVPMatrixLocation,
                              GLuint uNormalMatrixLocation,
                              GLuint uLightPosLocation,
                              glm::mat4 *globalPMatrix,
                              glm::mat4 globalMVMatrix = glm::mat4(1.f)) const;

        void drawNumber(std::string parsedValue,
                        MatrixManager numberMatrix,
                        GLuint uTextureLocation,
                        GLuint uMVMatrixLocation,
                        GLuint uMVPMatrixLocation,
                        GLuint uNormalMatrixLocation,
                        GLuint uLightPosLocation,
                        glm::mat4 *globalPMatrix) const;
        void clean();
    };
}