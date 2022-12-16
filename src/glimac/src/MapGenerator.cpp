#include <glimac/common.hpp>
#include <glimac/MapGenerator.hpp>

namespace glimac
{
    void MapGenerator::setWindowManager(SDLWindowManager *wind)
    {
        window = wind;
    }
    void MapGenerator::setMapToParsed(PPMParser *mapParsed)
    {
        map = mapParsed;

        walls.clear();
        waters.clear();
        corridors.clear();

        animDoor = 0.f;
        doorOpened = false;

        auto pixels = map->getPixels();

        for (int i = 0; i < map->getHeight(); i++)
        {
            for (int j = 0; j < map->getWidth(); j++)
            {
                auto pixel = pixels[i * map->getWidth() + j];

                if (pixel == RGB(0, 0, 0))
                {
                    walls.push_back(glm::vec2(i, j));
                    continue;
                }
                if (pixel == RGB(0, 0, 255))
                {
                    waters.push_back(glm::vec2(i, j));
                    continue;
                }
                if (pixel == RGB(255, 255, 255))
                {
                    corridors.push_back(glm::vec2(i, j));
                    continue;
                }
                if (pixel == RGB(255, 0, 0))
                {
                    start = glm::vec2(i, j);
                    continue;
                }
                if (pixel == RGB(0, 255, 0))
                {
                    end = glm::vec2(i, j);
                    continue;
                }
            }
        }
        auto origin = start;

        std::transform(walls.begin(), walls.end(), walls.begin(), [origin](glm::vec2 wall)
                       { auto pos = wall - origin;
                           return glm::vec2(pos.x*-1, pos.y); });

        std::transform(waters.begin(), waters.end(), waters.begin(), [origin](glm::vec2 water)
                       { auto pos = water - origin;
                           return glm::vec2(pos.x*-1, pos.y); });

        std::transform(corridors.begin(), corridors.end(), corridors.begin(), [origin](glm::vec2 corridor)
                       { auto pos = corridor - origin; 
                           return glm::vec2(pos.x*-1, pos.y); });

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
    MapGenerator::MapGenerator(PPMParser *mapParsed, SDLWindowManager *window) : map{mapParsed}, window(window)
    {
        auto pixels = map->getPixels();

        for (int i = 0; i < map->getHeight(); i++)
        {
            for (int j = 0; j < map->getWidth(); j++)
            {
                auto pixel = pixels[i * map->getWidth() + j];

                if (pixel == RGB(0, 0, 0))
                {
                    walls.push_back(glm::vec2(i, j));
                    continue;
                }
                if (pixel == RGB(0, 0, 255))
                {
                    waters.push_back(glm::vec2(i, j));
                    continue;
                }
                if (pixel == RGB(255, 255, 255))
                {
                    corridors.push_back(glm::vec2(i, j));
                    continue;
                }
                if (pixel == RGB(255, 0, 0))
                {
                    start = glm::vec2(i, j);
                    continue;
                }
                if (pixel == RGB(0, 255, 0))
                {
                    end = glm::vec2(i, j);
                    continue;
                }
            }
        }
        auto origin = start;

        std::transform(walls.begin(), walls.end(), walls.begin(), [origin](glm::vec2 wall)
                       { auto pos = wall - origin;
                           return glm::vec2(pos.x*-1, pos.y); });

        std::transform(waters.begin(), waters.end(), waters.begin(), [origin](glm::vec2 water)
                       { auto pos = water - origin;
                           return glm::vec2(pos.x*-1, pos.y); });

        std::transform(corridors.begin(), corridors.end(), corridors.begin(), [origin](glm::vec2 corridor)
                       { auto pos = corridor - origin; 
                           return glm::vec2(pos.x*-1, pos.y); });

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

        auto behind = glm::vec2{-1} * getFirstDirection();

        if (checkDistance(behind))
        {

            auto behindStartWallMVMatrix = glm::translate(globalMVMatrix, glm::vec3(behind.x, 0.f, behind.y));
            drawWall(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, behindStartWallMVMatrix);
        }

        for (auto wall : walls)
        {
            if (checkDistance(wall))
            {
                auto wallMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)wall.x, 0.f, (float)wall.y));
                drawWall(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, wallMVMatrix);
                drawWall(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, glm::translate(wallMVMatrix, glm::vec3(0.f, -1.f, 0.f)));
            }
        };

        wallTexture.unbind();

        waterTexture.bind();

        for (auto water : waters)
        {
            if (checkDistance(water))
            {
                auto waterMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)water.x, 0.f, (float)water.y));
                drawWater(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, waterMVMatrix);
            }
        }

        waterTexture.unbind();

        ceilingTexture.bind();

        // TEXTURE FOR START
        if (checkDistance(glm::vec2{0.f}))
        {
            drawCeilling(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, globalMVMatrix);
        }

        for (auto water : waters)
        {
            if (checkDistance(water))
            {
                auto waterMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)water.x, 0.f, (float)water.y));
                drawCeilling(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, waterMVMatrix);
            }
        }

        for (auto ceiling : corridors)
        {
            if (checkDistance(ceiling))
            {
                auto ceilingMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)ceiling.x, 0.f, (float)ceiling.y));
                drawCeilling(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, ceilingMVMatrix);
            }
        }

        // TEXTURE FOR END

        if (checkDistance(end))
        {
            auto ceilingMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)end.x, 0.f, (float)end.y));
            drawCeilling(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, ceilingMVMatrix);
        }
        ceilingTexture.unbind();

        groundTexture.bind();

        // TEXTURE FOR START
        if (checkDistance(glm::vec2{0.f}))
        {
            drawFloor(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, globalMVMatrix);
        }

        for (auto ground : corridors)
        {
            if (checkDistance(ground))
            {
                auto groundMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)ground.x, 0.f, (float)ground.y));
                drawFloor(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, groundMVMatrix);
            }
        }

        // TEXTURE FOR END

        if (checkDistance(end))
        {
            auto groundMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)end.x, 0.f, (float)end.y));
            drawFloor(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, groundMVMatrix);
        }
        groundTexture.unbind();
    }

    void MapGenerator::clean()
    {
        wallTexture.deleteTexture();
        ceilingTexture.deleteTexture();
        waterTexture.deleteTexture();
        groundTexture.deleteTexture();
    }

    glm::vec2 MapGenerator::getStartPosition() const { return start; }
    glm::vec2 MapGenerator::getEndPosition() const { return end; }

    bool MapGenerator::thereIsAWall(glm::vec2 pos) const { return std::find(walls.begin(), walls.end(), pos) != walls.end() || std::find(waters.begin(), waters.end(), pos) != waters.end() || (pos == doorPosition && (!doorOpened || animDoor < 1.f)) || pos == glm::vec2(-1) * getFirstDirection(); }

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

    glm::vec2 MapGenerator::getDoorPosition() { return doorPosition; }
}