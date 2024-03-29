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

#include <glimac/SixAdjacencyCamera.hpp>

namespace glimac
{
    SixAdjacencyCamera::SixAdjacencyCamera(glm::vec2 playerDirection, glm::mat4 *MVMatrix, MapGenerator *map) : globalMVMatrix{MVMatrix}, map{map}
    {
        initOrientation = playerDirection.y == 1.f ? 0 : playerDirection.y == -1.f ? 2
                                                     : playerDirection.x == 1.f    ? 3
                                                                                   : 1;
        orientation = initOrientation;
    }

    SixAdjacencyCamera::~SixAdjacencyCamera()
    {
        globalMVMatrix = nullptr;
        map = nullptr;
        delete (globalMVMatrix);
        delete (map);
    }

    void SixAdjacencyCamera::moveFront()
    {
        glm::vec2 target;
        if (orientation > 0)
            target = abs(orientation) % 4 == 0 ? glm::vec2(0, 1) : abs(orientation) % 4 == 1 ? glm::vec2(-1, 0)
                                                               : abs(orientation) % 4 == 2   ? glm::vec2(0, -1)
                                                                                             : glm::vec2(1, 0);
        else
            target = abs(orientation) % 4 == 0 ? glm::vec2(0, 1) : abs(orientation) % 4 == 1 ? glm::vec2(1, 0)
                                                               : abs(orientation) % 4 == 2   ? glm::vec2(0, -1)
                                                                                             : glm::vec2(-1, 0);
        if (!map->thereIsAWall(playerPosition + target))
        {
            playerPosition += target;
            *globalMVMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, 1.f)) * *globalMVMatrix;
        }
    }

    void SixAdjacencyCamera::moveBack()
    {
        glm::vec2 target;
        if (orientation > 0)
            target = abs(orientation) % 4 == 0 ? glm::vec2(0, -1) : abs(orientation) % 4 == 1 ? glm::vec2(1, 0)
                                                                : abs(orientation) % 4 == 2   ? glm::vec2(0, 1)
                                                                                              : glm::vec2(-1, 0);
        else
            target = abs(orientation) % 4 == 0 ? glm::vec2(0, -1) : abs(orientation) % 4 == 1 ? glm::vec2(-1, 0)
                                                                : abs(orientation) % 4 == 2   ? glm::vec2(1, 0)
                                                                                              : glm::vec2(1, 0);
        if (!map->thereIsAWall(playerPosition + target))
        {
            playerPosition += target;
            *globalMVMatrix = glm::translate(glm::mat4(1.f), glm::vec3(0.f, 0.f, -1.f)) * *globalMVMatrix;
        }
    }

    void SixAdjacencyCamera::moveLeft()
    {
        glm::vec2 target;
        if (orientation > 0)
            target = abs(orientation) % 4 == 0 ? glm::vec2(1, 0) : abs(orientation) % 4 == 1 ? glm::vec2(0, 1)
                                                               : abs(orientation) % 4 == 2   ? glm::vec2(-1, 0)
                                                                                             : glm::vec2(0, -1);
        else
            target = abs(orientation) % 4 == 0 ? glm::vec2(1, 0) : abs(orientation) % 4 == 1 ? glm::vec2(0, -1)
                                                               : abs(orientation) % 4 == 2   ? glm::vec2(-1, 0)
                                                                                             : glm::vec2(0, 1);

        if (!map->thereIsAWall(playerPosition + target))
        {
            playerPosition += target;
            *globalMVMatrix = glm::translate(glm::mat4(1.f), glm::vec3(1.f, 0.f, 0.f)) * *globalMVMatrix;
        }
    }

    void SixAdjacencyCamera::moveRight()
    {
        glm::vec2 target;
        if (orientation > 0)
            target = abs(orientation) % 4 == 0 ? glm::vec2(-1, 0) : abs(orientation) % 4 == 1 ? glm::vec2(0, -1)
                                                                : abs(orientation) % 4 == 2   ? glm::vec2(1, 0)
                                                                                              : glm::vec2(0, 1);
        else
            target = abs(orientation) % 4 == 0 ? glm::vec2(-1, 0) : abs(orientation) % 4 == 1 ? glm::vec2(0, 1)
                                                                : abs(orientation) % 4 == 2   ? glm::vec2(1, 0)
                                                                                              : glm::vec2(0, -1);

        if (!map->thereIsAWall(playerPosition + target))
        {
            playerPosition += target;
            *globalMVMatrix = glm::translate(glm::mat4(1.f), glm::vec3(-1.f, 0.f, 0.f)) * *globalMVMatrix;
        }
    }

    void SixAdjacencyCamera::rotateLeft()
    {
        orientation--;
        *globalMVMatrix = glm::rotate(glm::mat4(1.f), glm::radians(-90.f), glm::vec3(0.f, 1.f, 0.f)) * *globalMVMatrix;
    }

    void SixAdjacencyCamera::rotateRight()
    {
        orientation++;
        *globalMVMatrix = glm::rotate(glm::mat4(1.f), glm::radians(90.f), glm::vec3(0.f, 1.f, 0.f)) * *globalMVMatrix;
    }

    glm::vec2 SixAdjacencyCamera::getFrontTile() const
    {
        glm::vec2 target;
        if (orientation > 0)
            target = abs(orientation) % 4 == 0 ? glm::vec2(0, 1) : abs(orientation) % 4 == 1 ? glm::vec2(-1, 0)
                                                               : abs(orientation) % 4 == 2   ? glm::vec2(0, -1)
                                                                                             : glm::vec2(1, 0);
        else
            target = abs(orientation) % 4 == 0 ? glm::vec2(0, 1) : abs(orientation) % 4 == 1 ? glm::vec2(1, 0)
                                                               : abs(orientation) % 4 == 2   ? glm::vec2(0, -1)
                                                                                             : glm::vec2(-1, 0);

        return playerPosition + target;
    }

    glm::vec2 SixAdjacencyCamera::getPlayerPosition() const { return playerPosition; }
}