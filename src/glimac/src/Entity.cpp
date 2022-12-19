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

#include <glimac/Entity.hpp>

namespace glimac
{
    Entity::Entity(int id, glm::vec2 pos, glm::vec2 initPos, int lvl, std::string name, std::string texture) : id{id}, position{pos}, initialPosition{initPos}, levelStage{lvl}, name{name}, textureName{texture}, texture{texture, true} {}
    void Entity::updateActions(float time, Character *player, SixAdjacencyCamera *camera, MapGenerator *map)
    {
        auto newPos = position - camera->getPlayerPosition();

        if (newPos.y == 0 || glm::abs(newPos.y) < glm::abs(newPos.x))
        {
            rotation = 90.f;
            return;
        }
        rotation = 0.f;
    }
    void Entity::deleteTexture() { texture.deleteTexture(); }
    int Entity::getId() const { return id; }
    glm::vec2 Entity::getPosition() const { return position; }
    glm::vec2 Entity::getInitialPosition() const { return initialPosition; }
    int Entity::getLevelStage() const { return levelStage; }
    std::string Entity::getName() const { return name; }
    Texture Entity::getTexture() const { return texture; }
    std::string Entity::getTextureName() const { return textureName; }
}