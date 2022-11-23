#pragma once
#include "glm.hpp"

namespace glimac
{
    class Character
    {
    protected:
        int pvMax;
        int pv;
        int ca;
        int atk;

    public:
        Character() = delete;
        Character(int atk, int ca, int pv);
        int getAtk() const;
        int getCa() const;
        int getPV() const;
        int getPVMax() const;
        void setAtk(int value);
        void setCa(int value);
        void setPV(int value);
        void setPVMax(int value);
    };

}