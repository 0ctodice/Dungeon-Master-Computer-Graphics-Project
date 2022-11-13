#pragma once
#include "glm.hpp"
#include <glimac/Entity.hpp>
#include <glimac/MatrixManager.hpp>

namespace glimac
{
    enum TreasureType
    {
        MONEY = 1,
        HEALTH,
        MAX_HEALTH,
        CAC_WEAPON,
        CA
    };

    class Treasure : public Entity
    {
    private:
        TreasureType type;
        int value;

    public:
        Treasure(int id, glm::vec2 pos, std::string name, int type, int value, std::string texture) : Entity{id, pos, name, texture}, type{static_cast<TreasureType>(type)}, value{value} {}
        void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, glm::vec2 origin, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const override
        {
            texture.bind();
            auto mVMatrix = glm::translate(globalMVMatrix, glm::vec3((position.x - origin.x) * -1.f, 0.f, position.y - origin.y));
            MatrixManager matrix{globalPMatrix, mVMatrix};
            matrix.scale(glm::vec3(.5f));
            matrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation);
            matrix.rotate(90.f, glm::vec3(0.f, 1.F, 0.f));
            matrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation);
            texture.unbind();
        }
        TreasureType getType() const { return type; }
        int getValue() const { return value; }
    };

}