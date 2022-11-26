#pragma once
#include "glm.hpp"
#include <glimac/Entity.hpp>
#include <glimac/Character.hpp>
#include <glimac/SDLWindowManager.hpp>

namespace glimac
{
    class Monster : public Entity, public Character
    {
    private:
        float timeStamp = 0.f;

    public:
        Monster(int id, glm::vec2 pos, std::string name, int atk, int ca, int pv, std::string texture) : Entity{id, pos, name, texture}, Character{atk, ca, pv} {}
        void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::vec2 origin, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const override
        {
            texture.bind();
            auto mVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)position.x, 0.f, (float)position.y));
            MatrixManager matrix{globalPMatrix, mVMatrix};
            matrix.rotate(90.f, glm::vec3(0.f, 1.f, 0.f));
            matrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
            texture.unbind();
        }
        void updateActions(float time, glm::vec2 playerPos)
        {
            if (time - timeStamp >= 1.f)
            {
                if (glm::distance2(playerPos, position) <= 21)
                {
                    auto vec = glm::normalize(glm::vec2(playerPos.x - position.x, playerPos.y - position.y));
                    if (position + vec != playerPos)
                        position += vec;
                }
                timeStamp = time;
            }
        }
    };
}