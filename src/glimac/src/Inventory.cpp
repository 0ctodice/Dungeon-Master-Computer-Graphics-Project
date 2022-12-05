#include "glimac/common.hpp"
#include "glimac/Inventory.hpp"

namespace glimac
{
    Inventory::Inventory() : offensive{0, glm::vec2(0, 0), "fist", 3, 1, ""}, defensive{1, glm::vec2(0, 0), "skin", 4, 1, ""} {}
    Treasure Inventory::getOffensive() const { return offensive; }
    Treasure Inventory::getDefensive() const { return defensive; }
    int Inventory::getMoney() const { return money; }
    void Inventory::setOffensive(Treasure t) { offensive = t; }
    void Inventory::setDefensive(Treasure t) { defensive = t; }
    void Inventory::setMoney(int value) { money += value; }
}
