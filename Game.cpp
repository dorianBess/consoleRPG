#include "Game.h"

Game* Game::sInstance = NULL;

Game* Game::Instance() 
{
    if (sInstance == NULL) {
        sInstance = new Game();
    }
    return sInstance;
}

void Game::Release()
{
    delete sInstance;
    sInstance = NULL;
}

Game::Game() : player(new Player())
{

}

Game::~Game()
{
    delete player;
    player = NULL;

    for (auto row : map)
    {
        for (auto room : row)
        {
            for (auto weapon : room.weapons)
            {
                delete weapon;
                weapon = NULL;
            }
            room.weapons.clear();
            for (auto armor : room.armors)
            {
                delete armor;
                armor = NULL;
            }
            room.armors.clear();
            delete room.monster;
            room.monster = NULL;
        }
    }
    


    map.clear();
}

void Game::DisplayCurrentRoom() {
    int row = playerPosition.first;
    int col = playerPosition.second;

    std::cout << "=== Salle actuelle ===" << std::endl;
    map[row][col].DisplayContent();
    std::cout << "======================" << std::endl;
}

void Game::HandleCommand(Player* player, char command) {
    Command action = ConvertToCommand(command);
    if (std::find(map[playerPosition.first][playerPosition.second].possibleActions.begin(),
        map[playerPosition.first][playerPosition.second].possibleActions.end()
        , action) == map[playerPosition.first][playerPosition.second].possibleActions.end())
    {
        std::cout << "Commande invalide." << std::endl;
        return;
    }

    switch (action) {
    case Command::North:
    case Command::South:
    case Command::East:
    case Command::West:
        MovePlayer(action);
        break;
    case Command::Treasure:
        OpenTreasure(player);
        break;
    case Command::Pickup:
        PickUpItem(player);
        break;
    case Command::Fight:
        FightMonster(player);
        break;
    case Command::Map:
        DisplayWorldMap();
        break;
    case Command::PlayerStat:
        player->DisplayInfo();
        break;
    case Command::End:
        endGame();
        break;
    default:
        std::cout << "Commande invalide." << std::endl;
    }
}

Command Game::ConvertToCommand(char input) const {
    switch (input) {
    case 'N': case 'n': return Command::North;
    case 'S': case 's': return Command::South;
    case 'E': case 'e': return Command::East;
    case 'W': case 'w': return Command::West;
    case 'T': case 't': return Command::Treasure;
    case 'P': case 'p': return Command::Pickup;
    case 'F': case 'f': return Command::Fight;
    case 'M': case 'm': return Command::Map;
    case 'A': case 'a': return Command::PlayerStat;
    case 'D': case 'd': return Command::End;
    default: return Command::Unknow;
    }
}

void Game::MovePlayer(Command direction) {
    int row = playerPosition.first;
    int col = playerPosition.second;

    switch (direction) {
    case Command::North:
        if (row > 0) {
            --playerPosition.first;
        }
        break;
    case Command::South:
        if (row < static_cast<int>(map.size()) - 1) {
            ++playerPosition.first;
        }
        break;
    case Command::East:
        if (col < static_cast<int>(map[row].size()) - 1) {
            ++playerPosition.second;
        }
        break;
    case Command::West:
        if (col > 0) {
            --playerPosition.second;
        }
        break;
    default:
        break;
    }
}

void Game::OpenTreasure(Player* player) {
    int row = playerPosition.first;
    int col = playerPosition.second;

    if (map[row][col].treasure > 0) {
        int treasureAmount = map[row][col].treasure;
        player->gold += treasureAmount;
        map[row][col].treasure = 0;  // Trésor ramassé
        std::cout << "Vous avez trouvé un tresor ! Vous gagnez " << treasureAmount << " pieces d'or." << std::endl;
    }
    else {
        std::cout << "Il n'y a pas de trésor dans cette salle." << std::endl;
    }
}

void Game::PickUpItem(Player* player) {
    int row = playerPosition.first;
    int col = playerPosition.second;

    std::cout << "Quel item souhaitez-vous recuperer ?" << std::endl;

    int choice;
    std::string entree;
    std::cout << "Entrez le numero de l'element : ";
    std::getline(std::cin, entree);

    try {
        choice = std::stoi(entree);
    }
    catch (const std::invalid_argument& e) {
        std::cout << "Nombre incorrect" << std::endl;
        return;
    }
    catch (const std::out_of_range& e) {
        std::cout << "Nombre incorrect" << std::endl;
        return;
    }
    choice--;

    if (choice >= 0 && choice < static_cast<int>(map[row][col].armors.size() + map[row][col].weapons.size()))
    {
        if (choice < static_cast<int>(map[row][col].weapons.size()))
        {
            map[row][col].weapons[choice] = player->setNewWeapon(map[row][col].weapons[choice]);
            auto it = std::find(map[row][col].weapons.begin(), map[row][col].weapons.end(), nullptr);

            if (it != map[row][col].weapons.end()) {
                map[row][col].weapons.erase(it);
            }
            std::cout << "Arme recuperer" << std::endl;
        }
        else
        {
            choice = choice - static_cast<int>(map[row][col].weapons.size());
            map[row][col].armors[choice] = player->setNewArmor(map[row][col].armors[choice]);
            auto it = std::find(map[row][col].armors.begin(), map[row][col].armors.end(), nullptr);

            if (it != map[row][col].armors.end()) {
                map[row][col].armors.erase(it);
            }
            std::cout << "Armure recuperer" << std::endl;
        }
    }
    else
    {
        std::cout << "Nombre incorrect" << std::endl;
    }
}

