#include <glimac/common.hpp>
#include <glimac/Player.hpp>

namespace glimac
{
    Player::Player() : Character{}
    {
        setAtk(inventory.getOffensive().getValue());
        setCa(inventory.getDefensive().getValue());
    }
    int Player::getMoney() const { return inventory.getMoney(); }
    void Player::setMoney(int value) { inventory.setMoney(value); }
    Treasure Player::getOffensive() const { return inventory.getOffensive(); }
    Treasure Player::getdefensive() const { return inventory.getDefensive(); }
    void Player::setOffensive(Treasure t)
    {
        inventory.setOffensive(t);
        setAtk(t.getValue());
    }
    void Player::setDefensive(Treasure t)
    {
        inventory.setDefensive(t);
        setCa(t.getValue());
    }
    void Player::displayInfos() const
    {
        std::cout << "-----------------" << std::endl;
        std::cout << "money : " << inventory.getMoney() << std::endl;
        std::cout << "pvMax : " << pvMax << std::endl;
        std::cout << "pv : " << pv << std::endl;
        std::cout << "offensive : " << inventory.getOffensive().getName() << std::endl;
        std::cout << "atk : " << atk << std::endl;
        std::cout << "defensive : " << inventory.getDefensive().getName() << std::endl;
        std::cout << "ca : " << ca << std::endl;
        std::cout << "-----------------" << std::endl;
    }
}