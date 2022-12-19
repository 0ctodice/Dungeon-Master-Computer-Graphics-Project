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
#include <utility>
#include <glimac/Character.hpp>
#include <glimac/Treasure.hpp>
#include <iostream>

namespace glimac
{

    class Player : public Character
    {
    private:
        using Inventory = std::pair<Treasure, Treasure>;
        Inventory inventory = std::make_pair(Treasure{0, glm::vec2(0, 0), glm::vec2(0, 0), 0, "fist", 3, 1, ""}, Treasure{0, glm::vec2(0, 0), glm::vec2(0, 0), 0, "skin", 4, 1, ""});
        int money = 0;

    public:
        Player();
        int *getMoney();
        int *getPV();
        int *getPVMax();
        Treasure getOffensive() const;
        Treasure getDefensive() const;
        void setOffensive(Treasure t);
        void setDefensive(Treasure t);
        std::pair<Treasure, Treasure> *getInventory();
        void setMoney(int value);
        void displayInfos() const;
        void clean();
    };
}