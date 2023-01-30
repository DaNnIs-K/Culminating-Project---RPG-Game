// @Author MatteoI, DanK

#include <iostream>
#include "Game.hpp"
#include "gameItems.hpp"
using namespace std;

int main() {
  
  cout << "WELCOME TO BUG HUNTER!" << endl;
  cout << "Press Enter to Start: ";
  cin.get();

  srand(time(NULL));

  string name;
  cout << "What is the name of your character? ";
  getline(cin, name);
  
  Player player = Player(Creature(BaseStats(name)));
  Game g = Game(player);
}
