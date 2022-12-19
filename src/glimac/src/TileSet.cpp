/////////////////////////////////////////////////////////////////////////////////
//
// ------------------------------------------------------------------------------
//   _____      _            _ _
//  |  _  |    | |          | (_)
//  | |/' | ___| |_ ___   __| |_  ___ ___
//  |  /| |/ __| __/ _ \ / _` | |/ __/ _ \
//  \ |_/ / (__| || (_) | (_| | | (_|  __/
//   \___/ \___|\__\___/ \__,_|_|\___\___|
//
// ------------------------------------------------------------------------------
//
//  Projet de synthèse d'image du Master 2 Informatique spé. Sciences de l'image
//  ~ Thomas DUMONT A.K.A 0ctodice
//
// ------------------------------------------------------------------------------
//
/////////////////////////////////////////////////////////////////////////////////

#include <glimac/TileSet.hpp>
#include <glimac/MatrixManager.hpp>

namespace glimac
{
    TileSet::TileSet(float ori, glm::vec3 vec) : orientation{ori}, vectorOrientation{vec} {}
    void TileSet::resetSet() { tiles.clear(); }
    void TileSet::addTile(glm::vec2 pos)
    {
        Tile tmp{pos};
        tiles.emplace(tmp);
    }
    void TileSet::updateRender(glm::vec2 playerPosition)
    {
        std::set<Tile> tmpSet = {};
        std::for_each(tiles.begin(), tiles.end(), [this, &playerPosition, &tmpSet](const Tile &tile)
                      {
                            Tile tmp {tile.getPosition()};
                            tmp.changeRender(checkDistance(tile.getPosition(), playerPosition));
                            tmpSet.emplace(tmp); });
        tiles = tmpSet;
    }

    void TileSet::updateData(glm::vec2 origin)
    {
        std::set<Tile> tmpSet;
        std::for_each(tiles.begin(), tiles.end(), [&origin, &tmpSet](const Tile &tile)
                      {
                            auto pos = tile.getPosition() - origin;
                            pos.x *= -1;
                            Tile tmp {pos};
                            tmpSet.emplace(tmp); });
        tiles = tmpSet;
    }

    bool TileSet::thereIsATile(Tile tile) const { return std::find(tiles.begin(), tiles.end(), tile) != tiles.end(); }
    void TileSet::draw(GLuint uTextureLocation,
                       GLuint uMVMatrixLocation,
                       GLuint uMVPMatrixLocation,
                       GLuint uNormalMatrixLocation,
                       GLuint uLightPosLocation,
                       glm::mat4 *globalPMatrix,
                       glm::mat4 globalMVMatrix) const
    {
        std::for_each(tiles.begin(), tiles.end(), [this, &uTextureLocation, &uMVMatrixLocation, &uMVPMatrixLocation, &uNormalMatrixLocation, &uLightPosLocation, &globalPMatrix, &globalMVMatrix](const Tile &tile)
                      {
                            if(tile.shouldRender()){
                                auto pos = tile.getPosition();
                                auto matrix = glm::translate(globalMVMatrix, glm::vec3((float)pos.x, 0.f, (float)pos.y));
                                MatrixManager wallMatrix{globalPMatrix, matrix};
                                wallMatrix.rotate(orientation, vectorOrientation);
                                wallMatrix.translate(glm::vec3(0.f, 0.f, 0.5f));
                                wallMatrix.draw(uTextureLocation, uMVMatrixLocation, uMVPMatrixLocation, uNormalMatrixLocation, uLightPosLocation);
                            } });
    }

}