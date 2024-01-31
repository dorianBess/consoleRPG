#pragma once

#include <iostream>
#include <string>

#include "Weapon.h"
#include "Armor.h"
#include "Entity.h"

class Player : public Entity {
public:
    Player(const std::string& playerName);
    Player();
    ~Player();
    void DisplayInfo() const;
    Weapon* setNewWeapon(Weapon* newWeapon);
    Armor* setNewArmor(Armor* newArmor);
    void addGold(int value);
    int Attack(Entity* cible);

private:
    Weapon* currentWeapon;
    Armor* casque;
    Armor* plastron;
    Armor* jambe;
    Armor* botte;
    int gold;

    friend class Game;  // Permet à la classe Game d'accéder aux membres privés du joueur
};

