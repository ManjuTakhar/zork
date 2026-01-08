#ifndef ROOM_H
#define ROOM_H

#include <string>
#include <map>
#include <vector>
#include <memory>
#include "Item.h"

namespace Zork {
    
    class Room {
    private:
        std::string id_;
        std::string name_;
        std::string description_;
        std::map<std::string, std::shared_ptr<Room>> exits_;
        std::vector<ItemPtr> items_;
        bool visited_;
        bool lit_;
        bool locked_;
        
    public:
        Room(const std::string& id,
             const std::string& name,
             const std::string& description);
        
        // Getters
        std::string getId() const { return id_; }
        std::string getName() const { return name_; }
        std::string getDescription() const { return description_; }
        bool isVisited() const { return visited_; }
        bool isLit() const { return lit_; }
        bool isLocked() const { return locked_; }
        
        // Setters
        void setVisited(bool visited) { visited_ = visited; }
        void setLit(bool lit) { lit_ = lit; }
        void setLocked(bool locked) { locked_ = locked; }
        
        // Exit management
        void addExit(const std::string& direction, std::shared_ptr<Room> room);
        std::shared_ptr<Room> getExit(const std::string& direction);
        std::vector<std::string> getExits() const;
        bool hasExit(const std::string& direction) const;
        
        // Item management
        void addItem(ItemPtr item);
        ItemPtr removeItem(const std::string& itemName);
        ItemPtr getItem(const std::string& itemName);
        std::vector<ItemPtr> getItems() const { return items_; }
        bool hasItem(const std::string& itemName) const;
        
        // Display
        std::string getFullDescription() const;
        std::string getItemsList() const;
    };
    
    using RoomPtr = std::shared_ptr<Room>;
}

#endif // ROOM_H
