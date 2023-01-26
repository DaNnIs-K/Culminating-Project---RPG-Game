#ifndef BASESTATS_H
#define BASESTATS_H

#include <string>
#include <iostream>
using namespace std;

class BaseStats {

  protected:
    string name;
    double accuracy;
    double criticalChance;
    double criticalDamage;

  public:
    BaseStats(string name = "None", double criticalChance = 0, double criticalDamage = 0, double accuracy = 100) : name(name), accuracy(accuracy), criticalChance(criticalChance), criticalDamage(criticalDamage) {}

    string getName() {
      return this->name;
    }

    virtual double getAccuracy() {
      return this->accuracy;
    }

    virtual double getCriticalChance() {
      return this->criticalChance;
    }

    virtual double getCriticalDamage() {
      return this->criticalDamage;
    }
};

#endif // BASESTATS_H