#pragma once

#include <string>
#include "Entity.h"
#include "Player.h"

class Monster : public Entity {
public:
    Monster(const std::string& name, int healthPoints, int attackPoints,int recompense);
    virtual int Recompense(Player* player);
    virtual void Defeat(Player* player);
    friend class Room;

public:
    int mRecompense;
};

