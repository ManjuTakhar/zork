#include "../include/SaveManager.h"
#include "../include/Utils.h"
#include <fstream>
#include <sstream>

namespace Zork {
    
    SaveManager::SaveManager() : saveDirectory_("./saves/") {
        // TODO: Create save directory if it doesn't exist
    }
    
    std::string SaveManager::serializeGameState(const GameState& state) {
        // TODO: Implement proper JSON or binary serialization
        // This is a placeholder implementation
        std::stringstream ss;
        ss << "ZORK_SAVE_V1\n";
        ss << "player_name=" << state.playerName << "\n";
        ss << "current_room=" << state.currentRoomId << "\n";
        ss << "score=" << state.score << "\n";
        ss << "moves=" << state.moves << "\n";
        ss << "health=" << state.health << "\n";
        
        ss << "inventory=";
        for (size_t i = 0; i < state.inventory.size(); ++i) {
            ss << state.inventory[i];
            if (i < state.inventory.size() - 1) {
                ss << ",";
            }
        }
        ss << "\n";
        
        return ss.str();
    }
    
    GameState SaveManager::deserializeGameState(const std::string& data) {
        // TODO: Implement proper deserialization matching the save format
        GameState state;
        
        std::istringstream ss(data);
        std::string line;
        
        // Skip header
        std::getline(ss, line);
        
        while (std::getline(ss, line)) {
            size_t pos = line.find('=');
            if (pos != std::string::npos) {
                std::string key = line.substr(0, pos);
                std::string value = line.substr(pos + 1);
                
                if (key == "player_name") {
                    state.playerName = value;
                } else if (key == "current_room") {
                    state.currentRoomId = value;
                } else if (key == "score") {
                    state.score = std::stoi(value);
                } else if (key == "moves") {
                    state.moves = std::stoi(value);
                } else if (key == "health") {
                    state.health = std::stoi(value);
                }
            }
        }
        
        return state;
    }
    
    bool SaveManager::save(const GameState& state, const std::string& filename) {
        std::string filepath = saveDirectory_ + filename;
        std::string data = serializeGameState(state);
        return Utils::writeFile(filepath, data);
    }
    
    bool SaveManager::load(GameState& state, const std::string& filename) {
        std::string filepath = saveDirectory_ + filename;
        if (!Utils::fileExists(filepath)) {
            return false;
        }
        
        std::string data = Utils::readFile(filepath);
        state = deserializeGameState(data);
        return true;
    }
    
    std::vector<std::string> SaveManager::listSaveFiles() {
        // TODO: Implement directory listing to find all .sav files
        std::vector<std::string> saves;
        return saves;
    }
    
    bool SaveManager::deleteSave(const std::string& filename) {
        std::string filepath = saveDirectory_ + filename;
        return std::remove(filepath.c_str()) == 0;
    }
}
