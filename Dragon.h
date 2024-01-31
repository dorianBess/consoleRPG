#pragma once

#include "Monster.h"

class Dragon : public Monster
{
public:
	Dragon();
	int Attack(Entity* cible) override;
};

