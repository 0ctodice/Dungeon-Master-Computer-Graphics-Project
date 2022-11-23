#include <glimac/common.hpp>
#include <glimac/Player.hpp>

namespace glimac
{
    Player::Player(int atk, int ca, int pv) : Character{atk, ca, pv} {}
    int Player::getMoney() const { return money; }
    void Player::setMoney(int value) { money += value; }
    void Player::displayInfos() const
    {
        std::cout << "-----------------" << std::endl;
        std::cout << "money : " << money << std::endl;
        std::cout << "pvMax : " << pvMax << std::endl;
        std::cout << "pv : " << pv << std::endl;
        std::cout << "atk : " << atk << std::endl;
        std::cout << "ca : " << ca << std::endl;
        std::cout << "-----------------" << std::endl;
    }
}