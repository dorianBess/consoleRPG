#pragma once
#include "Command.h"
#include "Monster.h"
#include "Player.h"
#include <vector>
#include <list>


class Room {
public:
    Room();
    Room(const std::vector<Command>& directions, int treasure,
        const std::vector<Weapon*> weapons, const std::vector<Armor*> armors, Monster* monster,bool isLastRoom = false);
    ~Room();
    void DisplayContent() const;
    void DisplayOptions();
public:
    bool isWall;
    bool isLastRoom;
private:
    std::vector<Command> directions;
    std::list<Command> possibleActions;
    int treasure;
    std::vector<Weapon*> weapons;
    std::vector<Armor*> armors;
    Monster* monster;

    friend class Game;
};

