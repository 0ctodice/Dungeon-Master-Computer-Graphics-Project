#pragma once

#include "glimac/common.hpp"
#include <glimac/Texture.hpp>
#include <glimac/Tile.hpp>
#include <set>
#include <algorithm>

namespace glimac
{

    class TileSet
    {
    private:
        std::set<Tile> tiles;
        float orientation;
        glm::vec3 vectorOrientation;
        bool checkDistance(glm::vec2 pos, glm::vec2 playerPosition)
        {
            auto dst = glm::distance2(playerPosition, pos);
            return dst < 21 && dst >= 0;
        }

    public:
        TileSet() = delete;
        TileSet(float ori, glm::vec3 vec);
        void resetSet();
        void addTile(glm::vec2 pos);
        void updateRender(glm::vec2 playerPosition);
        void updateData(glm::vec2 origin);
        bool thereIsATile(Tile tile) const;
        void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const;
    };

}
