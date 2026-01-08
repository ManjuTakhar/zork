#include "../include/Room.h"
#include "../include/Utils.h"
#include <algorithm>
#include <sstream>

namespace Zork {
    
    Room::Room(const std::string& id,
               const std::string& name,
               const std::string& description)
        : id_(id),
          name_(name),
          description_(description),
          visited_(false),
          lit_(true),
          locked_(false) {
    }
    
    void Room::addExit(const std::string& direction, std::shared_ptr<Room> room) {
        exits_[Utils::toLower(direction)] = room;
    }
    
    std::shared_ptr<Room> Room::getExit(const std::string& direction) {
        std::string dir = Utils::toLower(direction);
        if (exits_.find(dir) != exits_.end()) {
            return exits_[dir];
        }
        return nullptr;
    }
    
    std::vector<std::string> Room::getExits() const {
        std::vector<std::string> exitList;
        for (const auto& pair : exits_) {
            exitList.push_back(pair.first);
        }
        return exitList;
    }
    
    bool Room::hasExit(const std::string& direction) const {
        return exits_.find(Utils::toLower(direction)) != exits_.end();
    }
    
    void Room::addItem(ItemPtr item) {
        items_.push_back(item);
    }
    
    ItemPtr Room::removeItem(const std::string& itemName) {
        std::string lowerName = Utils::toLower(itemName);
        for (auto it = items_.begin(); it != items_.end(); ++it) {
            if (Utils::toLower((*it)->getName()) == lowerName) {
                ItemPtr item = *it;
                items_.erase(it);
                return item;
            }
        }
        return nullptr;
    }
    
    ItemPtr Room::getItem(const std::string& itemName) {
        std::string lowerName = Utils::toLower(itemName);
        for (auto& item : items_) {
            if (Utils::toLower(item->getName()) == lowerName) {
                return item;
            }
        }
        return nullptr;
    }
    
    bool Room::hasItem(const std::string& itemName) const {
        std::string lowerName = Utils::toLower(itemName);
        for (const auto& item : items_) {
            if (Utils::toLower(item->getName()) == lowerName) {
                return true;
            }
        }
        return false;
    }
    
    std::string Room::getFullDescription() const {
        std::stringstream ss;
        ss << "\n" << name_ << "\n";
        
        if (!lit_) {
            ss << "It is pitch black. You are likely to be eaten by a grue.\n";
            return ss.str();
        }
        
        ss << description_ << "\n";
        return ss.str();
    }
    
    std::string Room::getItemsList() const {
        if (items_.empty()) {
            return "";
        }
        
        std::stringstream ss;
        ss << "\nYou see: ";
        for (size_t i = 0; i < items_.size(); ++i) {
            ss << items_[i]->getName();
            if (i < items_.size() - 1) {
                ss << ", ";
            }
        }
        ss << "\n";
        return ss.str();
    }
}
