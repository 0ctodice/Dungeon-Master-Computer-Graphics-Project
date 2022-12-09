#pragma once

#include "glm.hpp"
#include <utility>
#include <glimac/Character.hpp>
#include <glimac/Treasure.hpp>
// #include <glimac/Inventory.hpp>
#include <iostream>

namespace glimac
{

    class Player : public Character
    {
    private:
        using Inventory = std::pair<Treasure, Treasure>;
        Inventory inventory = std::make_pair(Treasure{0, glm::vec2(0, 0), "fist", 3, 1, ""}, Treasure{0, glm::vec2(0, 0), "skin", 4, 1, ""});
        int money = 0;

    public:
        Player();
        int getMoney() const;
        Treasure getOffensive() const;
        Treasure getDefensive() const;
        void setOffensive(Treasure t);
        void setDefensive(Treasure t);
        void setMoney(int value);
        void displayInfos() const;
    };
}