#include <glimac/common.hpp>
#include <glimac/MapGenerator.hpp>

namespace glimac
{
    MapGenerator::MapGenerator(PPMParser *mapParsed) : map{mapParsed}
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

        std::transform(corridors.begin(), corridors.end(), corridors.begin(), [origin](glm::vec2 corridor)
                       { auto pos = corridor - origin; 
                           return glm::vec2(pos.x*-1, pos.y); });

        end -= start;
        end = glm::vec2(end.x * -1, end.y);
    }

    MapGenerator::~MapGenerator()
    {
        map = nullptr;
        delete (map);
    }

    void MapGenerator::draw(GLuint uTextureLocation, GLuint uMVMatrixLocation, GLuint uMVPMatrixLocation, GLuint uNormalMatrixLocation, GLuint uLightPosLocation, glm::mat4 *globalPMatrix, glm::mat4 globalMVMatrix) const
    {
        wallTexture.bind();
        for (auto wall : walls)
        {
            auto wallMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)wall.x, 0.f, (float)wall.y));
            drawWall(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, wallMVMatrix);
        }
        wallTexture.unbind();

        ceilingTexture.bind();

        // TEXUTRE FOR START

        drawCeilling(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, globalMVMatrix);

        for (auto ceiling : corridors)
        {
            auto ceilingMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)ceiling.x, 0.f, (float)ceiling.y));
            drawCeilling(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, ceilingMVMatrix);
        }

        // TEXTURE FOR END

        auto ceilingMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)end.x, 0.f, (float)end.y));
        drawCeilling(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, ceilingMVMatrix);

        ceilingTexture.unbind();

        groundTexture.bind();

        // TEXUTRE FOR START
        drawFloor(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, globalMVMatrix);

        for (auto ground : corridors)
        {
            auto groundMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)ground.x, 0.f, (float)ground.y));
            drawFloor(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, groundMVMatrix);
        }

        // TEXTURE FOR END

        auto groundMVMatrix = glm::translate(globalMVMatrix, glm::vec3((float)end.x, 0.f, (float)end.y));
        drawFloor(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation, globalPMatrix, groundMVMatrix);

        groundTexture.unbind();
    }

    void MapGenerator::deleteMap()
    {
        wallTexture.deleteTexture();
        ceilingTexture.deleteTexture();
        groundTexture.deleteTexture();
    }

    glm::vec2 MapGenerator::getStartPosition() const { return start; }

    bool MapGenerator::thereIsAWall(glm::vec2 pos) const { return std::find(walls.begin(), walls.end(), pos) != walls.end(); }

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
}