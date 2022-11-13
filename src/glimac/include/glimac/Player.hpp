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
        Player(int atk = 1, int ca = 1, int pv = 20) : Character{atk, ca, pv} {}
        int getMoney() const { return money; }
        void setMoney(int value) { money += value; }
        void displayInfos() const
        {
            std::cout << "-----------------" << std::endl;
            std::cout << "money : " << money << std::endl;
            std::cout << "pvMax : " << pvMax << std::endl;
            std::cout << "pv : " << pv << std::endl;
            std::cout << "atk : " << atk << std::endl;
            std::cout << "ca : " << ca << std::endl;
            std::cout << "-----------------" << std::endl;
        }
    };
}