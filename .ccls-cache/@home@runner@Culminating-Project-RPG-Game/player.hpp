#ifndef PLAYER_H
#define PLAYER_H

#include "creature.hpp"
#include "mob.hpp"

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
        int choice = getInput<int>("Enter your choice here: ");
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

    void doTurn(Mob& opponent) {
      char action = getAction()[0];
      switch(action) {
        case 'A':
          this->attack(opponent);
          break;
        case 'I':
          this->itemMenu();
          break;
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

    void itemMenu() {
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
            return;
        }
        cout << "Invalid input, please re-enter." << endl;
      }
      this->useItem(useableItems[itemNumber-1]);
    }

};

#endif