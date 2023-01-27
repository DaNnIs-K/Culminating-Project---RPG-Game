#ifndef ShopItem_hpp
#define ShopItem_hpp

#include <string>
#include "gameItems.hpp"
using namespace std;

enum ItemType {
  ARMOUR,
  WEAPON,
  MISC
};

class ShopItem {
  
  private:
    string name;
    double price;
    ItemType type;

  public:
    ShopItem(string name, double price, ItemType type = MISC) : name(name), price(price), type(type) {}

    string getName() {
      return this->name;
    }

    double getPrice() {
      return this->price;
    }

    void print() {
      cout << "    Name: " << this->name << endl;
      cout << "    Price: " << this->price << endl;
      switch(this->type) {
        case WEAPON:
        {
          Weapon weapon = gameItems.weapons.getItem(this->name);
          cout << "    Damage: " << weapon.getDamage() << endl;
          weapon.printBaseStats("    ", false);
          break;
        }
        case ARMOUR:
        {
          Armour armour = gameItems.armours.getItem(this->name);
          cout << "    Defence: " << armour.getDefence() << endl;
          armour.printBaseStats("    ", false);
          break;
        }
      }
    }

    void giveTo(Player &p) {
      switch(this->type) {
        case ARMOUR:
          p.equipArmour(gameItems.armours.getItem(this->name));
          break;
        case WEAPON:
          p.equipWeapon(gameItems.weapons.getItem(this->name));
          break;
        case MISC:
          p.inventory.addItem(this->name);
          break;
      }
    }
};

#endif