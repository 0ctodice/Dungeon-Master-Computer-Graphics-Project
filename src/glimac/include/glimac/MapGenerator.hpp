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

namespace glimac
{
    class MapGenerator
    {
    private:
        std::vector<glm::vec2> walls;
        std::vector<glm::vec2> waters;
        std::vector<glm::vec2> corridors;
        glm::vec2 start;
        glm::vec2 end;
        float animDoor = 0.f;
        PPMParser *map;
        SDLWindowManager *window;
        bool doorOpened = false;
        Texture wallTexture{"dungeon/wall.png", true};
        Texture groundTexture{"dungeon/ground.png", true};
        Texture waterTexture{"dungeon/water.png", true};
        Texture ceilingTexture{"dungeon/ceiling.png", true};
        Texture doorTexture{"dungeon/door.png", true};

        void drawWall(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const
        {
            MatrixManager wall1Matrix{globalPMatrix, globalMVMatrix};
            MatrixManager wall2Matrix{globalPMatrix, globalMVMatrix};
            MatrixManager wall3Matrix{globalPMatrix, globalMVMatrix};
            MatrixManager wall4Matrix{globalPMatrix, globalMVMatrix};
            wall2Matrix.rotate(90.f, glm::vec3(0.f, 1.f, 0.f));
            wall3Matrix.rotate(180.f, glm::vec3(0.f, 1.f, 0.f));
            wall4Matrix.rotate(270.f, glm::vec3(0.f, 1.f, 0.f));
            wall1Matrix.translate(glm::vec3(0.f, 0.f, 0.5f));
            wall2Matrix.translate(glm::vec3(0.f, 0.f, 0.5f));
            wall3Matrix.translate(glm::vec3(0.f, 0.f, 0.5f));
            wall4Matrix.translate(glm::vec3(0.f, 0.f, 0.5f));
            wall1Matrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
            wall2Matrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
            wall3Matrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
            wall4Matrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
        }

        void drawCeilling(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const
        {
            MatrixManager ceilingMatrix{globalPMatrix, globalMVMatrix};
            ceilingMatrix.rotate(-90.f, glm::vec3(1.f, 0.f, 0.f));
            ceilingMatrix.translate(glm::vec3(0.f, 0.f, 0.5f));
            ceilingMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
        }

        void drawFloor(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const
        {
            MatrixManager groundMatrix{globalPMatrix, globalMVMatrix};
            groundMatrix.rotate(90.f, glm::vec3(1.f, 0.f, 0.f));
            groundMatrix.translate(glm::vec3(0.f, 0.f, 0.5f));
            groundMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
            drawWall(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, glm::translate(globalMVMatrix, glm::vec3(0.f, -1.f, 0.f)));
        }

        void drawWater(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const
        {
            MatrixManager waterMatrix{globalPMatrix, globalMVMatrix};
            waterMatrix.rotate(90.f, glm::vec3(1.f, 0.f, 0.f));
            waterMatrix.translate(glm::vec3(0.f, 0.f, 0.75f));
            waterMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
        }

        void drawDoor(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const
        {
            MatrixManager doorMatrix{globalPMatrix, globalMVMatrix};
            doorMatrix.rotate(90.f, glm::vec3(0.f, 1.f, 0.f));
            doorMatrix.translate(glm::vec3(0.f, 0.f, -0.5f));
            doorMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
        }

    public:
        MapGenerator() = delete;
        MapGenerator(PPMParser *mapParsed, SDLWindowManager *window);
        ~MapGenerator();
        void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f));
        void clean();
        glm::vec2 getStartPosition() const;
        glm::vec2 getEndPosition() const;
        bool thereIsAWall(glm::vec2 pos) const;
        glm::vec2 getFirstDirection() const;
        void openDoor();
    };
}