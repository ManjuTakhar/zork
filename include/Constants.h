#ifndef CONSTANTS_H
#define CONSTANTS_H

#include <string>

namespace Zork {
    namespace Constants {
        // Game constants
        const int MAX_INVENTORY_SIZE = 10;
        const int MAX_CARRY_WEIGHT = 100;
        const int INITIAL_PLAYER_HEALTH = 100;
        const std::string GAME_VERSION = "1.0.0";
        const std::string SAVE_FILE_EXTENSION = ".sav";
        
        // Scoring
        const int SCORE_ITEM_PICKUP = 5;
        const int SCORE_ROOM_DISCOVERED = 10;
        const int SCORE_PUZZLE_SOLVED = 25;
        const int SCORE_ENEMY_DEFEATED = 50;
        
        // Combat
        const int BASE_ATTACK_DAMAGE = 10;
        const int BASE_DEFENSE = 5;
        const int CRITICAL_HIT_MULTIPLIER = 2;
        
        // Directions
        const std::string DIR_NORTH = "north";
        const std::string DIR_SOUTH = "south";
        const std::string DIR_EAST = "east";
        const std::string DIR_WEST = "west";
        const std::string DIR_UP = "up";
        const std::string DIR_DOWN = "down";
    }
}

#endif // CONSTANTS_H
