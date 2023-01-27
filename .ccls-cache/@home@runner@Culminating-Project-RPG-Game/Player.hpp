#ifndef Player_hpp
#define Player_hpp

#include "Creature.hpp"

using namespace std;

class Player : public Creature {

  private:
    double currency;

    string getAction() {
      vector<string> availableActions = this->getAvailableActions();
      for (int i = 1; i <= availableActions.size(); i++) {
        cout << i << ": " << availableActions[i-1] << endl;
      }
      string action;
      while (true) {
        int choice = getIntInput("Enter your choice here: ");
        if ((choice < 1) || (choice > availableActions.size()))
          cout << "Invalid input. Please retry." << endl;
        else {
          action = availableActions[choice-1];
          break;
        }
      }
      return action;
    }

  public:
    Player(Creature creature, double currency = 100) : Creature(creature), currency(currency) {}

    TurnEffect doTurn(Creature& opponent) {
      char action = getAction()[0];
      switch(action) {
        case 'A':
          this->attack(opponent);
          return TurnEffect::NONE;
        case 'I':
          if (!this->itemMenu())
            return TurnEffect::CONTINUE;
          else
            return TurnEffect::NONE;
        case 'F':
          return TurnEffect::FLEE;
      };
    }

    double getCurrency() {
      return this->currency;
    }

    void giveCurrency(double amt) {
      this->currency += abs(amt);
    }

    void takeCurrency(double amt) {
      this->currency -= abs(amt);
    }

    template<class T>T getInput(string message = "") {
      cout << message;
      T input;
      cin >> input;
      return input;
    }

    int getIntInput(string message = "") {
      string input = getInput<string>(message);
      try {
        return stoi(input);
      } catch (...) {
        cout << "Invalid input. Try again." << endl;
        return getIntInput(message);
      }
    }

    bool itemMenu() {
      vector<string> useableItems = this->inventory.getItems();
      this->inventory.print();
      int itemNumber;
      while (true) {
        string entry = this->getInput<string>("Enter the number of the item you want to use, or enter exit: ");
        try {
          itemNumber = stoi(entry);
          useableItems[itemNumber-1];
          break;
        } catch(...) {
          if (entry == "exit")
            return false;
        }
        cout << "Invalid input, please re-enter." << endl;
      }
      this->useItem(useableItems[itemNumber-1]);
      return true;
    }

};

#endif