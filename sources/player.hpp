
#ifndef PLAYER_HPP
#define PLAYER_HPP

#include <string>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;
#include "card.hpp"

namespace ariel{


class Player
{
private:
    string name;
    vector <Card> pack; 
    int cardes_Taken;
    int wins_counter;
    bool status;
public:
    
    // constructor
    Player(string str);
    Card getCard();
    void setCard(Card c);
    int stacksize();
    int cardesTaken();
    string getName();
    int getWins_counter(); 
    void setWins_counter();
    void setCardesTaken();
    void setCardesTaken_byValue(int num);
    bool getStatus();
    void setStatus();
};


}

#endif