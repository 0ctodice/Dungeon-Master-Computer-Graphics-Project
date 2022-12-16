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
#include <glimac/SixAdjacencyCamera.hpp>
#include <glimac/Player.hpp>

namespace glimac
{
    class DataParser
    {
    private:
        MapGenerator *map = nullptr;
        std::string commentaire;
        std::vector<std::string> mapFiles;
        int currentLevel = 0;
        // std::string levelName;
        // std::string mapFile;
        int nbTreasure;
        int goal;
        std::vector<Treasure> treasures;
        int nbMonster;
        std::vector<Monster> monsters;
        glm::vec2 playerPosition;
        int parseInt(std::ifstream *file)
        {
            std::string parser;
            std::getline(*file, parser, ':');
            return std::stoi(parser);
        }

        float parseFloat(std::ifstream *file)
        {
            std::string parser;
            std::getline(*file, parser, ':');
            return std::stof(parser);
        }

        bool checkDistance(glm::vec2 pos) const
        {
            auto dst = glm::distance2(playerPosition, pos);
            return dst < 21 && dst >= 0;
        }

    public:
        DataParser() {}
        DataParser(std::string path);
        std::string getMapFile() const;
        std::vector<Treasure> getTreasures() const;
        std::vector<Monster> getMonsters() const;
        Treasure *findTreasure(glm::vec2 position);
        Monster *findMonster(glm::vec2 position);
        void updateData(glm::vec2 origin);
        void addTreasure(Treasure t);
        void clean();
        void draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix = glm::mat4(1.f)) const;
        void idle(float time, Player *player, SixAdjacencyCamera *camera, MapGenerator *map);
        int getGoal() const;
        bool nextLevel();
        int getCurrentLevel() const;
    };
}