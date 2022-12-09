#pragma once
#include "glm.hpp"
#include "iostream"

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
        Character();
        Character(int atk, int ca, int pv);
        virtual int getAtk() const;
        virtual int getCa() const;
        int getPV() const;
        int getPVMax() const;
        void setAtk(int value);
        void setCa(int value);
        void setPV(int value);
        void setPVMax(int value);

        void takeDamage(int value);
        bool isDead() const;
    };

}