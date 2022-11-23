#include <glimac/common.hpp>
#include <glimac/Entity.hpp>

namespace glimac
{
    Entity::Entity(int id, glm::vec2 pos, std::string name, std::string texture) : id{id}, position{pos}, name{name}, texture{"/home/thomas2dumont/Computer_Graphics/Dungeon-Master-Computer-Graphics-Project/assets/textures/" + texture, false} {}
    void Entity::deleteTexture() { texture.deleteTexture(); }
    glm::vec2 Entity::getPosition() const { return position; }
    std::string Entity::getName() const { return name; }
    Texture Entity::gettexture() const { return texture; }
}