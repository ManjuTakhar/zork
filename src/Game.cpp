#include "../include/Game.h"
#include "../include/Constants.h"
#include "../include/Utils.h"
#include <iostream>
#include <sstream>

namespace Zork {
    
    Game::Game() 
        : running_(false), 
          score_(0), 
          moves_(0),
          inCombat_(false) {
        parser_ = std::make_unique<CommandParser>(this);
    }
    
    Game::~Game() {
        // Cleanup handled by smart pointers
    }
    
    void Game::setupWorld() {
        createRooms();
        createItems();
        connectRooms();
        
        // Create player
        player_ = std::make_shared<Player>("Adventurer", rooms_["west_of_house"]);
    }
    
    void Game::createRooms() {
        rooms_["west_of_house"] = std::make_shared<Room>(
            "west_of_house",
            "West of House",
            "You are standing in an open field west of a white house, "
            "with a boarded front door. There is a small mailbox here."
        );
        
        rooms_["forest"] = std::make_shared<Room>(
            "forest",
            "Forest",
            "This is a forest, with trees in all directions. "
            "To the east, there appears to be sunlight."
        );
        
        rooms_["behind_house"] = std::make_shared<Room>(
            "behind_house",
            "Behind House",
            "You are behind the white house. A path leads into the forest "
            "to the east. In one corner of the house there is a small window "
            "which is slightly ajar."
        );
        
        rooms_["kitchen"] = std::make_shared<Room>(
            "kitchen",
            "Kitchen",
            "You are in the kitchen of the white house. A table seems to "
            "have been used recently for the preparation of food. A passage "
            "leads to the west and a dark staircase can be seen leading upward."
        );
        
        rooms_["living_room"] = std::make_shared<Room>(
            "living_room",
            "Living Room",
            "You are in the living room. There is a doorway to the east, "
            "a wooden door with strange gothic lettering to the west, which "
            "appears to be nailed shut, and a large oriental rug in the center "
            "of the room."
        );
        
        rooms_["attic"] = std::make_shared<Room>(
            "attic",
            "Attic",
            "This is the attic. The only exit is a stairway leading down. "
            "A large coil of rope is lying in the corner."
        );
        
        rooms_["cellar"] = std::make_shared<Room>(
            "cellar",
            "Cellar",
            "You are in a dark and damp cellar with a narrow passageway "
            "leading north, and a crawlway to the south. On the west is "
            "the bottom of a steep metal ramp which is unclimbable."
        );
        
        // Mark cellar as dark initially
        rooms_["cellar"]->setLit(false);
    }
    
    void Game::createItems() {
        // West of house items
        auto mailbox = std::make_shared<Item>("mailbox", 
            "A small mailbox. It can be opened.", 50, false);
        rooms_["west_of_house"]->addItem(mailbox);
        
        auto leaflet = std::make_shared<Item>("leaflet", 
            "A small leaflet that reads: 'Welcome to Zork!'", 1);
        rooms_["west_of_house"]->addItem(leaflet);
        
        // Kitchen items
        auto lamp = std::make_shared<Item>("lamp", 
            "A brass lantern that might provide light.", 3);
        rooms_["kitchen"]->addItem(lamp);
        
        // Attic items
        auto rope = std::make_shared<Item>("rope", 
            "A sturdy coil of rope.", 5);
        rooms_["attic"]->addItem(rope);
        
        // Living room items
        auto sword = std::make_shared<Item>("sword", 
            "An elvish sword of great antiquity.", 8, true, ItemType::WEAPON);
        sword->setDamage(15);
        sword->setValue(100);
        rooms_["living_room"]->addItem(sword);
        
        // TODO: Add more complex items and puzzle objects
        // Need keys, locked doors, combinable items, etc.
    }
    
