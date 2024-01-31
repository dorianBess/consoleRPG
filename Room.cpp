#include "Room.h"
#include <iostream>

Room::Room() : isLastRoom(false),monster(nullptr),treasure(0)
{
    isWall = true;
}

Room::Room(const std::vector<Command>& directions, int treasure,
    const std::vector<Weapon*> weapons, const std::vector<Armor*> armors,Monster* monster,bool isLastRoom)
    : directions(directions), treasure(treasure), weapons(weapons), armors(armors), monster(monster),isWall(false),isLastRoom(isLastRoom) {
}

Room::~Room()
{
    
}

void Room::DisplayContent() const {
    std::cout << "\nDirections disponibles : \n";
    for (const auto& direction : directions) {
        switch (direction) {
        case Command::North:
            std::cout << "N ";
            break;
        case Command::South:
            std::cout << "S ";
            break;
        case Command::East:
            std::cout << "E ";
            break;
        case Command::West:
            std::cout << "W ";
            break;
        default:
            break;
        }
    }
    std::cout << std::endl;

    if (treasure > 0) {
        std::cout << "Tresor : " << treasure << " pieces d'or" << std::endl;
    }

    if (!weapons.empty() || !armors.empty()) {
        std::cout << "Equipements disponibles :" << std::endl;
        int index = 1;

        for (const auto& weapon : weapons) {
            std::cout << index << ". Arme : " << weapon->name << " (+" << weapon->attackPoints << " attaque)" << std::endl;
            ++index;
        }

        for (const auto& armor : armors) {
            std::string type = "";
            switch (armor->type)
            {
            case ArmorType::casque:
                type = "casque";
                break;
            case ArmorType::plastron:
                type = "plastron";
                break;
            case ArmorType::jambe:
                type = "jambe";
                break;
            case ArmorType::botte:
                type = "botte";
                break;
            }
        
            std::cout << index << ". Armure : " << type << " : " << armor->name << " (+" << armor->defensePoints << " defense)" << std::endl;
            ++index;
        }
    }

    if (monster != nullptr) {
        std::cout << "Monstre present : " << monster->name << " (Points de vie : " << monster->healthPoints
            << ", Points d'attaque : " << monster->attackPoints << ")" << std::endl;
    }

    if (monster == nullptr && isLastRoom)
    {
        std::cout << "Vous pouvez sortir du Donjon ! "<< std::endl;
    }
}

void Room::DisplayOptions()
{
    possibleActions.clear();
    for (const auto& direction : directions) {
        switch (direction) {
        case Command::North:
            std::cout << "(N) Deplacer Nord ";
            possibleActions.push_back(Command::North);
            break;
        case Command::South:
            std::cout << "(S) Deplacer Sud ";
            possibleActions.push_back(Command::South);
            break;
        case Command::East:
            std::cout << "(E) Deplacer Est ";
            possibleActions.push_back(Command::East);
            break;
        case Command::West:
            std::cout << "(W) Deplacer Ouest ";
            possibleActions.push_back(Command::West);
            break;
        default:
            break;
        }
    }
    std::cout << std::endl;


    if (treasure > 0)
    {
        std::cout << "(T) Prendre tresor" << std::endl;
        possibleActions.push_back(Command::Treasure);
    }

    if (!weapons.empty() || !armors.empty()) 
    {
        std::cout << "(P) Prendre objet" << std::endl;
        possibleActions.push_back(Command::Pickup);
    }

    if (monster != nullptr) {
        std::cout << "(F) Combattre" << std::endl;
        possibleActions.push_back(Command::Fight);
    }

    if (monster == nullptr && isLastRoom)
    {
        std::cout << "(D) Sortir du Donjon ! " << std::endl;
        possibleActions.push_back(Command::End);
    }

    std::cout << "(M) Afficher carte" << std::endl;
    possibleActions.push_back(Command::Map);

    std::cout << "(A) Afficher statistique Joueur" << std::endl;
    possibleActions.push_back(Command::PlayerStat);
}

