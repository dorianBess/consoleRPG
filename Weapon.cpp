#include "Weapon.h"

Weapon::Weapon(const std::string& weaponName, int weaponAttackPoints)
    : name(weaponName), attackPoints(weaponAttackPoints) {
    // Initialisations suppl�mentaires si n�cessaire
}

std::string Weapon::getInfo()
{
    return std::string(name + " +" + std::to_string(attackPoints) + " attaque");
}

