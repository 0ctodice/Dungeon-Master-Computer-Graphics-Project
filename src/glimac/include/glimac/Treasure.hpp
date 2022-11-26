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
        Treasure() = delete;
        Treasure(int id, glm::vec2 pos, std::string name, int type, int value, std::string texture);
        void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::vec2 origin, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const override
        {
            texture.bind();
            auto mVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)position.x, 0.f, (float)position.y));
            MatrixManager matrix{globalPMatrix, mVMatrix};
            matrix.scale(glm::vec3(.5f));
            matrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
            matrix.rotate(90.f, glm::vec3(0.f, 1.F, 0.f));
            matrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
            texture.unbind();
        }
        TreasureType getType() const;
        int getValue() const;
    };

}