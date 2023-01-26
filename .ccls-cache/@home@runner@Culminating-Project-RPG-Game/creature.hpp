#ifndef CREATURE_H
#define CREATURE_H

#include "weapon.hpp"
#include "armour.hpp"
#include "baseStats.hpp"
#include "inventory.hpp"
#include <string>
#include <vector>
#include <array>

using namespace std;

const array<string, 1> actions = {
"ATTACK",
};

class Creature : public BaseStats
{

protected:
  //Inventory inventory;

private:
  double maxHealth;
  double currentHealth;
  double baseDamage;
  Weapon equippedWeapon;
  Armour equippedArmour;

public:
  Inventory inventory;

  Creature(BaseStats stats = BaseStats(), Weapon equippedWeapon = Weapon(), Armour equippedArmour = Armour(), double maxHealth = 100, double baseDamage = 10, Inventory inventory = Inventory()) : BaseStats(stats), equippedWeapon(equippedWeapon), equippedArmour(equippedArmour), maxHealth(maxHealth), baseDamage(baseDamage), currentHealth(maxHealth), inventory(inventory) {}

  double getDamage()
  {
    return this->equippedWeapon.getDamage() + this->baseDamage;
  }

  vector<string> getAvailableActions() {
    vector<string> actions = {"ATTACK"};
    if (this->inventory.size() > 0)
      actions.push_back("ITEM");
    return actions;
  }

  double getCurrentHealth()
  {
    return this->currentHealth;
  }

  double getCriticalChance()
  {
    double cc = this->criticalChance + this->equippedWeapon.getCriticalChance();
    if (cc > 100)
    {
      cc = 100;
    }
    return cc;
  }

  double getCriticalDamage()
  {
    return this->criticalDamage + this->equippedWeapon.getCriticalDamage();
  }

  double getAccuracy()
  {
    return (this->equippedArmour.getAccuracy() + this->equippedWeapon.getAccuracy() + this->accuracy) / 3;
  }

  double getDealtDamage(double damage)
  {
    damage -= this->equippedArmour.getDefence();
    if (damage < 0)
      damage = 0;
    return damage;
  }

  void equipWeapon(Weapon w)
  {
    this->equippedWeapon = w;
  }

  void equipArmour(Armour a)
  {
    this->equippedArmour = a;
  }

  bool isHit()
  {
    double target = rand() % 100 + 1;
    if (this->getAccuracy() < target)
    {
      return false;
    }
    return true;
  }

  void takeDamage(double damage)
  {
    damage = this->getDealtDamage(damage);
    this->currentHealth -= damage;
    if (this->currentHealth < 0)
    {
      this->currentHealth = 0;
    }
  }

  bool isCritical()
  {
    srand(time(NULL));
    int target = rand() % 100 + 1;
    if (this->getCriticalChance() < target)
    {
      return false;
    }
    return true;
  }

  void giveHealth(double amt) {
    this->currentHealth += amt;
    if (this->currentHealth > this->maxHealth)
      this->currentHealth = this->maxHealth;
  }

  void attack(Creature &victim)
  {
    if (this->isHit())
    {
      if (this->isCritical())
      {
        victim.takeDamage(this->getDamage() * (this->getCriticalDamage() / 100 + 1));
      }
      else
      {
        victim.takeDamage(this->getDamage());
      }
    }
    else
    {
      cout << "U missed" << endl;
    }
  }

  void printInfo()
  {
    cout << "Name: " << this->getName() << endl;
    cout << "Health: " << this->getCurrentHealth() << endl;
    cout << "Damage: " << this->getDamage() << endl;
    cout << "Defence: " << this->equippedArmour.getDefence() << endl;
    if (this->equippedWeapon.getName() != "None")
    {
      cout << "Weapon: " << this->equippedWeapon.getName() << endl;
    }
    if (this->equippedArmour.getName() != "None") {
      cout << "Armour: " << this->equippedArmour.getName() << endl;
    }
    cout << "Critical Chance: " << this->getCriticalChance() << "%" << endl;
    cout << "Critical Damage: " << this->getCriticalDamage() << "%" << endl;
    cout << "Accuracy: " << this->getAccuracy() << endl;
    cout << endl;
    //this->inventory.printInventory();
 }

  bool isDead() {
    return this->currentHealth == 0;
  }

  void useItem(string name) {
    if (name == "Health Potion") {
      this->giveHealth(40);
    }
    this->inventory.removeItem(name);
  }

  double getMaxHealth() {
    return this->maxHealth;
  }

};

#endif // CREATURE_H