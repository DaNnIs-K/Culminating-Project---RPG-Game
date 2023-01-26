#include <string>
#include <vector>
#include <unistd.h>
#include "gameItems.hpp"

#include "player.hpp"

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
    }

    void giveTo(Player &p) {
      switch(this->type) {
        case ARMOUR:
          for (auto& a : armours) {
            if (a.getName() == this->getName()) {
              p.equipArmour(a);
            }
          }
          break;
        case WEAPON:
          for (auto& w : weapons) {
            if (w.getName() == this->getName()) {
              p.equipWeapon(w);
            }
          }
          break;
        case MISC:
          // just add item to inventory
          p.inventory.addItem(this->name);
          break;
      }
    }
};

vector<ShopItem> miscItems = {
  ShopItem("Health Potion", 25),
};

vector<vector<ShopItem>> levelItems = {
  vector<ShopItem> { // level 0 requirement
    ShopItem("Sword", 100, WEAPON),  
    ShopItem("Iron Plate", 100, ARMOUR)
  },
  vector<ShopItem> { // level 1 requirement
    ShopItem("Strength Potion", 50)
  },
};

class Shop {

  private:
    vector<ShopItem> items;
    int level;

  void generateItems(int amtOfItems) {
    int miscItemsAmt = amtOfItems / 3;
    if (miscItemsAmt == 0)
      miscItemsAmt = 1;
    int levelItemsAmt = amtOfItems - miscItemsAmt;
    if (levelItemsAmt == 0) {
      levelItemsAmt = 1;
    }
    for (int i = 0; i < miscItemsAmt; i++) {
      int r = rand() % miscItems.size();
      this->items.push_back(miscItems[r]);
    }
    for (int j = 0; j < levelItemsAmt; j++) {
      vector<ShopItem> selectedItemSet = levelItems[rand() % this->level];
      this->items.push_back(selectedItemSet[rand() % selectedItemSet.size()]);
      }
    }

  public:
    Shop(int level, int amtOfItems) : level(level+1) {
      this->generateItems(amtOfItems);
    }

    void print() {
      cout << "Shop:" << endl;
      for (int i = 0; i < this->items.size(); i++) {
        cout << "  Item " << i+1 << ": ";
        cout << endl;
        this->items[i].print();
      }
    }

    void sellTo(Player& p) {
      system("clear");
      cout << "$: " << p.getCurrency() << endl;
      p.inventory.print();
      cout << endl;
      this->print();
      cout << endl;
      int itemNumber;
      while (true) {
        string entry = p.getInput<string>("Enter the number of the item you want to buy, or enter exit: ");
        try {
          itemNumber = stoi(entry);
          this->items[itemNumber-1];
          break;
        } catch(...) {
          if (entry == "exit")
            return;
        }
        cout << "Invalid input, please re-enter." << endl;
      }
      ShopItem selected = this->items[itemNumber-1];
      if (p.getCurrency() < selected.getPrice()) {
        cout << "You can't afford this, please retry." << endl;
        sleep(1);
        sellTo(p);
      } else {
        cout << "You bought the " << selected.getName() << " for " << selected.getPrice() << " cash." << endl;
        p.takeCurrency(selected.getPrice());
        selected.giveTo(p);
        this->items.erase(this->items.begin() + (itemNumber-1));
        sleep(1);
        sellTo(p);
      }
    }

};