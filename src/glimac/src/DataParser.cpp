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

    void DataParser::updateData(glm::vec2 origin)
    {
        std::transform(monsters.begin(), monsters.end(), monsters.begin(), [origin](Monster &monster)
                       {
                        auto pos = monster.getPosition() - origin;
                        pos.x *=-1;
                        return Monster{monster.getId(), pos, monster.getName(), monster.getAtk(), monster.getCa(),monster.getPVMax(), monster.getTextureName()}; });

        std::transform(treasures.begin(), treasures.end(), treasures.begin(), [origin](Treasure &treasure)
                       {
            auto pos = treasure.getPosition() - origin;
            pos.x *= -1;
            return Treasure{treasure.getId(), pos, treasure.getName(), treasure.getType(), treasure.getValue(), treasure.getTextureName()}; });
    }

    Treasure *DataParser::findTreasure(glm::vec2 position)
    {
        const auto it = std::find_if(treasures.begin(), treasures.end(), [position](const Treasure &t)
                                     { return t.Entity::getPosition().x == position.x && t.Entity::getPosition().y == position.y; });
        if (it == treasures.end())
            return nullptr;
        Treasure *treasurePtr = new Treasure(*it);
        std::cout << "PICKED " << treasurePtr->Entity::getName() << std::endl;
        treasures.erase(std::remove_if(treasures.begin(), treasures.end(), [position](const Treasure &t)
                                       { return t.Entity::getPosition().x == position.x && t.Entity::getPosition().y == position.y; }),
                        treasures.end());

        return treasurePtr;
    }

    void DataParser::clean()
    {
        std::for_each(monsters.begin(), monsters.end(), [](Monster monster)
                      { monster.Entity::deleteTexture(); });

        std::for_each(treasures.begin(), treasures.end(), [](Treasure treasure)
                      { treasure.Entity::deleteTexture(); });
    }

    void DataParser::draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::vec2 origin, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix) const
    {
        std::for_each(monsters.begin(), monsters.end(), [&uTextureLocation, &uMVMatrixLocation, &uMVPMatrixLocation, &uNormalMatrixLocation, &uLightPosLocation, &origin, &globalPMatrix, &globalMVMatrix](const Monster &monster)
                      { monster.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, origin, globalPMatrix, globalMVMatrix); });

        std::for_each(treasures.begin(), treasures.end(), [&uTextureLocation, &uMVMatrixLocation, &uMVPMatrixLocation, &uNormalMatrixLocation, &uLightPosLocation, &origin, &globalPMatrix, &globalMVMatrix](const Treasure &treasure)
                      { treasure.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, origin, globalPMatrix, globalMVMatrix); });
    }

    void DataParser::idle(float time, glm::vec2 playerPos, MapGenerator *map)
    {
        std::for_each(monsters.begin(), monsters.end(), [&time, &playerPos, &map](Monster &monster)
                      { monster.updateActions(time, playerPos, map); });
    }
}