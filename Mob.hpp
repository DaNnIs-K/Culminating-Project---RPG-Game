#ifndef Mob_hpp
#define Mob_hpp

#include "Creature.hpp"
#include <iostream>
#include <string>
using namespace std;

class Mob : public Creature {

  private:
    // string getAction() {}

  public:
    Mob(Creature creature = Creature()) : Creature(creature) {}

    TurnEffect doTurn(Creature &p) {
      this->attack(p);
    }
};

#endif