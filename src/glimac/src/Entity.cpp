#include <glimac/common.hpp>
#include <glimac/Entity.hpp>

namespace glimac
{
    Entity::Entity(int id, glm::vec2 pos, int lvl, std::string name, std::string texture) : id{id}, position{pos}, levelStage{lvl}, name{name}, textureName{texture}, texture{texture, false} {}
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
    int Entity::getLevelStage() const { return levelStage; }
    std::string Entity::getName() const { return name; }
    Texture Entity::getTexture() const { return texture; }
    std::string Entity::getTextureName() const { return textureName; }
}