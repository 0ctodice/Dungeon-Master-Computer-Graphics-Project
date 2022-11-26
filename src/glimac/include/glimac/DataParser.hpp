#pragma once

#include "glm.hpp"
#include <string>
#include <vector>
#include <algorithm>
#include <stdio.h>
#include <fstream>
#include <iostream>
#include <glimac/Treasure.hpp>
#include <glimac/Monster.hpp>
#include <glimac/MapGenerator.hpp>

namespace glimac
{
    class DataParser
    {
    private:
        MapGenerator *map = nullptr;
        std::string levelName;
        std::string mapFile;
        int nbTreasure;
        std::vector<Treasure> treasures;
        int nbMonster;
        std::vector<Monster> monsters;

        int parseInt(std::ifstream *file)
        {
            std::string parser;
            std::getline(*file, parser, ':');
            return std::stoi(parser);
        }

    public:
        DataParser() = delete;
        DataParser(std::string path);
        std::string getLevelName() const;
        std::string getMapFile() const;
        std::vector<Treasure> getTreasures() const;
        std::vector<Monster> getMonsters() const;
        Treasure *findTreasure(glm::vec2 position);
        void updateData(glm::vec2 origin);
        void clean();
        void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::vec2 origin, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const;
        void idle(float time, glm::vec2 playerPos);
    };
}