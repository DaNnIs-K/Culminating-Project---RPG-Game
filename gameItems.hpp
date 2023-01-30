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
      // -----------------------------------------------------

      // Armour(BaseStats stats = BaseStats(), double defence = 0)
      // ----------------------<Armours>----------------------
      this->armours.addItem(Armour(BaseStats("Iron Platemail", 0, 0, 50), 20));
      this->armours.addItem(Armour(BaseStats("Ranger Coat", 15, 15, 80), 10));
      this->armours.addItem(Armour(BaseStats("Iron Platemail", 0, 0, 50), 20));
      // -----------------------------------------------------

      // Creature(BaseStats stats = BaseStats(), Weapon equippedWeapon = Weapon(), Armour equippedArmour = Armour(), double maxHealth = 100, double baseDamage = 10, Inventory inventory = Inventory())
      // Mob(Creature creature = Creature())
      // ----------------------<Mobs>----------------------
      this->mobs.addItem(Mob(Creature(BaseStats("🐜 Ant", 50, 20, 80))));
      this->mobs.addItem(Mob(Creature(BaseStats("🦟 Mosquito", 80, 10, 100), Weapon(), Armour(), 30, 20)));
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
