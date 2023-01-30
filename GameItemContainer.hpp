#ifndef GameItemContainer_hpp
#define GameItemContainer_hpp

#include <string>
#include <vector>
using namespace std;

template <typename StoredType>
class GameItemContainer
{
private:
    vector<StoredType> items;

public:
    StoredType operator[](int index)
    {
        return this->items[index];
    }

    void addItem(StoredType item)
    {
        // insert item into sorted vector
        if ((this->items.size() == 0) || (item.getName() > this->items.back().getName()))
        {
            this->items.push_back(item);
        }
        else
        {
            for (int i = 0; i < this->items.size(); i++)
            {
                if (item.getName() < this->items[i].getName())
                {
                    this->items.insert(this->items.begin() + i, item);
                    break;
                }
            }
        }
    }

    StoredType getItem(string name)
    {
        // use a binary search through the vector using basestats.getName() and return the one with the name that matches
        int mid = items.size() / 2;
        int low = 0;
        int high = items.size() - 1;
        while (low <= high)
        { 
            if (items[mid].getName() == name)
            {
                return items[mid];
            }
            else if (items[mid].getName() < name)
            {
                low = mid + 1;
            }
            else if (items[mid].getName() > name)
            {
                high = mid - 1;
            }
            mid = (low + high) / 2;
        }
    }

    int size()
    {
        return items.size();
    }
};

#endif