#ifndef _GAME_H
#define _GAME_H

#include <string.h>
#include <vector>
#include "Room.h"
#include "Player.h"
#include "Troll.h"
#include "Orc.h"
#include "Dragon.h"

class Game
{	
public:
	std::vector<std::vector<Room>> map;
    std::pair<int, int> playerPosition;
    Player* player;
public:
    Game();
    ~Game();
	static Game* Instance();
	static void Release();
    void Play();
private:
    static Game* sInstance;
    void DisplayCurrentRoom();
    void HandleCommand(Player* player, char command);
    Command ConvertToCommand(char input) const;
    void MovePlayer(Command direction);
    void OpenTreasure(Player* player);
    void PickUpItem(Player* player);
    void FightMonster(Player* player);
    void DisplayWorldMap();
    void endGame();
private:
    bool askForPickUp;
    bool isGameFinish = false;
};

#endif
