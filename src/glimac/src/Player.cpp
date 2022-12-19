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

#include <glimac/Player.hpp>

namespace glimac
{
    Player::Player() : Character{}
    {
        setAtk(inventory.first.getValue());
        setCa(inventory.second.getValue());
    }
    int *Player::getMoney() { return &money; }
    int *Player::getPV() { return &pv; }
    int *Player::getPVMax() { return &pvMax; }
    void Player::setMoney(int value) { money += value; }
    Treasure Player::getOffensive() const { return inventory.first; }
    Treasure Player::getDefensive() const { return inventory.second; }
    void Player::setOffensive(Treasure t)
    {
        inventory.first = t;
        setAtk(inventory.first.getValue());
    }
    void Player::setDefensive(Treasure t)
    {
        inventory.second = t;
        setCa(inventory.second.getValue());
    }
    std::pair<Treasure, Treasure> *Player::getInventory() { return &inventory; }
    void Player::displayInfos() const
    {
        std::cout << "-----------------" << std::endl;
        std::cout << "money : " << money << std::endl;
        std::cout << "pvMax : " << pvMax << std::endl;
        std::cout << "pv : " << pv << std::endl;
        std::cout << "offensive : " << inventory.first.getName() << std::endl;
        std::cout << "atk : " << atk << std::endl;
        std::cout << "defensive : " << inventory.second.getName() << std::endl;
        std::cout << "ca : " << ca << std::endl;
        std::cout << "-----------------" << std::endl;
    }

    void Player::clean()
    {
        inventory.first.deleteTexture();
        inventory.second.deleteTexture();
    }
}