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
        glm::vec2 start{0};
        glm::vec2 end;
        PPMParser map;
        Texture wallTexture{"/home/thomas2dumont/Computer_Graphics/Dungeon-Master-Computer-Graphics-Project/assets/textures/wall.png", false};
        Texture groundTexture{"/home/thomas2dumont/Computer_Graphics/Dungeon-Master-Computer-Graphics-Project/assets/textures/ground.png", false};
        Texture ceilingTexture{"/home/thomas2dumont/Computer_Graphics/Dungeon-Master-Computer-Graphics-Project/assets/textures/ceiling.png", false};

    public:
        MapGenerator(PPMParser mapParsed) : map{mapParsed}
        {
            auto pixels = map.getPixels();

            for (int i = 0; i < map.getHeight(); i++)
            {
                for (int j = 0; j < map.getWidth(); j++)
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
                    if (pixel == RGB(0, 255, 0))
                    {
                        end = glm::vec2(i, j);
                        continue;
                    }
                }
            }
            auto origin = start;

            std::transform(walls.begin(), walls.end(), walls.begin(), [origin](glm::vec2 wall)
                           { auto pos = wall - origin; 
                           std::cout << pos << std::endl;
                           return glm::vec2(pos.x, pos.y*-1); });

            std::transform(corridors.begin(), corridors.end(), corridors.begin(), [origin](glm::vec2 corridor)
                           { auto pos = corridor - origin; 
                           return glm::vec2(pos.x, pos.y*-1); });

            end -= start;
            end = glm::vec2(end.x, end.y * -1);
        }

        void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f))
        {
            wallTexture.bind();
            for (auto wall : walls)
            {
                auto wallMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)wall.x, 0.f, (float)wall.y));
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
                auto ceilingMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)ceiling.x, 0.f, (float)ceiling.y));
                MatrixManager ceilingMatrix{globalPMatrix, ceilingMVMatrix};
                ceilingMatrix.rotate(-90.f, glm::vec3(1.f, 0.f, 0.f));
                ceilingMatrix.translate(glm::vec3(0.f, 0.f, 0.5f));
                ceilingMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation);
            }
            // TEXUTRE FOR START

            MatrixManager startCeilingMatrix{globalPMatrix, globalMVMatrix};
            startCeilingMatrix.rotate(-90.f, glm::vec3(1.f, 0.f, 0.f));
            startCeilingMatrix.translate(glm::vec3(0.f, 0.f, 0.5f));
            startCeilingMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation);

            // TEXTURE FOR END

            auto ceilingMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)end.x, 0.f, (float)end.y));
            MatrixManager endCeilingMatrix{globalPMatrix, ceilingMVMatrix};
            endCeilingMatrix.rotate(-90.f, glm::vec3(1.f, 0.f, 0.f));
            endCeilingMatrix.translate(glm::vec3(0.f, 0.f, 0.5f));
            endCeilingMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation);

            ceilingTexture.unbind();

            groundTexture.bind();

            for (auto ground : corridors)
            {
                auto groundMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)ground.x, 0.f, (float)ground.y));
                MatrixManager groundMatrix{globalPMatrix, groundMVMatrix};
                groundMatrix.rotate(90.f, glm::vec3(1.f, 0.f, 0.f));
                groundMatrix.translate(glm::vec3(0.f, 0.f, 0.5f));
                groundMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation);
            }

            // TEXUTRE FOR START

            MatrixManager startGroundMatrix{globalPMatrix, globalMVMatrix};
            startGroundMatrix.rotate(90.f, glm::vec3(1.f, 0.f, 0.f));
            startGroundMatrix.translate(glm::vec3(0.f, 0.f, 0.5f));
            startGroundMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation);

            // TEXTURE FOR END

            auto groundMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)end.x, 0.f, (float)end.y));
            MatrixManager endGroundMatrix{globalPMatrix, groundMVMatrix};
            endGroundMatrix.rotate(90.f, glm::vec3(1.f, 0.f, 0.f));
            endGroundMatrix.translate(glm::vec3(0.f, 0.f, 0.5f));
            endGroundMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation);

            groundTexture.unbind();
        }

        void deleteMap()
        {
            wallTexture.deleteTexture();
            ceilingTexture.deleteTexture();
            groundTexture.deleteTexture();
        }

        bool thereIsAWall(glm::vec2 pos) const
        {
            std::cout << (std::find(walls.begin(), walls.end(), pos) != walls.end()) << std::endl;
            return std::find(walls.begin(), walls.end(), pos) != walls.end();
        }

        glm::vec2 getFirstDirection() const
        {
            auto i = start.x;
            auto j = start.y;
            return i == 0                     ? glm::vec2(1.f, 0.f)
                   : j == 0                   ? glm::vec2(0.f, 1.f)
                   : i == map.getHeight() - 1 ? glm::vec2(-1.f, 0.f)
                   : j == map.getWidth() - 1  ? glm::vec2(0.f, -1.f)
                                              : glm::vec2(0.f);
        }
    };
}