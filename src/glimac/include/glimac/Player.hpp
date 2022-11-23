#pragma once

#include "glm.hpp"
#include <glimac/Character.hpp>
#include <iostream>

namespace glimac
{
    class Player : public Character
    {
    private:
        int money = 0;

    public:
        Player(int atk = 1, int ca = 1, int pv = 20);
        int getMoney() const;
        void setMoney(int value);
        void displayInfos() const;
    };
}