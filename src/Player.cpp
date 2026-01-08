#include "../include/Player.h"
#include "../include/Constants.h"
#include "../include/Utils.h"
#include <sstream>
#include <algorithm>

namespace Zork {
    
    Player::Player(const std::string& name, RoomPtr startingRoom)
        : name_(name),
          currentRoom_(startingRoom),
          maxInventorySize_(Constants::MAX_INVENTORY_SIZE),
          maxCarryWeight_(Constants::MAX_CARRY_WEIGHT),
          currentWeight_(0),
          health_(Constants::INITIAL_PLAYER_HEALTH),
          maxHealth_(Constants::INITIAL_PLAYER_HEALTH),
          attackPower_(Constants::BASE_ATTACK_DAMAGE),
          defense_(Constants::BASE_DEFENSE) {
    }
    
    void Player::modifyHealth(int amount) {
        health_ += amount;
        if (health_ > maxHealth_) {
            health_ = maxHealth_;
        }
        if (health_ < 0) {
            health_ = 0;
        }
    }
    
    bool Player::move(const std::string& direction) {
        RoomPtr nextRoom = currentRoom_->getExit(direction);
        if (nextRoom) {
            if (nextRoom->isLocked()) {
                return false;
            }
            currentRoom_ = nextRoom;
            if (!currentRoom_->isVisited()) {
                currentRoom_->setVisited(true);
            }
            return true;
        }
        return false;
    }
    
    bool Player::takeItem(ItemPtr item, std::string& message) {
        if (!item) {
            message = "That item doesn't exist.";
            return false;
        }
        
        if (!item->isTakeable()) {
            message = "You can't take the " + item->getName() + ".";
            return false;
        }
        
        // TODO: Implement comprehensive weight system
        // Need to check total weight including all items in inventory
        if (inventory_.size() >= static_cast<size_t>(maxInventorySize_)) {
            message = "Your inventory is full!";
            return false;
        }
        
        if (!canCarry(item->getWeight())) {
            message = "That's too heavy to carry!";
            return false;
        }
        
        inventory_.push_back(item);
        currentWeight_ += item->getWeight();
        message = "You take the " + item->getName() + ".";
        return true;
    }
    
    bool Player::dropItem(const std::string& itemName, std::string& message) {
        std::string lowerName = Utils::toLower(itemName);
        for (auto it = inventory_.begin(); it != inventory_.end(); ++it) {
            if (Utils::toLower((*it)->getName()) == lowerName) {
                ItemPtr item = *it;
                inventory_.erase(it);
                currentWeight_ -= item->getWeight();
                currentRoom_->addItem(item);
                message = "You drop the " + item->getName() + ".";
                return true;
            }
        }
        message = "You don't have that item.";
        return false;
    }
    
    bool Player::hasItem(const std::string& itemName) const {
        std::string lowerName = Utils::toLower(itemName);
        for (const auto& item : inventory_) {
            if (Utils::toLower(item->getName()) == lowerName) {
                return true;
            }
        }
        return false;
    }
    
    ItemPtr Player::getInventoryItem(const std::string& itemName) {
        std::string lowerName = Utils::toLower(itemName);
        for (auto& item : inventory_) {
            if (Utils::toLower(item->getName()) == lowerName) {
                return item;
            }
        }
        return nullptr;
    }
    
    bool Player::canCarry(int weight) const {
        return (currentWeight_ + weight) <= maxCarryWeight_;
    }
    
    int Player::attack() {
        int damage = attackPower_;
        
        // TODO: Add weapon bonuses and critical hit system
        // Check for equipped weapon and apply damage bonus
        // Implement random critical hit chance
        
        if (Utils::randomBool(0.2)) { // 20% critical hit chance
            damage *= Constants::CRITICAL_HIT_MULTIPLIER;
        }
        
        return damage;
    }
    
    void Player::takeDamage(int damage) {
        int actualDamage = damage - defense_;
        if (actualDamage < 0) actualDamage = 0;
        
        health_ -= actualDamage;
        if (health_ < 0) {
            health_ = 0;
        }
    }
    
    std::string Player::getInventoryList() const {
        if (inventory_.empty()) {
            return "\nYou are empty-handed.\n";
        }
        
        std::stringstream ss;
        ss << "\nYou are carrying:\n";
        for (const auto& item : inventory_) {
            ss << "  - " << item->getName() 
               << " (" << item->getWeight() << " lbs)\n";
        }
        ss << "Total weight: " << currentWeight_ 
           << "/" << maxCarryWeight_ << " lbs\n";
        return ss.str();
    }
    
    std::string Player::getStatus() const {
        std::stringstream ss;
        ss << "\n=== Player Status ===\n";
        ss << "Name: " << name_ << "\n";
        ss << "Health: " << health_ << "/" << maxHealth_ << "\n";
        ss << "Attack: " << attackPower_ << "\n";
        ss << "Defense: " << defense_ << "\n";
        ss << "Inventory: " << inventory_.size() 
           << "/" << maxInventorySize_ << " items\n";
        ss << "Weight: " << currentWeight_ 
           << "/" << maxCarryWeight_ << " lbs\n";
        ss << "====================\n";
        return ss.str();
    }
}
