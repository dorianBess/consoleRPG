#pragma once

#include <string>
enum ArmorType
{
    casque, plastron, jambe, botte
};
class Armor {
public:
    Armor(const std::string& name, const ArmorType& type, int defensePoints);
    std::string getInfo();
private:
    std::string name;
    ArmorType type;
    int defensePoints;

    friend class Room;
    friend class Player;
};

