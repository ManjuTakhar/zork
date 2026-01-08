#include "../include/Item.h"
#include <iostream>

namespace Zork {
    
    Item::Item(const std::string& name, 
               const std::string& description,
               int weight,
               bool takeable,
               ItemType type)
        : name_(name), 
          description_(description),
          weight_(weight),
          takeable_(takeable),
          type_(type),
          value_(0),
          damage_(0),
          defense_(0) {
    }
    
    std::string Item::getTypeString() const {
        switch (type_) {
            case ItemType::WEAPON: return "Weapon";
            case ItemType::ARMOR: return "Armor";
            case ItemType::KEY: return "Key";
            case ItemType::CONSUMABLE: return "Consumable";
            case ItemType::QUEST_ITEM: return "Quest Item";
            default: return "Miscellaneous";
        }
    }
    
    void Item::use() {
        // TODO: Implement item-specific use functionality
        // Different items should have different effects when used
        std::cout << "You use the " << name_ << ".\n";
        
        switch (type_) {
            case ItemType::CONSUMABLE:
                std::cout << "The " << name_ << " has been consumed.\n";
                break;
            case ItemType::WEAPON:
                std::cout << "You equip the " << name_ << " as your weapon.\n";
                break;
            case ItemType::ARMOR:
                std::cout << "You equip the " << name_ << " as your armor.\n";
                break;
            case ItemType::KEY:
                std::cout << "This key might unlock something nearby.\n";
                break;
            default:
                std::cout << "Nothing happens.\n";
                break;
        }
    }
}
