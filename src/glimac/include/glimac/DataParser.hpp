#pragma once

#include "glm.hpp"
#include <string>
#include <vector>
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
        DataParser(std::string path)
        {
            // CREATION DU STREAM
            std::ifstream file(path, std::ios::in);
            if (file.fail())
            {
                std::cout << "Could not open file: " << path << std::endl;
                return;
            }
            // RECUP DATA
            std::getline(file, levelName);
            levelName = levelName.substr(1);
            std::cout << "parsing data from " << levelName << std::endl;
            std::getline(file, mapFile);
            std::cout << "name of map file " << mapFile << std::endl;

            std::string parser;
            std::getline(file, parser);
            nbTreasure = std::stoi(parser);
            std::cout << "number of treasure " << nbTreasure << std::endl;
            parser = "";

            for (int i = 0; i < nbTreasure; i++)
            {
                int id = parseInt(&file);

                std::cout << "id " << id << std::endl;

                int x = parseInt(&file);
                int y = parseInt(&file);

                glm::vec2 position{x, y};

                std::cout << "position " << position << std::endl;

                std::string name;
                std::getline(file, name, ':');

                std::cout << "name " << name << std::endl;

                std::getline(file, parser, ':');
                int type = std::stoi(parser);
                parser = "";

                std::cout << "type " << type << std::endl;

                int value = parseInt(&file);

                std::cout << "value " << value << std::endl;

                std::string texture;
                std::getline(file, texture);

                std::cout << "texture " << texture << std::endl;

                Treasure treasure{id, position, name, type, value, texture};
                treasures.push_back(treasure);
            }

            std::getline(file, parser);
            nbMonster = std::stoi(parser);
            std::cout << "number of monster " << nbMonster << std::endl;

            parser = "";

            for (int i = 0; i < nbMonster; i++)
            {
                int id = parseInt(&file);

                std::cout << "id " << id << std::endl;

                glm::vec2 position{parseInt(&file), parseInt(&file)};

                std::cout << "position " << position << std::endl;

                std::string name;
                std::getline(file, name, ':');

                std::cout << "name " << name << std::endl;

                int atk = parseInt(&file);

                std::cout << "atk " << atk << std::endl;

                int ca = parseInt(&file);

                std::cout << "ca " << ca << std::endl;

                int pv = parseInt(&file);

                std::cout << "pv " << pv << std::endl;

                std::string texture;
                std::getline(file, texture);

                std::cout << "texture " << texture << std::endl;

                Monster monster{id, position, name, atk, ca, pv, texture};
                monsters.push_back(monster);
            }

            file.close();
        }

        std::string getLevelName() const { return levelName; }
        std::string getMapFile() const { return mapFile; }
        std::vector<Treasure> getTreasures() const { return treasures; }
        std::vector<Monster> getMonsters() const { return monsters; }
    };

}