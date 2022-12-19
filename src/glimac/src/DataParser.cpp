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
        std::getline(file, commentaire);
        commentaire = commentaire.substr(1);

        std::string parser;
        std::getline(file, parser);

        int nbLevels = std::stoi(parser);
        parser = "";

        for (int i = 0; i < nbLevels; i++)
        {
            std::string tmp;
            std::getline(file, tmp, ':');
            mapFiles.push_back(tmp);
            std::cout << tmp << std::endl;
            tmp = "";

            std::getline(file, tmp);
            goals.push_back(std::stoi(tmp));
        }
        std::getline(file, parser);

        nbTreasure = std::stoi(parser);
        parser = "";

        for (int i = 0; i < nbTreasure; i++)
        {
            int id = parseInt(&file);
            int x = parseInt(&file);
            int y = parseInt(&file);
            glm::vec2 position{x, y};
            int lvl = parseInt(&file);
            std::string name;
            std::getline(file, name, ':');
            std::getline(file, parser, ':');
            int type = std::stoi(parser);
            parser = "";
            int value = parseInt(&file);
            std::string texture;
            std::getline(file, texture);
            Treasure treasure{id, position, position, lvl, name, type, value, texture};
            treasures.push_back(treasure);
        }

        std::getline(file, parser);
        nbMonster = std::stoi(parser);
        parser = "";

        for (int i = 0; i < nbMonster; i++)
        {
            int id = parseInt(&file);
            glm::vec2 position{parseInt(&file), parseInt(&file)};
            int lvl = parseInt(&file);
            std::string name;
            std::getline(file, name, ':');
            int atk = parseInt(&file);
            int ca = parseInt(&file);
            int pv = parseInt(&file);
            float actionTime = parseFloat(&file);
            int value = parseInt(&file);
            std::string texture;
            std::getline(file, texture);
            Monster monster{id, position, position, lvl, name, atk, ca, pv, actionTime, value, texture};
            monsters.push_back(monster);
        }

        file.close();
    }

    std::string DataParser::getMapFile() const { return mapFiles[currentLevel]; }
    std::vector<Treasure> DataParser::getTreasures() const { return treasures; }
    std::vector<Monster> DataParser::getMonsters() const { return monsters; }

    void DataParser::updateData(glm::vec2 origin)
    {
        std::transform(monsters.begin(), monsters.end(), monsters.begin(), [this, origin](Monster &monster)
                       {
                        if(monster.getLevelStage() != getCurrentLevel()){
                            return monster;
                        }
                        auto pos = monster.getInitialPosition() - origin;
                        pos.x *=-1;
                        return Monster{monster.getId(), pos,monster.getInitialPosition(), monster.getLevelStage(), monster.getName(), monster.getAtk(), monster.getCa(),monster.getPVMax(), monster.getActionTime(), monster.getValue(), monster.getTextureName()}; });

        std::transform(treasures.begin(), treasures.end(), treasures.begin(), [this, origin](Treasure &treasure)
                       {
                        if(treasure.getLevelStage() != getCurrentLevel()){
                            return treasure;
                        }
                        auto pos = treasure.getInitialPosition() - origin;
                        pos.x *= -1;
                        return Treasure{treasure.getId(), pos,treasure.getInitialPosition(), treasure.getLevelStage(), treasure.getName(), treasure.getType(), treasure.getValue(), treasure.getTextureName()}; });
    }

    Treasure *DataParser::findTreasure(glm::vec2 position)
    {
        const auto it = std::find_if(treasures.begin(), treasures.end(), [this, position](const Treasure &t)
                                     { return t.getLevelStage() == getCurrentLevel() && t.Entity::getPosition().x == position.x && t.Entity::getPosition().y == position.y; });
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
        auto it = std::find_if(monsters.begin(), monsters.end(), [this, position](const Monster &m)
                               { return m.getLevelStage() == getCurrentLevel() && m.Entity::getPosition().x == position.x && m.Entity::getPosition().y == position.y; });

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
                      { if(monster.getLevelStage() == getCurrentLevel() && checkDistance(monster.getPosition())){monster.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, globalMVMatrix);} });

        std::for_each(treasures.begin(), treasures.end(), [this, &uTextureLocation, &uMVMatrixLocation, &uMVPMatrixLocation, &uNormalMatrixLocation, &uLightPosLocation, &globalPMatrix, &globalMVMatrix](const Treasure &treasure)
                      { if(treasure.getLevelStage() == getCurrentLevel() && checkDistance(treasure.getPosition())){treasure.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, globalMVMatrix);} });
    }

    void DataParser::idle(float time, Player *player, SixAdjacencyCamera *camera, MapGenerator *map)
    {
        playerPosition = camera->getPlayerPosition();
        monsters.erase(std::remove_if(monsters.begin(), monsters.end(), [player](Monster &m)
                                      {
                                        if(m.isDead()) {
                                            m.deleteTexture();
                                            player->setMoney(m.getValue());
                                            return true;
                                        }
                                        return false; }),
                       monsters.end());

        std::for_each(treasures.begin(), treasures.end(), [this, &time, &player, &camera, &map](Treasure &treasure)
                      {if(treasure.getLevelStage() == getCurrentLevel()) treasure.updateActions(time, player, camera, map); });

        std::for_each(monsters.begin(), monsters.end(), [this, &time, &player, &camera, &map](Monster &monster)
                      { if(monster.getLevelStage() == getCurrentLevel()) monster.updateActions(time, player, camera, map); });
    }
    int DataParser::getGoal() const { return goals[currentLevel]; }
    bool DataParser::nextLevel()
    {
        currentLevel++;
        return currentLevel == mapFiles.size();
    }
    int DataParser::getCurrentLevel() const { return currentLevel; }
}