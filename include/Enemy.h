#ifndef ENEMY_H
#define ENEMY_H

#include <string>
#include <memory>

namespace Zork {
    
    class Enemy {
    private:
        std::string name_;
        std::string description_;
        int health_;
        int maxHealth_;
        int attackPower_;
        int defense_;
        int experienceReward_;
        bool isHostile_;
        
    public:
        Enemy(const std::string& name,
              const std::string& description,
              int health,
              int attackPower,
              int defense);
        
        // Getters
        std::string getName() const { return name_; }
        std::string getDescription() const { return description_; }
        int getHealth() const { return health_; }
        int getMaxHealth() const { return maxHealth_; }
        int getAttackPower() const { return attackPower_; }
        int getDefense() const { return defense_; }
        int getExperienceReward() const { return experienceReward_; }
        bool getIsHostile() const { return isHostile_; }
        
        // Setters
        void setHealth(int health) { health_ = health; }
        void setIsHostile(bool hostile) { isHostile_ = hostile; }
        void setExperienceReward(int exp) { experienceReward_ = exp; }
        
        // Combat
        int attack();
        void takeDamage(int damage);
        bool isAlive() const { return health_ > 0; }
        
        // AI behavior
        std::string getAction();
        
        // Display
        std::string getStatus() const;
    };
    
    using EnemyPtr = std::shared_ptr<Enemy>;
}

#endif // ENEMY_H
