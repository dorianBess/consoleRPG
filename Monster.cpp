#include "Monster.h"

Monster::Monster(const std::string& monsterName, int monsterHealthPoints, int monsterAttackPoints,int recompense)
    : Entity(monsterName,monsterHealthPoints,monsterAttackPoints,0) 
{
    mRecompense = recompense;
}

int Monster::Recompense(Player* player)
{
    player->addGold(mRecompense);
    return mRecompense;
}

void Monster::Defeat(Player* player)
{
    std::cout << this->name << " vaincu. " << std::endl;
    Recompense(player);
}

