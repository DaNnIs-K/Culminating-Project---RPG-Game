#ifndef ARMOUR_H
#define ARMOUR_H

#include <string>
#include "baseStats.hpp"
using namespace std;

class Armour : public BaseStats {

  private:
    double defence; 

  public:
    Armour(BaseStats stats = BaseStats(), double defence = 0) : defence(defence), BaseStats(stats) {}

    double getDefence() {
      return this->defence;
    }
};

#endif // ARMOUR_H