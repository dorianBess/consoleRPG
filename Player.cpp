#include "Player.h"

Player::Player(const std::string& playerName)
    : Entity(playerName, 100, 10, 0) {
    setNewWeapon(new Weapon("Epee de base", 5));
    currentHealth = healthPoints;
}

Player::Player() : Entity("",100,10, 0)
{
    setNewWeapon(new Weapon("Epee de base", 5));
    currentHealth = healthPoints;
}

Player::~Player()
{
    delete currentWeapon;
    currentWeapon = NULL;

    delete casque;
    casque = NULL;

    delete plastron;
    plastron = NULL;

    delete jambe;
    jambe = NULL;

    delete botte;
    botte = NULL;
}

void Player::DisplayInfo() const {
    std::cout << "=== Infos du Joueur ===" << std::endl;
    std::cout << "Nom : " << name << std::endl;
    std::cout << "Points de vie : " << currentHealth << "/" << healthPoints << std::endl;
    std::cout << "Points d'attaque : " << attackPoints << std::endl;
    std::cout << "Points de defense : " << defensePoints << std::endl;
    std::cout << "Arme actuelle : " << currentWeapon->name << " (+" << currentWeapon->attackPoints << " attaque)" << std::endl;
    if (casque != nullptr)
    {
        std::cout << "Casque : " << casque->name << " (+" << casque->defensePoints << " defense)" << std::endl;
    }
    if (plastron != nullptr)
    {
        std::cout << "Plastron : " << plastron->name << " (+" << plastron->defensePoints << " defense)" << std::endl;
    }
    if (jambe != nullptr)
    {
        std::cout << "Jambe : " << jambe->name << " (+" << jambe->defensePoints << " defense)" << std::endl;
    }
    if (botte != nullptr)
    {
        std::cout << "Botte : " << botte->name << " (+" << botte->defensePoints << " defense)" << std::endl;
    }
    // Affichez d'autres informations du joueur si nécessaire
    std::cout << "Pieces d'or : " << gold << std::endl;
    std::cout << "========================" << std::endl;
}

Weapon* Player::setNewWeapon(Weapon* newWeapon)
{
    if (currentWeapon)
    {
        Weapon* toReturn = currentWeapon;
        attackPoints -= currentWeapon->attackPoints;
        currentWeapon = newWeapon;
        attackPoints += currentWeapon->attackPoints;
        return toReturn;
    }
    else
    {
        currentWeapon = newWeapon;
        attackPoints += currentWeapon->attackPoints;
        return nullptr;
    }    
}

Armor* Player::setNewArmor(Armor* newArmor)
{
    Armor* toReturn = nullptr;
    switch (newArmor->type) 
	{
    case ArmorType::casque :
        toReturn = casque;
        casque = newArmor;
        if (toReturn != nullptr)
        {
            defensePoints -= toReturn->defensePoints;            
        }
        defensePoints += casque->defensePoints;
        break;
    case ArmorType::plastron:
        toReturn = plastron;
        plastron = newArmor;
        if (toReturn != nullptr)
        {
            defensePoints -= toReturn->defensePoints;            
        }
        defensePoints += plastron->defensePoints;
        break;
    case ArmorType::jambe:
        toReturn = jambe;
        jambe = newArmor;
        if (toReturn != nullptr)
        {
            defensePoints -= toReturn->defensePoints;
        }
        defensePoints += jambe->defensePoints;
        break;
    case ArmorType::botte:
        toReturn = botte;
        botte = newArmor;
        if (toReturn != nullptr)
        {
            defensePoints -= toReturn->defensePoints;
        }
        defensePoints += botte->defensePoints;
        break;
    }
    return toReturn;
        
}

void Player::addGold(int value)
{
    std::cout << this->name << " a recu " << value << " piece d'or." << std::endl;
    gold += value;
}

int Player::Attack(Entity* cible)
{
    std::cout << this->name << " attaque " << cible->name << " avec " << currentWeapon->name << "." << std::endl;
    return cible->TakeDamage(attackPoints);
}

