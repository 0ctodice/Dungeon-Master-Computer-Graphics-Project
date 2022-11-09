#pragma once

#include "glm.hpp"
#include <GL/glew.h>
#include <iostream>
#include <glimac/FilePath.hpp>
#include <glimac/PPMParser.hpp>
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

    public:
        MapGenerator(PPMParser mapParsed, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) : map{mapParsed}
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
    };
}