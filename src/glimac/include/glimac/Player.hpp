#pragma once

#include "glm.hpp"
#include <glimac/Character.hpp>
#include <glimac/Inventory.hpp>
#include <iostream>

namespace glimac
{
    class Player : public Character
    {
    private:
        Inventory inventory{};

    public:
        Player();
        int getMoney() const;
        Treasure getOffensive() const;
        Treasure getdefensive() const;
        void setOffensive(Treasure t);
        void setDefensive(Treasure t);
        void setMoney(int value);
        void displayInfos() const;
    };
}