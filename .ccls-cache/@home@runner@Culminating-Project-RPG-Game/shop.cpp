#include "shop.hpp"
using namespace std;

#if 0
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

ShopItem Shop::generateItems(int amtOfItems) {
  int miscItemsAmt = amtOfItems / 3;
  int levelItemsAmt = amtOfItems - miscItemsAmt;
  
  for (int i = 0; i < miscItemsAmt; i++) {
    int r = rand() % miscItems.size();
    this->items.push_back(miscItems[r]);
  }
  cout << "test1-" << endl;
  cout << levelItemsAmt << endl;
  sleep(2);
      
  for (int j = 0; j < levelItemsAmt; j++) {
    cout << j << " #" << levelItemsAmt << endl; 
    vector<ShopItem> selectedItemSet = levelItems[rand() % this->level];
    this->items.push_back(selectedItemSet[rand() % selectedItemSet.size()]);
  }
  cout << "endof test1" << endl;
}

#endif