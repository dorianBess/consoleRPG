#pragma once
#include "Monster.h"

class Troll : public Monster
{
public:
	Troll();
	int Attack(Entity* cible) override;
};

