#ifndef WEAPON_H
#define WEAPON_H

#include <string>

#include "baseStats.hpp"

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