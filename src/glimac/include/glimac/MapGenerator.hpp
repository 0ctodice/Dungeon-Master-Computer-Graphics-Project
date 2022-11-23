#pragma once

#include "glm.hpp"
#include <GL/glew.h>
#include <iostream>
#include <glimac/FilePath.hpp>
#include <glimac/PPMParser.hpp>
#include <glimac/MatrixManager.hpp>
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
        std::vector<glm::vec2> corridors;
        glm::vec2 start;
        glm::vec2 end;
        PPMParser *map;
        Texture wallTexture{"/home/thomas2dumont/Computer_Graphics/Dungeon-Master-Computer-Graphics-Project/assets/textures/wall.png", false};
        Texture groundTexture{"/home/thomas2dumont/Computer_Graphics/Dungeon-Master-Computer-Graphics-Project/assets/textures/ground.png", false};
        Texture ceilingTexture{"/home/thomas2dumont/Computer_Graphics/Dungeon-Master-Computer-Graphics-Project/assets/textures/ceiling.png", false};

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
        }

    public:
        MapGenerator() = delete;
        MapGenerator(PPMParser *mapParsed);
        ~MapGenerator();
        void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const;
        void deleteMap();
        glm::vec2 getStartPosition() const;
        bool thereIsAWall(glm::vec2 pos) const;
        glm::vec2 getFirstDirection() const;
    };
}