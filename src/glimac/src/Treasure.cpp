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

#include <glimac/Treasure.hpp>
#include <glimac/Entity.hpp>

namespace glimac
{
    Treasure::Treasure(int id, glm::vec2 pos, glm::vec2 initPos, int lvl, std::string name, int type, int value, std::string texture) : Entity{id, pos, initPos, lvl, name, texture}, type{static_cast<TreasureType>(type)}, value{value} {}
    TreasureType Treasure::getType() const { return type; }
    int Treasure::getValue() const { return value; }
    void Treasure::setPosition(glm::vec2 pos) { position = pos; }
}