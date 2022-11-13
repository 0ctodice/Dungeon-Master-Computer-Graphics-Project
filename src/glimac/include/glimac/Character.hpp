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
    };

}