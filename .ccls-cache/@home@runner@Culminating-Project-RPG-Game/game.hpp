#ifndef GAME_H
#define GAME_H

#include "mob.hpp"
#include "player.hpp"
#include "creature.hpp"
#include "baseStats.hpp"
#include "shop.hpp"
#include "gameItems.hpp"
#include <vector>
#include <map>
#include <iostream>
#include <string>
using namespace std;

class Game {

  enum TurnState {
    PLAYER,
    MOB
  };

  enum GameState {
    PLAYERTURN,
    MOBTURN,
    INTERSTICE
  };

  private:
    Player &player;
    GameState gameState;
    int numOfMobs;
    int worldLevel;

  public:
    Game(Player &p) : player(p) {
      this->numOfMobs = mobs.size();
      this->gameState = PLAYERTURN;
      this->worldLevel = 0;
    }

  void gamePlay() {
    bool game = true;
    while (game) {
      // if (this->numOfMobs == 0) {
      //   cout << "There is no Mobs left." << endl;
      //   break;
      // }
      Shop shop(this->worldLevel, (rand() % 5) + 1);
      if (this->player.getCurrentHealth() == 0) {
        cout << "Game Over" << endl;
        break;
      }
      int action; 
      cout << "1: fight | 2: shop | 3: leave" << endl;
      cout << "Choose Your Action: ";
      cin >> action;
      switch (action) {
        case 3:
          game = false;
          break;
        case 1:
          fight();
          break;
        case 2:
          shop.sellTo(player);
          break;
      };
    }
  }

  void fight() {
    int cMob = rand() % this->numOfMobs;
    Mob currentMob = mobs[cMob];
    // since we r using same mobs many times.
    // this->numOfMobs -= 1;
    // this->mobs.erase(this->mobs.begin()+cMob);

    while (!currentMob.isDead() && !this->player.isDead()) {
      
      system("clear");
      cout << "     <MOB>      " << endl;
      currentMob.printInfo();
      cout << "    <PLAYER>     " << endl;
      this->player.printInfo();
      
      if (this->gameState == PLAYERTURN) {
         this->player.doTurn(currentMob); 
        this->gameState = MOBTURN;
      } else {
        currentMob.attack(this->player);
        this->gameState = PLAYERTURN;
      }
    }
    
    system("clear");
    cout << "     <MOB>      " << endl;
    currentMob.printInfo();
    cout << "    <PLAYER>     " << endl;
    this->player.printInfo();
    
    if (!this->gameState == PLAYERTURN) { //b/c last htter is mob
      player.giveCurrency(currentMob.getMaxHealth());
      cout << "You Defeated the Mob" << endl;
    }
  }

  void getMobsInfo() {
    for (Mob& mob : mobs) {
      mob.printInfo();
    }
  }

  void getPlayerInfo() {
    player.printInfo();
  }

};

#endif