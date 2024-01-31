#include "Dragon.h"

Dragon::Dragon() : Monster("Dragon", 50, 10,50)
{
}

int Dragon::Attack(Entity* cible)
{
	if (std::rand() % 2 == 0)
	{
		std::cout << this->name << " attaque " << cible->name << " avec ses dents. " << std::endl;
		return cible->TakeDamage(attackPoints * 2);
	}
	else
	{
		std::cout << this->name << " attaque " << cible->name << " avec ses griffes. " << std::endl;
		return cible->TakeDamage(attackPoints);
	}
	
}