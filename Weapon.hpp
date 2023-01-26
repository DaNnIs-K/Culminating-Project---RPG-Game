#ifndef Weapon_hpp
#define Weapon_hpp

#include <string>

#include "BaseStats.hpp"

using namespace std;

class Weapon : public BaseStats {

  private:
    double damage;
  public:
    Weapon(BaseStats stats = BaseStats(), double dmg = 0) : BaseStats(stats), damage(dmg) {}
    double getDamage() {
      return this->damage;
    }
};

#endif