#ifndef GameItemContainer
#define GameItemContainer

#include "baseStats.hpp"
#include <string>
#include <vector>
using namespace std;

class GameItemContainer
{
    private:
        vector<BaseStats> items;

    public:
        // in the function below, use quicksort to add a new item to the vector. Use its .name property.
        void addItem(BaseStats item) {
            // since the vector will always be sorted, it is better to use insertion sort over quicksort, as the best case time complexity for insertion sort is O(n). Quicksort's best case is O(n log n).
            if (items.size() == 0) {
                items.push_back(item);
            } else {
                for (int i = 0; i < items.size(); i++) {
                    if (item.getName() < items[i].getName()) {
                        items.insert(items.begin() + i, item);
                        break;
                    }
                }
            }
        }

        BaseStats getItem(string name) {
            // use a binary search through the vector using basestats.getName() and return the one with the name that matches
            int mid = items.size() / 2;
            int low = 0;
            int high = items.size() - 1;
            while (low <= high) {
                if (items[mid].getName() == name) {
                    return items[mid];
                } else if (items[mid].getName() < name) {
                    low = mid + 1;
                } else {
                    high = mid - 1;
                }
                mid = (low + high) / 2;
            }
        }
};

#endif