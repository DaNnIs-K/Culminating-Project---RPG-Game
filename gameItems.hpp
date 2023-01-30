#ifndef gameItems_hpp
#define gameItems_hpp

#include <vector>
#include <string>
#include "GameItemContainer.hpp"
using namespace std;

class GameItems {
  public:
    GameItemContainer<Weapon> weapons;
    GameItemContainer<Armour> armours;
    GameItemContainer<Mob> mobs;

    GameItems() {
      // BaseStats(string name = "None", double criticalChance = 0, double criticalDamage = 0, double accuracy = 100)
      
      // Weapon(BaseStats stats = BaseStats(), double dmg = 0)
      // ----------------------<Weapons>----------------------
      this->weapons.addItem(Weapon(BaseStats("Sword", 10, 15, 85), 25));
      this->weapons.addItem(Weapon(BaseStats("Flintlock", 10, 25, 70), 40));
      this->weapons.addItem(Weapon(BaseStats("Wooden Bow", 50, 50, 40), 30));
      this->weapons.addItem(Weapon(BaseStats("Shotgun", 30, 80, 10), 50));
      this->weapons.addItem(Weapon(BaseStats("Excalibur", 1, 200, 40), 60));
      this->weapons.addItem(Weapon(BaseStats("Bug Spray", 50, 50, 1), 70));
      // -----------------------------------------------------

      // Armour(BaseStats stats = BaseStats(), double defence = 0)
      // ----------------------<Armours>----------------------
      this->armours.addItem(Armour(BaseStats("Iron Platemail", 0, 0, 50), 20));
      this->armours.addItem(Armour(BaseStats("Ranger Coat", 15, 15, 80), 10));
      this->armours.addItem(Armour(BaseStats("Puffer Jacket", 0, 0, 70), 30));
      this->armours.addItem(Armour(BaseStats("Cowboy Hat", 30, 30, 90), 5));
      this->armours.addItem(Armour(BaseStats("Bee Suit", 0, 0, 10), 50));
      // -----------------------------------------------------

      // Creature(BaseStats stats = BaseStats(), Weapon equippedWeapon = Weapon(), Armour equippedArmour = Armour(), double maxHealth = 100, double baseDamage = 10, Inventory inventory = Inventory())
      // Mob(Creature creature = Creature())
      // ----------------------<Mobs>----------------------
      this->mobs.addItem(Mob(Creature(BaseStats("🐜 Ant", 50, 20, 80))));
      this->mobs.addItem(Mob(Creature(BaseStats("🦟 Mosquito", 80, 10, 100), Weapon(), Armour(), 130, 20)));
      this->mobs.addItem(Mob(Creature(BaseStats("🐛 Caterpillar", 50, 50, 50))));
      this->mobs.addItem(Mob(Creature(BaseStats("🐞 Lady Beetle", 10, 30, 80), Weapon(), Armour(), 150)));
      this->mobs.addItem(Mob(Creature(BaseStats("🦗 Cricket", 10, 100, -140))));
      this->mobs.addItem(Mob(Creature(BaseStats("🦋 Butterfly", 80, 80, 100))));
      this->mobs.addItem(Mob(Creature(BaseStats("🐌 Snail", 10, 100, -170), Weapon(), Armour(), 200, 50)));
      this->mobs.addItem(Mob(Creature(BaseStats("🐝 Bee", 80, 70, 50), Weapon(), Armour(), 110, 20)));
      this->mobs.addItem(Mob(Creature(BaseStats("🦂 Scorpion", 50, 90, 10), Weapon(), Armour(), 150, 30)));
      this->mobs.addItem(Mob(Creature(BaseStats("🦠 Amoeba", 22, 222, -134), Weapon(), Armour(), 222, 22)));
      // --------------------------------------------------
    }
};
GameItems gameItems;

template<typename T> class TierSorter {
  
  private:
    vector<vector<T>> items;

  public:
    void addItem(int tier, T item) {
      if (items.size() < tier+1) {
        items.resize(tier+1);
      }
      items[tier] = vector<T>{};
      items[tier].push_back(item);
    }

    T getRandomItemOfTier(int tier) {
      vector<T> tierItems;
      try {
        tierItems = items[tier];
      } catch (...) {
        tierItems = items.back();
      }
      return tierItems[rand() % tierItems.size()];
    }
};

#endif
