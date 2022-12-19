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
#include "glm.hpp"
#include <glimac/MapGenerator.hpp>

namespace glimac
{
    class SixAdjacencyCamera
    {
    private:
        int orientation;
        int initOrientation;
        glm::mat4 *globalMVMatrix;
        glm::vec2 playerPosition{0};
        MapGenerator *map;

    public:
        SixAdjacencyCamera() {}
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