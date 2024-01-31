#pragma once
#include <string>
class Entity
{
public:
	std::string name;
	int currentHealth;
	int healthPoints;
	int attackPoints;
	int defensePoints;
public:
	Entity();
	Entity(const std::string& name, int healthPoints, int attackPoints,int defensePoints);
	virtual int Attack(Entity* cible);
	virtual int TakeDamage(int value);
	bool isAlive();

};

