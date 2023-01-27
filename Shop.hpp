#ifndef Shop_hpp
#define Shop_hpp

#include <string>
#include <vector>
#include <chrono>
#include <thread>
#include "gameItems.hpp"
#include "Player.hpp"

using namespace std;

enum ItemType
{
  ARMOUR,
  WEAPON,
  MISC
};

class ShopItem
{

private:
  string name;
  double price;
  ItemType type;

public:
  ShopItem(string name, double price, ItemType type = MISC) : name(name), price(price), type(type) {}

  string getName()
  {
    return this->name;
  }

  double getPrice()
  {
    return this->price;
  }

  void print()
  {
    cout << "    Name: " << this->name << endl;
    cout << "    Price: " << this->price << endl;
    switch (this->type)
    {
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

  void giveTo(Player &p)
  {
    switch (this->type)
    {
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

vector<ShopItem> miscItems = {
    ShopItem("Health Potion", 50),
};

vector<vector<ShopItem>> levelItems = {
    vector<ShopItem>{
        // level 0 requirement
        ShopItem("Sword", 100, WEAPON),
        ShopItem("Wooden Bow", 100, WEAPON),
    },
    vector<ShopItem>{
        // level 1 requirement
        ShopItem("Iron Platemail", 150, ARMOUR),
        ShopItem("Ranger Coat", 150, ARMOUR),
    },
    vector<ShopItem>{
        // level 2 requirement
        ShopItem("Flintlock", 250, WEAPON),
    },
};

class Shop
{

private:
  vector<ShopItem> items;
  int level;

  void generateItems(int amtOfItems)
  {
    int miscItemsAmt = amtOfItems / 3;
    if (miscItemsAmt == 0)
      miscItemsAmt = 1;
    int levelItemsAmt = amtOfItems - miscItemsAmt;
    if (levelItemsAmt == 0)
    {
      levelItemsAmt = 1;
    }
    for (int i = 0; i < miscItemsAmt; i++)
    {
      int r = rand() % miscItems.size();
      this->items.push_back(miscItems[r]);
    }
    for (int j = 0; j < levelItemsAmt; j++)
    {
      vector<ShopItem> selectedItemSet = levelItems[rand() % this->level];
      this->items.push_back(selectedItemSet[rand() % selectedItemSet.size()]);
    }
  }

public:
  Shop(int level, int amtOfItems) : level(level + 1)
  {
    if (this->level > levelItems.size())
      this->level = levelItems.size();
    this->generateItems(amtOfItems);
  }

  void print()
  {
    cout << "Shop:" << endl;
    for (int i = 0; i < this->items.size(); i++)
    {
      cout << "  Item " << i + 1 << ": ";
      cout << endl;
      this->items[i].print();
    }
  }

  void sellTo(Player &p)
  {
    system("clear");
    cout << "Money: " << p.getCurrency() << endl;
    p.inventory.print();
    cout << endl;
    this->print();
    cout << endl;
    int itemNumber;
    while (true)
    {
      string input = p.getInput<string>("Enter the number of the item you want to buy, or enter exit: ");
      if (input == "exit")
        return;
      else
      {
        try
        {
          int num = stoi(input);
          if ((num > 0) && (num <= items.size()))
          {
            itemNumber = num;
            break;
          }
        }
        catch (...) {}
      }
      cout << "Invalid input, please re-enter." << endl;
    }
    ShopItem selected = this->items[itemNumber - 1];
    if (p.getCurrency() < selected.getPrice())
    {
      cout << "You can't afford this, please retry." << endl;
      this_thread::sleep_for(1000ms);
      sellTo(p);
    }
    else
    {
      cout << "You bought the " << selected.getName() << " for " << selected.getPrice() << " cash." << endl;
      p.takeCurrency(selected.getPrice());
      selected.giveTo(p);
      this->items.erase(this->items.begin() + (itemNumber - 1));
      this_thread::sleep_for(1000ms);
      sellTo(p);
    }
  }
};

#endif