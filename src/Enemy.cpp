#include "../include/Enemy.h"
#include "../include/Utils.h"
#include <sstream>

namespace Zork {
    
    Enemy::Enemy(const std::string& name,
                 const std::string& description,
                 int health,
                 int attackPower,
                 int defense)
        : name_(name),
          description_(description),
          health_(health),
          maxHealth_(health),
          attackPower_(attackPower),
          defense_(defense),
          experienceReward_(health * 2),
          isHostile_(true) {
    }
    
    int Enemy::attack() {
        // TODO: Implement enemy-specific attack patterns
        // Different enemies should have different behaviors
        // Some might have special attacks or abilities
        
        int damage = attackPower_;
        
        // Random variance in damage
        int variance = Utils::randomInt(-2, 2);
        damage += variance;
        
        if (damage < 1) damage = 1;
        
        return damage;
    }
    
    void Enemy::takeDamage(int damage) {
        int actualDamage = damage - defense_;
        if (actualDamage < 0) actualDamage = 0;
        
        health_ -= actualDamage;
        if (health_ < 0) {
            health_ = 0;
        }
    }
    
    std::string Enemy::getAction() {
        // TODO: Implement AI decision making
        // Enemies should choose between attack, defend, or special moves
        // Based on their health and player's state
        
        if (health_ < maxHealth_ / 4) {
            if (Utils::randomBool(0.3)) {
                return "flee";
            }
        }
        
        if (Utils::randomBool(0.1)) {
            return "defend";
        }
        
        return "attack";
    }
    
    std::string Enemy::getStatus() const {
        std::stringstream ss;
        ss << name_ << " - ";
        
        double healthPercent = (static_cast<double>(health_) / maxHealth_) * 100;
        
        if (healthPercent > 75) {
            ss << "looking strong";
        } else if (healthPercent > 50) {
            ss << "slightly wounded";
        } else if (healthPercent > 25) {
            ss << "badly wounded";
        } else {
            ss << "near death";
        }
        
        ss << " (" << health_ << "/" << maxHealth_ << " HP)";
        return ss.str();
    }
}
