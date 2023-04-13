#include "player.hpp"
using namespace ariel;
#include <string>

namespace ariel {
    // vector <Card> player_pack;
    Player::Player(string str)  {
        this->name = str;  
        this->cardes_Taken = 0;
        this->wins_counter = 0;
    }


    Card Player::getCard(){
        Card c = pack[size_t(pack.size()-1)];
        pack.pop_back();
        return c;
    }

    void Player::setCard(Card c){
        pack.push_back(c);
    }
    int Player::stacksize() {
        return pack.size();
    }

    void Player::setWins_counter() {
        wins_counter += 1;
    }
    int Player::getWins_counter() {
        return wins_counter;
    }
    void Player::setCardesTaken(){
        cardes_Taken += 1;
    }
    int Player::cardesTaken() {
        return cardes_Taken;
    }

    string Player::getName(){
        return name;
    }

}  // namespace ariel

