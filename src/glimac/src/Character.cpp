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

#include "glimac/Character.hpp"

namespace glimac
{
    Character::Character() : atk{0}, ca{0}, pvMax{20}, pv{20} {}
    Character::Character(int atk, int ca, int pv) : atk{atk}, ca{ca}, pvMax{pv}, pv{pv} {}
    int Character::getAtk() const { return atk; }
    int Character::getCa() const { return ca; }
    int Character::getPV() const { return pv; }
    int Character::getPVMax() const { return pvMax; }
    void Character::setAtk(int value) { atk = value; }
    void Character::setCa(int value) { ca = value; }
    void Character::setPV(int value) { pv = std::min(pvMax, pv + value); }
    void Character::setPVMax(int value)
    {
        pvMax += value;
        pv = pvMax;
    }
    void Character::takeDamage(int value)
    {
        int tank = ca - value;
        if (tank < 0)
            pv += tank;
        std::cout << "current pv : " << pv << std::endl;
    }
    bool Character::isDead() const { return pv <= 0; }
}