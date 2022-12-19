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

#pragma once

#include "glimac/common.hpp"
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
        Treasure(int id, glm::vec2 pos, glm::vec2 initPos, int lvl, std::string name, int type, int value, std::string texture);
        void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const override
        {
            texture.bind();
            auto mVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)position.x, 0.f, (float)position.y));
            MatrixManager matrix{globalPMatrix, mVMatrix};
            matrix.rotate(rotation, glm::vec3(0.f, 1.f, 0.f));
            switch (type)
            {
            case MONEY:
                matrix.scale(glm::vec3(.25f, .25f, 0.f));
                break;
            case HEALTH:
            case MAX_HEALTH:
            case CA:
                matrix.scale(glm::vec3(.5f, .5f, 0.f));
                break;
            }
            matrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
            texture.unbind();
        }
        void updateActions(float time, Character *player, SixAdjacencyCamera *camera, MapGenerator *map) override
        {
            Entity::updateActions(time, player, camera, map);
        }
        TreasureType getType() const;
        int getValue() const;
        void setPosition(glm::vec2 pos);
    };
}