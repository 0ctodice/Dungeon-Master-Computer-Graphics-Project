#pragma once

#include "glm.hpp"
#include <glimac/Texture.hpp>

namespace glimac
{
    class Entity
    {
    protected:
        int id;
        glm::vec2 position;
        std::string name;
        Texture texture;

    public:
        Entity(int id, glm::vec2 pos, std::string name, std::string texture) : id{id}, position{pos}, name{name}, texture{"/home/thomas2dumont/Computer_Graphics/Dungeon-Master-Computer-Graphics-Project/assets/textures/" + texture, false} {}
        virtual void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, glm::vec2 origin, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const = 0;
        void deleteTexture()
        {
            texture.deleteTexture();
        }
        glm::vec2 getPosition() const { return position; }
        std::string getName() const { return name; }
        Texture gettexture() const { return texture; }
    };
}