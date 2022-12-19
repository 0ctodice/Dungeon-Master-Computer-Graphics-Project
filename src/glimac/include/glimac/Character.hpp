/////////////////////////////////////////////////////////////////////////////////
//
// ------------------------------------------------------------------------------
//   _____      _            _ _
//  |  _  |    | |          | (_)
//  | |/' | ___| |_ ___   __| |_  ___ ___
//  |  /| |/ __| __/ _ \ / _` | |/ __/ _ \
//  \ |_/ / (__| || (_) | (_| | | (_|  __/
//   \___/ \___|\__\___/ \__,_|_|\___\___|
//
// ------------------------------------------------------------------------------
//
//  Projet de synthèse d'image du Master 2 Informatique spé. Sciences de l'image
//  ~ Thomas DUMONT A.K.A 0ctodice
//
// ------------------------------------------------------------------------------
//
/////////////////////////////////////////////////////////////////////////////////

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