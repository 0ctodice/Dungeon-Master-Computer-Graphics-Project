#include "glimac/common.hpp"
#include "glimac/DataParser.hpp"

namespace glimac
{
    DataParser::DataParser(std::string path)
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

    std::string DataParser::getLevelName() const { return levelName; }
    std::string DataParser::getMapFile() const { return mapFile; }
    std::vector<Treasure> DataParser::getTreasures() const { return treasures; }
    std::vector<Monster> DataParser::getMonsters() const { return monsters; }
    Treasure *DataParser::findTreasure(glm::vec2 position, glm::vec2 origin)
    {
        const auto it = std::find_if(treasures.begin(), treasures.end(), [position, origin](const Treasure &t)
                                     { return (t.Entity::getPosition().x - origin.x) * -1 == position.x && t.Entity::getPosition().y - origin.y == position.y; });
        if (it == treasures.end())
            return nullptr;
        Treasure *treasurePtr = new Treasure(*it);
        std::cout << "PICKED " << treasurePtr->Entity::getName() << std::endl;
        treasures.erase(std::remove_if(treasures.begin(), treasures.end(), [position, origin](const Treasure &t)
                                       { return (t.Entity::getPosition().x - origin.x) * -1 == position.x && t.Entity::getPosition().y - origin.y == position.y; }),
                        treasures.end());

        return treasurePtr;
    }
}