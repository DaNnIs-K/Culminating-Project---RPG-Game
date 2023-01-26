#ifndef MOB_H
#define MOB_H

#include "creature.hpp"
#include <iostream>
#include <string>
using namespace std;

class Mob : public Creature {

  private:
    // string getAction() {}

  public:
    Mob(Creature creature = Creature()) : Creature(creature) {}

    // void doTurn(Player &p) {}
};

#endif