#include <string>
using namespace std;

class Armor {

  private:
    string name;
    double defence; 

  public:
    Armor(string name, double defence) : defence(defence), name(name) {}

    double getDefence() {
      return this->defence;
    }

    string getName() {
      return this->name;
    }
};