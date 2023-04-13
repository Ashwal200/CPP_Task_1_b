#ifndef GAME_HPP
#define GAME_HPP


#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <vector>
using namespace std;

#include "player.hpp"
using namespace ariel;
namespace ariel{



class Game
{
private:
    Player& player1;
    Player& player2;
    bool play_flage;
    vector<pair <Card, Card> > log;
    vector<Card> shuffle_pack; 
public:
    // constructor
    Game(Player&, Player&);
    void shuffle_cards();
    void split_pack(); 
    void create_pack();
    void playTurn();
    void playAll();
    void printLastTurn();
    void printWiner();
    void printLog();
    void printStats();
    string get_shape_name(int num);
    string get_number_name(int num);
    int getFlage();
    void setFlage();
    void addFlage();
};

}


#endif