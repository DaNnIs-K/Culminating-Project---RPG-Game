#ifndef BaseStats_hpp
#define BaseStats_hpp

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
    BaseStats(string name = "None", double criticalChance = 0, double criticalDamage = 0, double accuracy = 85) : name(name), accuracy(accuracy), criticalChance(criticalChance), criticalDamage(criticalDamage) {}

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

    void printBaseStats(string prefix = "", bool name = true) {
      if (name) {
        cout << prefix << "Name: " << this->name << endl;
      }
      cout << prefix << "Accuracy: " << this->accuracy << "%" << endl;
      cout << prefix << "Critical Chance: +" << this->criticalChance << "%" << endl;
      cout << prefix << "Critical Damage: +" << this->criticalDamage << "%" << endl;
    }

};

#endif