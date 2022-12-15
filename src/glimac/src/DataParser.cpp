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
        std::getline(file, mapFile);

        std::string parser;
        std::getline(file, parser);
        nbTreasure = std::stoi(parser);
        parser = "";

        for (int i = 0; i < nbTreasure; i++)
        {
            int id = parseInt(&file);
            int x = parseInt(&file);
            int y = parseInt(&file);
            glm::vec2 position{x, y};
            std::string name;
            std::getline(file, name, ':');
            std::getline(file, parser, ':');
            int type = std::stoi(parser);
            parser = "";
            int value = parseInt(&file);
            std::string texture;
            std::getline(file, texture);
            Treasure treasure{id, position, name, type, value, texture};
            treasures.push_back(treasure);
        }

        std::getline(file, parser);
        nbMonster = std::stoi(parser);
        parser = "";

        for (int i = 0; i < nbMonster; i++)
        {
            int id = parseInt(&file);
            glm::vec2 position{parseInt(&file), parseInt(&file)};
            std::string name;
            std::getline(file, name, ':');
            int atk = parseInt(&file);
            int ca = parseInt(&file);
            int pv = parseInt(&file);
            std::string texture;
            std::getline(file, texture);
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

    Monster *DataParser::findMonster(glm::vec2 position)
    {
        auto it = std::find_if(monsters.begin(), monsters.end(), [position](const Monster &m)
                               { return m.Entity::getPosition().x == position.x && m.Entity::getPosition().y == position.y; });

        return it == monsters.end() ? nullptr : &(*it);
    }

    void DataParser::addTreasure(Treasure t) { treasures.emplace_back(t); }

    void DataParser::clean()
    {
        std::for_each(monsters.begin(), monsters.end(), [](Monster monster)
                      { monster.Entity::deleteTexture(); });

        std::for_each(treasures.begin(), treasures.end(), [](Treasure treasure)
                      { treasure.Entity::deleteTexture(); });
    }

    void DataParser::draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix) const
    {
        std::for_each(monsters.begin(), monsters.end(), [this, &uTextureLocation, &uMVMatrixLocation, &uMVPMatrixLocation, &uNormalMatrixLocation, &uLightPosLocation, &globalPMatrix, &globalMVMatrix](const Monster &monster)
                      { if(checkDistance(monster.getPosition())){monster.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, globalMVMatrix);} });

        std::for_each(treasures.begin(), treasures.end(), [this, &uTextureLocation, &uMVMatrixLocation, &uMVPMatrixLocation, &uNormalMatrixLocation, &uLightPosLocation, &globalPMatrix, &globalMVMatrix](const Treasure &treasure)
                      { if(checkDistance(treasure.getPosition())){treasure.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, globalMVMatrix);} });
    }

    void DataParser::idle(float time, Character *player, SixAdjacencyCamera *camera, MapGenerator *map)
    {
        playerPosition = camera->getPlayerPosition();
        monsters.erase(std::remove_if(monsters.begin(), monsters.end(), [](Monster &m)
                                      {
                                        if(m.isDead()) {
                                            m.deleteTexture();
                                            return true;
                                        }
                                        return false; }),
                       monsters.end());

        std::for_each(treasures.begin(), treasures.end(), [&time, &player, &camera, &map](Treasure &treasure)
                      { treasure.updateActions(time, player, camera, map); });

        std::for_each(monsters.begin(), monsters.end(), [&time, &player, &camera, &map](Monster &monster)
                      { monster.updateActions(time, player, camera, map); });
    }
}