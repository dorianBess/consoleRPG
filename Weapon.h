#pragma once

#include <string>

class Weapon
{
public:
    Weapon(const std::string& name, int attackPoints);
    std::string getInfo();
private:
    std::string name;
    int attackPoints;

    friend class Room;
    friend class Player;
};

