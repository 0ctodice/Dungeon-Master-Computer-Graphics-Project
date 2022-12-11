#pragma once

#include "glm.hpp"
#include <glimac/Texture.hpp>
#include <glimac/Treasure.hpp>

namespace glimac
{
    class HUD
    {
    private:
        std::pair<int, int> window;
        std::pair<Treasure, Treasure> *playerInventory;
        float ratio;

    public:
        HUD(int width, int height, std::pair<Treasure, Treasure> *invn, float ratio);
        void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const;
        void clean();
    };
}