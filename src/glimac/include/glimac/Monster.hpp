#pragma once
#include "glm.hpp"
#include <glimac/Entity.hpp>
#include <glimac/Character.hpp>
#include <glimac/MapGenerator.hpp>

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
            matrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
            matrix.rotate(90.f, glm::vec3(0.f, 1.f, 0.f));
            matrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
            texture.unbind();
        }
        void updateActions(float time, glm::vec2 playerPos, MapGenerator *map)
        {
            if (time - timeStamp < 1.f)
            {
                return;
            }

            timeStamp = time;

            auto distance = glm::distance2(playerPos, position);

            if (distance > 21)
            {
                return;
            }

            std::cout << "distance :" << distance << std::endl;

            if (distance == 1 || distance == 0) // FIGHT PHASE
            {
                return;
            }

            int distX = playerPos.x - position.x;
            int distY = playerPos.y - position.y;

            std::cout << "distX :" << distX << std::endl;
            std::cout << "distY :" << distY << std::endl;

            distX = distX > 0 ? 1 : distX < 0 ? -1
                                              : 0;
            distY = distY > 0 ? 1 : distY < 0 ? -1
                                              : 0;

            auto vec = glm::vec2(std::abs(distX) >= std::abs(distY) ? distX : 0, std::abs(distX) >= std::abs(distY) ? 0 : distY);

            if (!map->thereIsAWall(position + vec))
            {
                position += vec;
                std::cout << "target :" << vec << std::endl;
                return;
            }

            vec = glm::vec2(std::abs(distX) >= std::abs(distY) ? 0 : distX, std::abs(distX) >= std::abs(distY) ? distY : 0);

            if (!map->thereIsAWall(position + vec))
            {
                position += vec;
                std::cout << "target :" << vec << std::endl;
                return;
            }

            vec = glm::vec2(std::abs(distX) >= std::abs(distY) ? -distX : 0, std::abs(distX) >= std::abs(distY) ? 0 : -distY);

            if (!map->thereIsAWall(position + vec))
            {
                position += vec;
                std::cout << "target :" << vec << std::endl;
                return;
            }

            vec = glm::vec2(std::abs(distX) >= std::abs(distY) ? 0 : -distX, std::abs(distX) >= std::abs(distY) ? -distY : 0);

            if (!map->thereIsAWall(position + vec))
            {
                position += vec;
                std::cout << "target :" << vec << std::endl;
                return;
            }
        }
    };
}