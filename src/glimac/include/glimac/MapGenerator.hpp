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

namespace glimac
{
    class MapGenerator
    {
    private:
        std::vector<glm::vec2> walls;
        std::vector<glm::vec2> corridors;
        glm::vec2 start;
        glm::vec2 end;
        PPMParser map;
        Texture wallTexture;
        Texture groundTexture;
        Texture ceilingTexture;

    public:
        MapGenerator(PPMParser mapParsed) : map{mapParsed},
                                            wallTexture{"/home/thomas2dumont/Computer_Graphics/Dungeon-Master-Computer-Graphics-Project/assets/textures/wall.png", false},
                                            groundTexture{"/home/thomas2dumont/Computer_Graphics/Dungeon-Master-Computer-Graphics-Project/assets/textures/ground.png", false},
                                            ceilingTexture{"/home/thomas2dumont/Computer_Graphics/Dungeon-Master-Computer-Graphics-Project/assets/textures/ceiling.png", false}
        {
            auto pixels = map.getPixels();

            for (int i = 0; i < map.getWidth(); i++)
            {
                for (int j = 0; j < map.getHeight(); j++)
                {

                    auto pixel = pixels[i * map.getWidth() + j];

                    if (pixel == RGB(0, 0, 0))
                    {
                        walls.push_back(glm::vec2(i, j));
                        continue;
                    }
                    if (pixel == RGB(255, 255, 255))
                    {
                        corridors.push_back(glm::vec2(i, j));
                        continue;
                    }
                    if (pixel == RGB(255, 0, 0))
                    {
                        start = glm::vec2(i, j);
                        continue;
                    }
                    if (pixel == RGB(29, 255, 0))
                    {
                        end = glm::vec2(i, j);
                        continue;
                    }
                }
            }
        }

        void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const
        {
            wallTexture.bind();
            auto camMV = glm::rotate(globalMVMatrix, glm::radians(180.f), glm::vec3(0.f, 0.f, 1.f));
            camMV = glm::rotate(camMV, glm::radians(-90.f), glm::vec3(0.f, 1.f, 0.f));
            for (auto wall : walls)
            {
                auto wallMVMatrix = glm::translate(camMV, glm::vec3((float)wall.x - (float)start.x, 0.f, (float)wall.y - (float)start.y));
                MatrixManager wall1Matrix{globalPMatrix, wallMVMatrix};
                MatrixManager wall2Matrix{globalPMatrix, wallMVMatrix};
                MatrixManager wall3Matrix{globalPMatrix, wallMVMatrix};
                MatrixManager wall4Matrix{globalPMatrix, wallMVMatrix};
                wall2Matrix.rotate(90.f, glm::vec3(0.f, 1.f, 0.f));
                wall3Matrix.rotate(180.f, glm::vec3(0.f, 1.f, 0.f));
                wall4Matrix.rotate(270.f, glm::vec3(0.f, 1.f, 0.f));
                wall1Matrix.translate(glm::vec3(0.f, 0.f, 0.5f));
                wall2Matrix.translate(glm::vec3(0.f, 0.f, 0.5f));
                wall3Matrix.translate(glm::vec3(0.f, 0.f, 0.5f));
                wall4Matrix.translate(glm::vec3(0.f, 0.f, 0.5f));
                wall1Matrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation);
                wall2Matrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation);
                wall3Matrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation);
                wall4Matrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation);
            }
            wallTexture.unbind();

            ceilingTexture.bind();
            for (auto ceiling : corridors)
            {
                auto ceilingMVMatrix = glm::translate(camMV, glm::vec3((float)ceiling.x - (float)start.x, 0.f, (float)ceiling.y - (float)start.y));
                MatrixManager ceilingMatrix{globalPMatrix, ceilingMVMatrix};
                ceilingMatrix.rotate(90.f, glm::vec3(1.f, 0.f, 0.f));
                ceilingMatrix.translate(glm::vec3(0.f, 0.f, 0.5f));
                ceilingMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation);
            }
            ceilingTexture.unbind();

            groundTexture.bind();
            for (auto ground : corridors)
            {
                auto groundMVMatrix = glm::translate(camMV, glm::vec3((float)ground.x - (float)start.x, 0.f, (float)ground.y - (float)start.y));
                MatrixManager groundMatrix{globalPMatrix, groundMVMatrix};
                groundMatrix.rotate(-90.f, glm::vec3(1.f, 0.f, 0.f));
                groundMatrix.translate(glm::vec3(0.f, 0.f, 0.5f));
                groundMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation);
            }
            groundTexture.unbind();
        }

        void deleteMap()
        {
            wallTexture.deleteTexture();
            ceilingTexture.deleteTexture();
            groundTexture.deleteTexture();
        }
    };
}