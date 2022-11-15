#pragma once
#include "glm.hpp"
#include <glimac/Entity.hpp>
#include <glimac/Character.hpp>

namespace glimac
{
    class Monster : public Entity, public Character
    {
    private:
    public:
        Monster(int id, glm::vec2 pos, std::string name, int atk, int ca, int pv, std::string texture) : Entity{id, pos, name, texture}, Character{atk, ca, pv} {}
        void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::vec2 origin, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const override
        {
        }
    };
}