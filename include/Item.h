#ifndef ITEM_H
#define ITEM_H

#include <string>
#include <memory>

namespace Zork {
    
    enum class ItemType {
        MISC,
        WEAPON,
        ARMOR,
        KEY,
        CONSUMABLE,
        QUEST_ITEM
    };
    
    class Item {
    private:
        std::string name_;
        std::string description_;
        int weight_;
        bool takeable_;
        ItemType type_;
        int value_;
        int damage_;  // For weapons
        int defense_; // For armor
        
    public:
        Item(const std::string& name, 
             const std::string& description,
             int weight = 1,
             bool takeable = true,
             ItemType type = ItemType::MISC);
        
        // Getters
        std::string getName() const { return name_; }
        std::string getDescription() const { return description_; }
        int getWeight() const { return weight_; }
        bool isTakeable() const { return takeable_; }
        ItemType getType() const { return type_; }
        int getValue() const { return value_; }
        int getDamage() const { return damage_; }
        int getDefense() const { return defense_; }
        
        // Setters
        void setValue(int value) { value_ = value; }
        void setDamage(int damage) { damage_ = damage; }
        void setDefense(int defense) { defense_ = defense; }
        
        // Methods
        std::string getTypeString() const;
        void use();
    };
    
    using ItemPtr = std::shared_ptr<Item>;
}

#endif // ITEM_H
