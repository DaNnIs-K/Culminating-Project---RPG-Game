#ifndef Game_hpp
#define Game_hpp

#include "Mob.hpp"
#include "Player.hpp"
#include "Creature.hpp"
#include "BaseStats.hpp"
#include "Shop.hpp"
#include "gameItems.hpp"
#include "TierSorter.hpp"
#include <vector>
#include <map>
#include <iostream>
#include <string>
#include <chrono>
#include <thread>
using namespace std;

class Game
{

    enum GameState
    {
        FIGHT,
        INTERSTICE
    };

    enum Turn
    {
        PLAYER,
        MOB,
    };

private:
    TierSorter<Mob> mobLevels;
    Player &player;
    GameState gameState;
    int worldLevel;
    Turn currentTurn;

    void fight()
    {

        Mob currentMob = mobLevels.getRandomItemOfTier(worldLevel);

        while (!currentMob.isDead() && !this->player.isDead())
        {

            system("clear");
            cout << "     <MOB>      " << endl;
            currentMob.printInfo();
            cout << "    <PLAYER>     " << endl;
            getPlayerInfo();

            if (this->currentTurn == PLAYER)
            {
                TurnEffect turnEffectOnFight = this->player.doTurn(currentMob);
                this->currentTurn = MOB;
                switch (turnEffectOnFight)
                {
                case TurnEffect::FLEE:
                {
                    int selectedNum = (rand() % 4) + 1;
                    if (selectedNum == 4)
                    {
                        cout << player.getName() << " has escaped the fight." << endl;
                        this->gameState = INTERSTICE;
                        this_thread::sleep_for(1000ms);
                        return;
                    }
                    else
                    {
                        cout << player.getName() << " has attempted to flee, sadly they were caught." << endl;
                        this_thread::sleep_for(1000ms);
                    }
                    break;
                }
                case TurnEffect::CONTINUE:
                {
                    this->currentTurn = PLAYER;
                    break;
                }
                }
            }
            else
            {
                currentMob.attack(this->player);
                this->currentTurn = PLAYER;
            }
        }

        system("clear");
        cout << "     <MOB>      " << endl;
        currentMob.printInfo();
        cout << "    <PLAYER>     " << endl;
        getPlayerInfo();

        if (!this->currentTurn == PLAYER)
        { // b/c last htter is mob
            player.giveCurrency(currentMob.getMaxHealth());
            cout << "You defeated the Mob" << endl;
            this->gameState = INTERSTICE;
            this->worldLevel++;
        }
        else
        {
            cout << "You died." << endl;
            cout << "Thanks for playing!" << endl;
            exit(0);
        }
    }

    void interstice()
    {
        Shop currentShop(this->worldLevel, (rand() % 2) + 3);
        while (true)
        {
            system("clear");
            int action = player.getIntInput("(1: Fight | 2: Open Shop | 3: Quit): ");
            switch (action)
            {
            case 1:
            {
                this->gameState = FIGHT;
                this->currentTurn = PLAYER;
                return;
            }
            case 2:
            {
                currentShop.sellTo(player);
                break;
            }
            case 3:
            {
                cout << "Thanks for playing!" << endl;
                exit(0);
                break;
            }
            }
        }
    }

    void gamePlay()
    {
        system("clear");
        while (1)
        {
            switch (gameState)
            {
            case INTERSTICE:
            {
                this->interstice();
                break;
            }
            case FIGHT:
            {
                this->fight();
                break;
            }
            }
        }
    }

public:
    Game(Player &p) : player(p)
    {

        mobLevels.addItem(0, gameItems.mobs.getItem("🦗 Cricket"));
        mobLevels.addItem(0, gameItems.mobs.getItem("🐛 Caterpillar"));
        mobLevels.addItem(1, gameItems.mobs.getItem("🐜 Ant"));
        mobLevels.addItem(1, gameItems.mobs.getItem("🦋 Butterfly"));
        mobLevels.addItem(2, gameItems.mobs.getItem("🐞 Lady Beetle"));
        mobLevels.addItem(2, gameItems.mobs.getItem("🦠 Amoeba"));
        mobLevels.addItem(3, gameItems.mobs.getItem("🐝 Bee"));
        mobLevels.addItem(3, gameItems.mobs.getItem("🦂 Scorpion"));
        mobLevels.addItem(4, gameItems.mobs.getItem("🦟 Mosquito"));
        mobLevels.addItem(4, gameItems.mobs.getItem("🐌 Snail"));

        this->gameState = INTERSTICE;
        this->worldLevel = 0;
        while (true)
        {
            this->gamePlay();
        }
    }

    // gonna move this to private

    void getPlayerInfo()
    {
        player.printInfo();
    }
};

#endif