    void Game::connectRooms() {
        // West of house connections
        rooms_["west_of_house"]->addExit("north", rooms_["forest"]);
        rooms_["west_of_house"]->addExit("south", rooms_["behind_house"]);
        
        // Forest connections (loops back to itself)
        rooms_["forest"]->addExit("south", rooms_["west_of_house"]);
        rooms_["forest"]->addExit("east", rooms_["west_of_house"]);
        rooms_["forest"]->addExit("west", rooms_["forest"]);
        rooms_["forest"]->addExit("north", rooms_["forest"]);
        
        // Behind house connections
        rooms_["behind_house"]->addExit("north", rooms_["west_of_house"]);
        rooms_["behind_house"]->addExit("east", rooms_["kitchen"]);
        
        // Kitchen connections
        rooms_["kitchen"]->addExit("west", rooms_["behind_house"]);
        rooms_["kitchen"]->addExit("east", rooms_["living_room"]);
        rooms_["kitchen"]->addExit("up", rooms_["attic"]);
        rooms_["kitchen"]->addExit("down", rooms_["cellar"]);
        
        // Living room connections
        rooms_["living_room"]->addExit("west", rooms_["kitchen"]);
        
        // Attic connections
        rooms_["attic"]->addExit("down", rooms_["kitchen"]);
        
        // Cellar connections
        rooms_["cellar"]->addExit("up", rooms_["kitchen"]);
    }
    
    RoomPtr Game::getRoom(const std::string& roomId) {
        if (rooms_.find(roomId) != rooms_.end()) {
            return rooms_[roomId];
        }
        return nullptr;
    }
    
    void Game::addRoom(RoomPtr room) {
        rooms_[room->getId()] = room;
    }
    
    void Game::start() {
        setupWorld();
        running_ = true;
        
        displayWelcome();
        displayRoom();
    }
    
    void Game::run() {
        while (running_) {
            try {
                std::string input = Utils::getInput("\n> ");
                if (!input.empty()) {
                    processCommand(input);
                }
            } catch (const std::exception& e) {
                std::cerr << "Error: " << e.what() << std::endl;
            }
        }
    }
    
    void Game::displayRoom() {
        RoomPtr room = player_->getCurrentRoom();
        
        std::cout << room->getFullDescription();
        
        if (room->isLit()) {
            std::cout << room->getItemsList();
            
            std::vector<std::string> exits = room->getExits();
            if (!exits.empty()) {
                std::cout << "Exits: " << Utils::join(exits, ", ") << std::endl;
            }
        }
        
        // Award points for discovering new rooms
        if (!room->isVisited()) {
            addScore(Constants::SCORE_ROOM_DISCOVERED);
        }
    }
    
    void Game::processCommand(const std::string& input) {
        CommandResult result = parser_->parse(input);
        
        if (!result.message.empty()) {
            std::cout << result.message << std::endl;
        }
        
        if (!result.continueGame) {
            running_ = false;
        }
    }
    
    void Game::gameOver(bool victory) {
        Utils::printSeparator('=');
        if (victory) {
            std::cout << "Congratulations! You have won the game!\n";
        } else {
            std::cout << "GAME OVER\n";
        }
        std::cout << "Your final score: " << score_ << " points in " 
                  << moves_ << " moves.\n";
        Utils::printSeparator('=');
        running_ = false;
    }
    
    void Game::startCombat(EnemyPtr enemy) {
        // TODO: Implement full combat system with turn-based mechanics
        currentEnemy_ = enemy;
        inCombat_ = true;
        std::cout << "Combat with " << enemy->getName() << " begins!\n";
    }
    
    void Game::processCombatTurn(const std::string& action) {
        // TODO: Handle combat actions and enemy AI responses
    }
    
    void Game::endCombat(bool playerVictory) {
        inCombat_ = false;
        if (playerVictory) {
            addScore(Constants::SCORE_ENEMY_DEFEATED);
        }
        currentEnemy_ = nullptr;
    }
    
    bool Game::saveGame(const std::string& filename) {
        // TODO: Implement save game serialization
        return false;
    }
    
    bool Game::loadGame(const std::string& filename) {
        // TODO: Implement load game deserialization
        return false;
    }
    
    void Game::displayWelcome() {
        Utils::printSeparator('=');
        Utils::printCentered("ZORK - A Text Adventure Game");
        Utils::printSeparator('=');
        std::cout << "\nWelcome to Zork! You are about to embark on a great adventure.\n";
        std::cout << "Type 'help' for a list of commands.\n";
    }
    
    void Game::displayHelp() {
        std::cout << parser_->getHelpText();
    }
    
    void Game::displayScore() {
        std::cout << "\n=== Score ===\n";
        std::cout << "Current score: " << score_ << " points\n";
        std::cout << "Moves taken: " << moves_ << "\n";
        std::cout << "=============\n";
    }
}
