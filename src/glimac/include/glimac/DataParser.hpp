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

namespace glimac
{
    class DataParser
    {
    private:
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
        Treasure *findTreasure(glm::vec2 position, glm::vec2 origin);
    };
}