void Game::FightMonster(Player* player) {
    int row = playerPosition.first;
    int col = playerPosition.second;

    if (map[row][col].monster != nullptr) {
        if (std::rand() % 2 == 0)
        {
            player->Attack(map[row][col].monster);
            //std::cout << "Vous avez infliger " << player.Attack(map[row][col].monster) <<" a " << map[row][col].monster->name << std::endl;
        }
        else 
        {
            map[row][col].monster->Attack(player);
            //std::cout << map[row][col].monster->name << " vous a infliger " <<map[row][col].monster->Attack(&player) << " degats." << std::endl;
        }
    }
    else {
        std::cout << "Il n'y a pas de monstre dans cette salle." << std::endl;
    }

    if (!player->isAlive())
    {
        endGame();
    }
    else if (!map[row][col].monster->isAlive())
    {
        map[row][col].monster->Defeat(player);
        delete map[row][col].monster;
        map[row][col].monster = NULL;
    }
}

void Game::DisplayWorldMap() {
    std::cout << "=== Carte du Monde ===" << std::endl;
    for (size_t i = 0; i < map.size()  ; ++i) {
        for (size_t j = 0; j < map[i].size(); ++j) {
            if (i == static_cast<size_t>(playerPosition.first) && j == static_cast<size_t>(playerPosition.second)) {
                std::cout << "P ";  // Affiche la position du joueur
            }
            else if (map[i][j].isWall)
            {
                std::cout << "- ";  // Affiche une salle non visitée
            }
            else 
            {
                std::cout << "X ";  // Affiche une salle non visitée
            }
        }
        std::cout << std::endl;
    }
    std::cout << "======================" << std::endl;
}

void Game::endGame()
{
    std::cout << "=== Fin de la partie ===" << std::endl;
    player->DisplayInfo();
    if (player->isAlive())
    {
        std::cout << "=== Bravo vous avez triompher ! ===" << std::endl;
    }
    else
    {
        std::cout << "=== Vous vous etes fait terrasser. ===" << std::endl;
    }
    isGameFinish = true;
}

void Game::Play()
{
    map.resize(5, std::vector<Room>(5));
    map[4][0] = Room({ Command::North }, 10, { new Weapon("Epee magique",10) }, {}, nullptr);
    map[3][0] = Room({ Command::North }, 0, {}, {}, new Troll());
    map[2][0] = Room({ Command::East }, 0, {}, {new Armor("Casque lourd",ArmorType::casque,2),new Armor("Plastron lourd",ArmorType::plastron,4) }, nullptr);
    map[2][1] = Room({ Command::East }, 0, {}, { new Armor("Jambiere lourd",ArmorType::jambe,3),new Armor("Botte lourd",ArmorType::botte,1) }, nullptr);
    map[2][2] = Room({ Command::North,Command::South }, 10, {}, {}, new Orc());
    map[1][2] = Room({ Command::North }, 0, {}, {}, nullptr);
    map[0][2] = Room({ Command::East }, 0, {}, {}, nullptr);
    map[0][3] = Room({ Command::East }, 0, {}, {}, nullptr);
    map[0][4] = Room({ Command::South }, 0, {}, {}, nullptr);

    map[1][4] = Room({}, 10, {}, {}, new Dragon(),true);

    map[3][2] = Room({ Command::East }, 10, {}, {}, nullptr);
    map[3][3] = Room({ Command::East }, 10, 
        {new Weapon("Arc Magique",12)},
        { new Armor("Casque Magique",ArmorType::casque,3),
        new Armor("Plastron magique",ArmorType::plastron,5),
        new Armor("Jambiere magique",ArmorType::jambe,4),
        new Armor("Botte magique",ArmorType::botte,2) }, nullptr);
    map[3][4] = Room({ Command::North }, 10, {}, {}, nullptr);
    map[2][4] = Room({ Command::North }, 10, {}, {},nullptr);

    playerPosition = { 4, 0 };

    std::cout << "Veuillez entrer votre nom : \n";

    // Lire le nom saisi par le joueur
    std::getline(std::cin, player->name);
    std::cout << "--------------------";

    std::string entree = "";

    while (!isGameFinish)
    {
        // Afficher la salle actuelle
        map[playerPosition.first][playerPosition.second].DisplayContent();
        std::cout << "--------------------\n";

        std::cout << "Choisissez une action : \n";

        // Afficher les options d'action
        map[playerPosition.first][playerPosition.second].DisplayOptions();
        std::getline(std::cin, entree);

        if (entree.length() == 1)
        {
            HandleCommand(player, entree.at(0));
        }
        else
        {
            std::cout << "\nAction non reconnu \n";
        }
    }
}
