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
        Character(int atk, int ca, int pv) : atk{atk}, ca{ca}, pvMax{pv}, pv{pv} {}
        int getAtk() const { return atk; }
        int getCa() const { return ca; }
        int getPV() const { return pv; }
        int getPVMax() const { return pvMax; }
        void setAtk(int value) { atk += value; }
        void setCa(int value) { ca += value; }
        void setPV(int value) { pv += value; }
        void setPVMax(int value) { pvMax += value; }
    };

}