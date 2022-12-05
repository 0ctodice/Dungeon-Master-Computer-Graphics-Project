#pragma once
#include "glm.hpp"
#include <glimac/Treasure.hpp>

namespace glimac
{
    class Inventory
    {
    private:
        Treasure offensive;
        Treasure defensive;
        int money;

    public:
        Inventory();
        Treasure getOffensive() const;
        Treasure getDefensive() const;
        int getMoney() const;
        void setOffensive(Treasure t);
        void setDefensive(Treasure t);
        void setMoney(int value);
    };
}