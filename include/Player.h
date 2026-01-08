#ifndef PLAYER_H
#define PLAYER_H

#include <string>
#include <vector>
#include <memory>
#include "Room.h"
#include "Item.h"

namespace Zork {
    
    class Player {
    private:
        std::string name_;
        RoomPtr currentRoom_;
        std::vector<ItemPtr> inventory_;
        int maxInventorySize_;
        int maxCarryWeight_;
        int currentWeight_;
        int health_;
        int maxHealth_;
        int attackPower_;
        int defense_;
        
    public:
        Player(const std::string& name, RoomPtr startingRoom);
        
        // Getters
        std::string getName() const { return name_; }
        RoomPtr getCurrentRoom() const { return currentRoom_; }
        int getHealth() const { return health_; }
        int getMaxHealth() const { return maxHealth_; }
        int getAttackPower() const { return attackPower_; }
        int getDefense() const { return defense_; }
        int getCurrentWeight() const { return currentWeight_; }
        int getMaxCarryWeight() const { return maxCarryWeight_; }
        std::vector<ItemPtr> getInventory() const { return inventory_; }
        
        // Setters
        void setCurrentRoom(RoomPtr room) { currentRoom_ = room; }
        void setHealth(int health) { health_ = health; }
        void modifyHealth(int amount);
        
        // Movement
        bool move(const std::string& direction);
        
        // Inventory management
        bool takeItem(ItemPtr item, std::string& message);
        bool dropItem(const std::string& itemName, std::string& message);
        bool hasItem(const std::string& itemName) const;
        ItemPtr getInventoryItem(const std::string& itemName);
        int getInventorySize() const { return inventory_.size(); }
        bool canCarry(int weight) const;
        
        // Combat
        int attack();
        void takeDamage(int damage);
        bool isAlive() const { return health_ > 0; }
        
        // Display
        std::string getInventoryList() const;
        std::string getStatus() const;
    };
    
    using PlayerPtr = std::shared_ptr<Player>;
}

#endif // PLAYER_H
