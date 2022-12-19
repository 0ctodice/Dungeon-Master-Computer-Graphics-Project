#pragma once
#include "glm.hpp"
#include <glimac/Entity.hpp>
#include <glimac/Character.hpp>

namespace glimac
{
    class Monster : public Entity, public Character
    {
    private:
        float timeStamp = 0.f;
        float actionTime = 0.f;
        int value = 0;

    public:
        Monster(int id, glm::vec2 pos, glm::vec2 initPos, int lvl, std::string name, int atk, int ca, int pv, float actTime, int val, std::string texture) : Entity{id, pos, initPos, lvl, name, texture}, Character{atk, ca, pv}, actionTime{actTime}, value{val} {}

        void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const override
        {
            texture.bind();
            auto mVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)position.x, 0.f, (float)position.y));
            MatrixManager matrix{globalPMatrix, mVMatrix};
            matrix.rotate(rotation, glm::vec3(0.f, 1.f, 0.f));
            matrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
            texture.unbind();
        }

        void updateActions(float time, Character *player, SixAdjacencyCamera *camera, MapGenerator *map) override
        {
            Entity::updateActions(time, player, camera, map);

            if (time - timeStamp < actionTime)
            {
                return;
            }

            timeStamp = time;

            auto playerPos = camera->getPlayerPosition();

            auto distance = glm::distance2(playerPos, position);

            if (distance > 21)
            {
                return;
            }

            if (distance == 1 || distance == 0) // FIGHT PHASE
            {
                player->takeDamage(atk);
                return;
            }

            int distX = playerPos.x - position.x;
            int distY = playerPos.y - position.y;

            distX = distX > 0 ? 1 : distX < 0 ? -1
                                              : 0;
            distY = distY > 0 ? 1 : distY < 0 ? -1
                                              : 0;

            auto vec = glm::vec2(std::abs(distX) >= std::abs(distY) ? distX : 0, std::abs(distX) >= std::abs(distY) ? 0 : distY);

            if (!map->thereIsAWall(position + vec))
            {
                position += vec;
                return;
            }

            vec = glm::vec2(std::abs(distX) >= std::abs(distY) ? 0 : distX, std::abs(distX) >= std::abs(distY) ? distY : 0);

            if (!map->thereIsAWall(position + vec))
            {
                position += vec;
                return;
            }

            vec = glm::vec2(std::abs(distX) >= std::abs(distY) ? -distX : 0, std::abs(distX) >= std::abs(distY) ? 0 : -distY);

            if (!map->thereIsAWall(position + vec))
            {
                position += vec;
                return;
            }

            vec = glm::vec2(std::abs(distX) >= std::abs(distY) ? 0 : -distX, std::abs(distX) >= std::abs(distY) ? -distY : 0);

            if (!map->thereIsAWall(position + vec))
            {
                position += vec;
                return;
            }
        }

        float getActionTime() const { return actionTime; }
        int getValue() const { return value; }
    };
}