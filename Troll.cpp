#include "Troll.h"

Troll::Troll() : Monster("Troll",10,5,5)
{
}

int Troll::Attack(Entity* cible)
{
	std::cout << this->name << " attaque " << cible->name << " avec ses poings. " << std::endl;
	return cible->TakeDamage(attackPoints);
}
