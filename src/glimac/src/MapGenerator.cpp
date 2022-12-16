#include <glimac/common.hpp>
#include <glimac/MapGenerator.hpp>

namespace glimac
{
    void MapGenerator::setMapToParsed(PPMParser *mapParsed)
    {
        map = mapParsed;

        wallE.clear();
        wallN.clear();
        wallS.clear();
        wallW.clear();
        water.clear();
        floor.clear();

        animDoor = 0.f;
        doorOpened = false;

        auto pixels = map->getPixels();

        for (int i = 0; i < map->getHeight(); i++)
        {
            for (int j = 0; j < map->getWidth(); j++)
            {
                auto pixel = pixels[i * map->getWidth() + j];

                Tile tile{glm::vec2(i, j)};

                if (pixel == RGB(0, 0, 0))
                {
                    if (i - 1 >= 0 && !(pixels[(i - 1) * map->getWidth() + j] == RGB(0, 0, 0)))
                        wallS.emplace(tile);
                    if (i + 1 < map->getHeight() && !(pixels[(i + 1) * map->getWidth() + j] == RGB(0, 0, 0)))
                        wallN.emplace(tile);
                    if (j - 1 >= 0 && !(pixels[i * map->getWidth() + (j - 1)] == RGB(0, 0, 0)))
                        wallE.emplace(tile);
                    if (j + 1 < map->getWidth() && !(pixels[i * map->getWidth() + (j + 1)] == RGB(0, 0, 0)))
                        wallW.emplace(tile);
                }
                if (pixel == RGB(0, 0, 255))
                {
                    water.emplace(tile);
                }
                if (pixel == RGB(255, 255, 255))
                {
                    floor.emplace(tile);
                }
                if (pixel == RGB(255, 0, 0))
                {
                    floor.emplace(tile);
                    start = glm::vec2(i, j);
                }
                if (pixel == RGB(0, 255, 0))
                {
                    floor.emplace(tile);
                    end = glm::vec2(i, j);
                }
            }
        }

        std::set<Tile> tmpE;

        std::for_each(wallE.begin(), wallE.end(), [this, &tmpE](const Tile &tile)
                      {
                        auto pos = tile.getPosition() - start;
                        pos.x *= -1;
                        Tile t{pos};
                        tmpE.emplace(t); });

        wallE = tmpE;

        std::set<Tile> tmpS;

        std::for_each(wallS.begin(), wallS.end(), [this, &tmpS](const Tile &tile)
                      {
                        auto pos = tile.getPosition() - start;
                        pos.x *= -1;
                        Tile t{pos};
                        tmpS.emplace(t); });

        wallS = tmpS;

        std::set<Tile> tmpN;

        std::for_each(wallN.begin(), wallN.end(), [this, &tmpN](const Tile &tile)
                      {
                        auto pos = tile.getPosition() - start;
                        pos.x *= -1;
                        Tile t{pos};
                        tmpN.emplace(t); });

        wallN = tmpN;

        std::set<Tile> tmpW;

        std::for_each(wallW.begin(), wallW.end(), [this, &tmpW](const Tile &tile)
                      {
                        auto pos = tile.getPosition() - start;
                        pos.x *= -1;
                        Tile t{pos};
                        tmpW.emplace(t); });

        wallW = tmpW;

        std::set<Tile> tmpWater;

        std::for_each(water.begin(), water.end(), [this, &tmpWater](const Tile &tile)
                      {
                        auto pos = tile.getPosition() - start;
                        pos.x *= -1;
                        Tile t{pos};
                        tmpWater.emplace(t); });

        water = tmpWater;

        std::set<Tile> tmpFloor;

        std::for_each(floor.begin(), floor.end(), [this, &tmpFloor](const Tile &tile)
                      {
                        auto pos = tile.getPosition() - start;
                        pos.x *= -1;
                        Tile t{pos};
                        tmpFloor.emplace(t); });

        floor = tmpFloor;

        Tile behindStart{glm::vec2{-1} * getFirstDirection()};

        if (behindStart.getPosition().x == -1)
        {
            wallS.emplace(behindStart);
        }
        else if (behindStart.getPosition().x == 1)
        {
            wallN.emplace(behindStart);
        }
        else if (behindStart.getPosition().y == -1)
        {
            wallW.emplace(behindStart);
        }
        else if (behindStart.getPosition().y == 1)
        {
            wallE.emplace(behindStart);
        }

        if (end.x == 0)
        {
            doorOrientation = 90.f;
            doorPosition = glm::vec2(end.x - 1, end.y);
        }
        else if (end.y == 0)
        {
            doorOrientation = 180.f;
            doorPosition = glm::vec2(end.x, end.y - 1);
        }
        else if (end.x > end.y)
        {
            doorOrientation = -90.f;
            doorPosition = glm::vec2(end.x + 1, end.y);
        }
        else
        {
            doorOrientation = 0.f;
            doorPosition = glm::vec2(end.x, end.y + 1);
        }

        end -= start;
        end = glm::vec2(end.x * -1, end.y);

        doorPosition -= start;
        doorPosition.x *= -1;
    }

