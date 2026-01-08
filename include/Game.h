#ifndef GAME_H
#define GAME_H

#include <string>
#include <map>
#include <memory>
#include "Player.h"
#include "Room.h"
#include "Command.h"
#include "Enemy.h"

namespace Zork {
    
    class CommandParser; // Forward declaration
    
    class Game {
    private:
        PlayerPtr player_;
        std::map<std::string, RoomPtr> rooms_;
        std::unique_ptr<CommandParser> parser_;
        bool running_;
        int score_;
        int moves_;
        EnemyPtr currentEnemy_;
        bool inCombat_;
        
        void setupWorld();
        void createRooms();
        void createItems();
        void connectRooms();
        
    public:
        Game();
        ~Game();
        
        // Getters
        PlayerPtr getPlayer() const { return player_; }
        int getScore() const { return score_; }
        int getMoves() const { return moves_; }
        bool isRunning() const { return running_; }
        bool isInCombat() const { return inCombat_; }
        EnemyPtr getCurrentEnemy() const { return currentEnemy_; }
        
        // Setters
        void addScore(int points) { score_ += points; }
        void incrementMoves() { moves_++; }
        void setRunning(bool running) { running_ = running; }
        void setInCombat(bool combat) { inCombat_ = combat; }
        void setCurrentEnemy(EnemyPtr enemy) { currentEnemy_ = enemy; }
        
        // Room management
        RoomPtr getRoom(const std::string& roomId);
        void addRoom(RoomPtr room);
        
        // Game flow
        void start();
        void run();
        void displayRoom();
        void processCommand(const std::string& input);
        void gameOver(bool victory = false);
        
        // Combat
        void startCombat(EnemyPtr enemy);
        void processCombatTurn(const std::string& action);
        void endCombat(bool playerVictory);
        
        // Save/Load
        bool saveGame(const std::string& filename);
        bool loadGame(const std::string& filename);
        
        // Display
        void displayWelcome();
        void displayHelp();
        void displayScore();
    };
}

#endif // GAME_H
