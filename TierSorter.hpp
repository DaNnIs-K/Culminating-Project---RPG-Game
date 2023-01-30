#ifndef TierSorter_hpp
#define TierSorter_hpp

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