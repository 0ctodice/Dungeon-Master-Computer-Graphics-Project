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
        Texture hud{"dungeon/hud.png", true};
        Texture coin{"dungeon/coin.png", true};

    public:
        HUD(int width, int height, std::pair<Treasure, Treasure> *invn, int *money);
        void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const;
        void clean();
    };
}