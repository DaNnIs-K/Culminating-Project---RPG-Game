#ifndef INVENTORY_H
#define INVENTORY_H

#include <map>
#include <string>
#include <vector>
using namespace std;

class Inventory {

  private:
    map<string, int> items;

  public:
    void addItem(string itemName, int amt = 1) {
      // maps are binary search trees, so this is efficient.
      if (this->containsItem(itemName))
      {
        this->items[itemName] += abs(amt);
      } else {
        this->items[itemName] = amt;
      }
    }

    void removeItem(string itemName, int amt = 1) {
      if (this->containsItem(itemName))
      {
        this->items[itemName] -= amt;
        if (this->items[itemName] <= 0)
          this->items.erase(itemName);
      }
    }

    bool containsItem(string itemName) {
      return (this->items.find(itemName) != this->items.end());
    }

    void print() {
      cout << "Inventory:" << endl;
      if (items.size() == 0) {
        cout << "  Nothing" << endl;
        return;
      }
      int count = 1;
      for (const auto& item : items) {
        cout << "Item " << count << ": " << item.first << " - " << item.second << endl;
        count++;
      }
    }

    int size() {
      return this->items.size();
    }

    vector<string> getItems() {
      vector<string> items;
      for (const auto& item : this->items) {
        items.push_back(item.first);
      }
      return items;
    }

};

#endif