    MapGenerator::~MapGenerator()
    {
        map = nullptr;
        window = nullptr;
        delete (map);
        delete (window);
    }

    void MapGenerator::idle(glm::vec2 playerPos)
    {
        playerPosition = playerPos;

        if (doorOpened && animDoor < 1.f)
        {
            animDoor += 0.005f * window->getTime();
        }
    }

    void MapGenerator::draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix)
    {
        if (checkDistance(end))
        {
            doorTexture.bind();

            auto doorMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)end.x, animDoor, (float)end.y));
            drawDoor(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, doorMVMatrix);

            doorTexture.unbind();
        }

        wallTexture.bind();

        std::for_each(wallE.begin(), wallE.end(), [this, &uTextureLocation, &uMVMatrixLocation, &uMVPMatrixLocation, &uNormalMatrixLocation, &uLightPosLocation, &globalPMatrix, &globalMVMatrix](const Tile &tile)
                      {
                        auto pos = tile.getPosition();
                        if(checkDistance(glm::vec2(pos))){
                            auto matrix = glm::translate(globalMVMatrix, glm::vec3((float)pos.x, 0.f, (float)pos.y));
                            drawWallE(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, matrix); 
                        } });

        std::for_each(wallW.begin(), wallW.end(), [this, &uTextureLocation, &uMVMatrixLocation, &uMVPMatrixLocation, &uNormalMatrixLocation, &uLightPosLocation, &globalPMatrix, &globalMVMatrix](const Tile &tile)
                      {
                        auto pos = tile.getPosition();
                        if(checkDistance(glm::vec2(pos))){
                            auto matrix = glm::translate(globalMVMatrix, glm::vec3((float)pos.x, 0.f, (float)pos.y));
                            drawWallW(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, matrix); 
                        } });

        std::for_each(wallN.begin(), wallN.end(), [this, &uTextureLocation, &uMVMatrixLocation, &uMVPMatrixLocation, &uNormalMatrixLocation, &uLightPosLocation, &globalPMatrix, &globalMVMatrix](const Tile &tile)
                      {
                        auto pos = tile.getPosition();
                        if(checkDistance(glm::vec2(pos))){
                            auto matrix = glm::translate(globalMVMatrix, glm::vec3((float)pos.x, 0.f, (float)pos.y));
                            drawWallN(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, matrix); 
                        } });

        std::for_each(wallS.begin(), wallS.end(), [this, &uTextureLocation, &uMVMatrixLocation, &uMVPMatrixLocation, &uNormalMatrixLocation, &uLightPosLocation, &globalPMatrix, &globalMVMatrix](const Tile &tile)
                      {
                        auto pos = tile.getPosition();
                        if(checkDistance(glm::vec2(pos))){
                            auto matrix = glm::translate(globalMVMatrix, glm::vec3((float)pos.x, 0.f, (float)pos.y));
                            drawWallS(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, matrix); 
                        } });

        wallTexture.unbind();

        groundTexture.bind();

        std::for_each(floor.begin(), floor.end(), [this, &uTextureLocation, &uMVMatrixLocation, &uMVPMatrixLocation, &uNormalMatrixLocation, &uLightPosLocation, &globalPMatrix, &globalMVMatrix](const Tile &tile)
                      {
                        auto pos = tile.getPosition();
                        if(checkDistance(glm::vec2(pos))){
                            auto matrix = glm::translate(globalMVMatrix, glm::vec3((float)pos.x, 0.f, (float)pos.y));
                            drawFloor(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, matrix); 
                        } });

        groundTexture.unbind();

        waterTexture.bind();

        std::for_each(water.begin(), water.end(), [this, &uTextureLocation, &uMVMatrixLocation, &uMVPMatrixLocation, &uNormalMatrixLocation, &uLightPosLocation, &globalPMatrix, &globalMVMatrix](const Tile &tile)
                      {
                        auto pos = tile.getPosition();
                        if(checkDistance(glm::vec2(pos))){
                            auto matrix = glm::translate(globalMVMatrix, glm::vec3((float)pos.x, 0.f, (float)pos.y));
                            drawWater(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, matrix); 
                        } });

        waterTexture.unbind();

        ceilingTexture.bind();

        std::for_each(floor.begin(), floor.end(), [this, &uTextureLocation, &uMVMatrixLocation, &uMVPMatrixLocation, &uNormalMatrixLocation, &uLightPosLocation, &globalPMatrix, &globalMVMatrix](const Tile &tile)
                      {
                        auto pos = tile.getPosition();
                        if(checkDistance(glm::vec2(pos))){
                            auto matrix = glm::translate(globalMVMatrix, glm::vec3((float)pos.x, 0.f, (float)pos.y));
                            drawCeiling(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, matrix); 
                        } });

        std::for_each(water.begin(), water.end(), [this, &uTextureLocation, &uMVMatrixLocation, &uMVPMatrixLocation, &uNormalMatrixLocation, &uLightPosLocation, &globalPMatrix, &globalMVMatrix](const Tile &tile)
                      {
                        auto pos = tile.getPosition();
                        if(checkDistance(glm::vec2(pos))){
                            auto matrix = glm::translate(globalMVMatrix, glm::vec3((float)pos.x, 0.f, (float)pos.y));
                            drawCeiling(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, matrix); 
                        } });

        ceilingTexture.unbind();
    }

    void MapGenerator::clean()
    {
        wallTexture.deleteTexture();
        ceilingTexture.deleteTexture();
        waterTexture.deleteTexture();
        groundTexture.deleteTexture();
    }

    glm::vec2 MapGenerator::getStartPosition() const
    {
        return start;
    }
    glm::vec2 MapGenerator::getEndPosition() const
    {
        return end;
    }

    bool MapGenerator::thereIsAWall(glm::vec2 pos) const
    {
        Tile tmp{pos};
        return std::find(wallS.begin(), wallS.end(), tmp) != wallS.end() ||
               std::find(wallE.begin(), wallE.end(), tmp) != wallE.end() ||
               std::find(wallN.begin(), wallN.end(), tmp) != wallN.end() ||
               std::find(wallW.begin(), wallW.end(), tmp) != wallW.end() ||
               std::find(water.begin(), water.end(), tmp) != water.end() ||
               (pos == doorPosition && (!doorOpened || animDoor < 1.f)) ||
               pos == glm::vec2(-1) * getFirstDirection();
    }

    glm::vec2 MapGenerator::getFirstDirection() const
    {
        auto i = start.x;
        auto j = start.y;
        return i == 0                      ? glm::vec2(-1.f, 0.f)
               : j == 0                    ? glm::vec2(0.f, 1.f)
               : i == map->getHeight() - 1 ? glm::vec2(1.f, 0.f)
               : j == map->getWidth() - 1  ? glm::vec2(0.f, -1.f)
                                           : glm::vec2(0.f);
    }

    void MapGenerator::openDoor()
    {
        doorOpened = true;
    }

    glm::vec2 MapGenerator::getDoorPosition()
    {
        return doorPosition;
    }
}