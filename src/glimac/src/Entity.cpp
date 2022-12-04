#include <glimac/common.hpp>
#include <glimac/Entity.hpp>

namespace glimac
{
    Entity::Entity(int id, glm::vec2 pos, std::string name, std::string texture) : id{id}, position{pos}, name{name}, textureName{texture}, texture{"/home/thomas2dumont/Computer_Graphics/Dungeon-Master-Computer-Graphics-Project/assets/textures/" + texture, false} {}
    void Entity::updateActions(float time, SixAdjacencyCamera *player, MapGenerator *map)
    {
        auto newPos = position - player->getPlayerPosition();

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
    std::string Entity::getName() const { return name; }
    Texture Entity::getTexture() const { return texture; }
    std::string Entity::getTextureName() const { return textureName; }
}