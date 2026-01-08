#ifndef SAVEMANAGER_H
#define SAVEMANAGER_H

#include <string>
#include <map>
#include <memory>
#include "Player.h"
#include "Room.h"

namespace Zork {
    
    struct GameState {
        std::string playerName;
        std::string currentRoomId;
        std::vector<std::string> inventory;
        std::map<std::string, bool> visitedRooms;
        std::map<std::string, std::vector<std::string>> roomItems;
        int score;
        int moves;
        int health;
        
        GameState() : score(0), moves(0), health(100) {}
    };
    
    class SaveManager {
    private:
        std::string saveDirectory_;
        
        std::string serializeGameState(const GameState& state);
        GameState deserializeGameState(const std::string& data);
        
    public:
        SaveManager();
        
        bool save(const GameState& state, const std::string& filename);
        bool load(GameState& state, const std::string& filename);
        std::vector<std::string> listSaveFiles();
        bool deleteSave(const std::string& filename);
        
        std::string getSaveDirectory() const { return saveDirectory_; }
        void setSaveDirectory(const std::string& dir) { saveDirectory_ = dir; }
    };
}

#endif // SAVEMANAGER_H
