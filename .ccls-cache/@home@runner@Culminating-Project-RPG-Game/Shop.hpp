#ifndef Shop_hpp
#define Shop_hpp

#include <string>
#include <vector>
#include <unistd.h>
#include "gameItems.hpp"
#include "ShopItem.hpp"
#include "Player.hpp"

using namespace std;

vector<ShopItem> miscItems = {
  ShopItem("Health Potion", 50),
};

vector<vector<ShopItem>> levelItems = {
  vector<ShopItem> { // level 0 requirement
    ShopItem("Sword", 100, WEAPON),
    ShopItem("Wooden Bow", 100, WEAPON),
    ShopItem("Iron Platemail", 150, ARMOUR),
    ShopItem("Ranger Coat", 150, ARMOUR)
  },
  vector<ShopItem> { // level 1 requirement
    ShopItem("Flintlock", 250, WEAPON)
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
      if (this->level > levelItems.size())
        this->level = levelItems.size();
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
      cout << "Money: " << p.getCurrency() << endl;
      p.inventory.print();
      cout << endl;
      this->print();
      cout << endl;
      int itemNumber;
      while (true) {
        string input = p.getInput<string>("Enter the number of the item you want to buy, or enter exit: ");
        if (input == "exit")
          return;
        else {
          try {
            int num = stoi(input);
            if ((num > 0) && (num <= items.size()))
            {
              itemNumber = num;
              break; 
            }
          } catch (...) {}
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

#endif