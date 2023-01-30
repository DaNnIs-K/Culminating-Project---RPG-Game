#ifndef Mob_hpp
#define Mob_hpp

#include "Creature.hpp"
#include <iostream>
#include <string>
using namespace std;

class Mob : public Creature {

  public:
    Mob(Creature creature = Creature()) : Creature(creature) {}

};

#endif