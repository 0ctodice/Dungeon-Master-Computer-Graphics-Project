#pragma once

#include "glm.hpp"
#include <glimac/Texture.hpp>
#include <glimac/MapGenerator.hpp>
#include <glimac/SixAdjacencyCamera.hpp>

namespace glimac
{
    class Entity
    {
    protected:
        int id;
        glm::vec2 position;
        std::string name;
        std::string textureName;
        Texture texture;
        float rotation = 0.f;

    public:
        Entity() = delete;
        Entity(int id, glm::vec2 pos, std::string name, std::string texture);
        virtual void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::vec2 origin, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const = 0;
        virtual void updateActions(float time, SixAdjacencyCamera *player, MapGenerator *map);
        void deleteTexture();
        int getId() const;
        glm::vec2 getPosition() const;
        std::string getName() const;
        Texture getTexture() const;
        std::string getTextureName() const;
    };
}