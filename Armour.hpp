#ifndef Armour_hpp
#define Armour_hpp

#include <string>
#include "BaseStats.hpp"
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

#endif