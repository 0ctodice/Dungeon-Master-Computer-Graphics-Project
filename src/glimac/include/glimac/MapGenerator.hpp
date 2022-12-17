#pragma once

#include "glm.hpp"
#include <GL/glew.h>
#include <iostream>
#include <glimac/FilePath.hpp>
#include <glimac/PPMParser.hpp>
#include <glimac/MatrixManager.hpp>
#include <glimac/SDLWindowManager.hpp>
#include <glimac/Texture.hpp>
#include <stdio.h>
#include <fstream>
#include <vector>
#include <algorithm>
#include <map>
#include <set>
#include <glimac/Tile.hpp>
#include <glimac/TileSet.hpp>

namespace glimac
{
    enum TILETYPE
    {
        WALL_N,
        WALL_S,
        WALL_W,
        WALL_E,
        WATER,
        FLOOR,
        CEILING
    };

    class MapGenerator
    {
    private:
        TileSet wallN{270.f, glm::vec3(0.f, 1.f, 0.f)};
        TileSet wallE{180.f, glm::vec3(0.f, 1.f, 0.f)};
        TileSet wallS{90.f, glm::vec3(0.f, 1.f, 0.f)};
        TileSet wallW{0.f, glm::vec3(0.f, 1.f, 0.f)};
        TileSet water{90.f, glm::vec3(1.f, 0.f, 0.f)};
        TileSet floor{90.f, glm::vec3(1.f, 0.f, 0.f)};
        TileSet ceiling{-90.f, glm::vec3(1.f, 0.f, 0.f)};
        glm::vec2 start;
        glm::vec2 end;
        glm::vec2 playerPosition;
        glm::vec2 doorPosition;
        float doorOrientation = 0.f;
        float animDoor = 0.f;
        PPMParser *map;
        SDLWindowManager *window;
        bool doorOpened = false;
        Texture wallTexture{"dungeon/wall.png", true};
        Texture groundTexture{"dungeon/ground.png", true};
        Texture waterTexture{"dungeon/water.png", true};
        Texture ceilingTexture{"dungeon/ceiling.png", true};
        Texture doorTexture{"dungeon/door.png", true};

    public:
        MapGenerator(SDLWindowManager *window) : window{window} {}
        ~MapGenerator();
        void setMapToParsed(PPMParser *mapParsed);
        void idle(glm::vec2 playerPos);
        void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f));
        void clean();
        glm::vec2 getStartPosition() const;
        glm::vec2 getEndPosition() const;
        bool thereIsAWall(glm::vec2 pos) const;
        glm::vec2 getFirstDirection() const;
        void openDoor();
        glm::vec2 getDoorPosition();
    };
}