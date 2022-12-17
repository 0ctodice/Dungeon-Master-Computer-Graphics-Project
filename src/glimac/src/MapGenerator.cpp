#include <glimac/common.hpp>
#include <glimac/MapGenerator.hpp>

namespace glimac
{
    void MapGenerator::setMapToParsed(PPMParser *mapParsed)
    {
        map = mapParsed;

        wallE.resetSet();
        wallN.resetSet();
        wallS.resetSet();
        wallW.resetSet();
        water.resetSet();
        floor.resetSet();
        ceiling.resetSet();

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
                        wallS.addTile(glm::vec2(i, j));
                    if (i + 1 < map->getHeight() && !(pixels[(i + 1) * map->getWidth() + j] == RGB(0, 0, 0)))
                        wallN.addTile(glm::vec2(i, j));
                    if (j - 1 >= 0 && !(pixels[i * map->getWidth() + (j - 1)] == RGB(0, 0, 0)))
                        wallE.addTile(glm::vec2(i, j));
                    if (j + 1 < map->getWidth() && !(pixels[i * map->getWidth() + (j + 1)] == RGB(0, 0, 0)))
                        wallW.addTile(glm::vec2(i, j));
                    continue;
                }
                if (pixel == RGB(0, 0, 255))
                {
                    water.addTile(glm::vec2(i, j));
                    ceiling.addTile(glm::vec2(i, j));
                    continue;
                }
                if (pixel == RGB(255, 0, 0))
                {
                    start = glm::vec2(i, j);
                }
                if (pixel == RGB(0, 255, 0))
                {
                    end = glm::vec2(i, j);
                }
                floor.addTile(glm::vec2(i, j));
                ceiling.addTile(glm::vec2(i, j));
            }
        }

        wallE.updateData(start);
        wallS.updateData(start);
        wallN.updateData(start);
        wallW.updateData(start);
        water.updateData(start);
        floor.updateData(start);
        ceiling.updateData(start);

        auto behindStart = glm::vec2{-1} * getFirstDirection();

        if (behindStart.x == -1)
        {
            wallS.addTile(behindStart);
        }
        else if (behindStart.x == 1)
        {
            wallN.addTile(behindStart);
        }
        else if (behindStart.y == -1)
        {
            wallW.addTile(behindStart);
        }
        else if (behindStart.y == 1)
        {
            wallE.addTile(behindStart);
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
        auto dst = glm::distance2(playerPosition, end);

        if (dst < 21 && dst >= 0)
        {
            doorTexture.bind();

            auto doorMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)end.x, animDoor, (float)end.y));
            MatrixManager doorMatrix{globalPMatrix, doorMVMatrix};
            doorMatrix.rotate(doorOrientation, glm ::vec3(0.f, 1.f, 0.f));
            doorMatrix.translate(glm::vec3(0.f, 0.f, 0.5f));
            doorMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);

            doorTexture.unbind();
        }

        wallE.updateRender(playerPosition);
        wallN.updateRender(playerPosition);
        wallS.updateRender(playerPosition);
        wallW.updateRender(playerPosition);
        water.updateRender(playerPosition);
        floor.updateRender(playerPosition);
        ceiling.updateRender(playerPosition);

        wallTexture.bind();
        wallE.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, globalMVMatrix);
        wallN.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, globalMVMatrix);
        wallS.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, globalMVMatrix);
        wallW.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, globalMVMatrix);
        wallTexture.unbind();

        groundTexture.bind();
        floor.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, globalMVMatrix);
        groundTexture.unbind();

        waterTexture.bind();
        water.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, globalMVMatrix);
        waterTexture.unbind();

        ceilingTexture.bind();
        ceiling.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, globalMVMatrix);
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
        return (pos == doorPosition && (!doorOpened || animDoor < 1.f)) ||
               pos == glm::vec2(-1) * getFirstDirection() ||
               water.thereIsATile(tmp) ||
               wallS.thereIsATile(tmp) ||
               wallW.thereIsATile(tmp) ||
               wallE.thereIsATile(tmp) ||
               wallN.thereIsATile(tmp);
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