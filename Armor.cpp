#include "Armor.h"

Armor::Armor(const std::string& armorName, const ArmorType& armorType, int armorDefensePoints)
    : name(armorName), type(armorType), defensePoints(armorDefensePoints) {
    // Initialisations suppl�mentaires si n�cessaire
}

std::string Armor::getInfo()
{
    return std::string(name + " +" + std::to_string(defensePoints) + " defense");
}

