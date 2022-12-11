#include <glimac/common.hpp>
#include <glimac/Player.hpp>

namespace glimac
{
    Player::Player() : Character{}
    {
        setAtk(inventory.first.getValue());
        setCa(inventory.second.getValue());
    }
    int Player::getMoney() const { return money; }
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