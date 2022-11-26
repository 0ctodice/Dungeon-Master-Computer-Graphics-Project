#pragma once
#include "glm.hpp"
#include <glimac/MapGenerator.hpp>

namespace glimac
{
    class SixAdjacencyCamera
    {
    private:
        int orientation;
        glm::mat4 *globalMVMatrix;
        glm::vec2 playerPosition{0};
        MapGenerator *map;

    public:
        SixAdjacencyCamera() = delete;
        SixAdjacencyCamera(glm::vec2 playerDirection, glm::mat4 *MVMatrix, MapGenerator *map);
        ~SixAdjacencyCamera();

        void moveFront();
        void moveBack();
        void moveLeft();
        void moveRight();
        void rotateLeft();
        void rotateRight();

        glm::vec2 getFrontTile() const;
        glm::vec2 getPlayerPosition() const;
    };

}