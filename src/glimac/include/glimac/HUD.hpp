#pragma once

#include "glm.hpp"
#include <glimac/Texture.hpp>

namespace glimac
{
    class HUD
    {
    private:
        Texture texture{"door.png", true};
        std::pair<int, int> window;

    public:
        HUD(int width, int height);
        void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const;
        void deleteTexture();
    };
}