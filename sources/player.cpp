#include "player.hpp"
using namespace ariel;
#include <string>

namespace ariel {
    // Constructor for the player
    Player::Player(string str)  {
        this->name = str;  
        this->cardes_Taken = 0;
        this->wins_counter = 0;
        this->status = false;
    }

    // get the card on the "top" of the pack, and earse him from the pack.
    Card Player::getCard(){
        Card c = pack[size_t(pack.size()-1)];
        pack.pop_back();
        return c;
    }

    // set the cards for the player
    void Player::setCard(Card c){
        pack.push_back(c);
    }
    int Player::stacksize() {
        return pack.size();
    }

    // status about the player if he in a card game or not.
    bool Player::getStatus(){
        return status;
    }

    // set the status
    void Player::setStatus(){
        status = !status;
    }
    
    // update the counter
    void Player::setWins_counter() {
        wins_counter += 1;
    }
    // get the number of winning for this player
    int Player::getWins_counter() {
        return wins_counter;
    }
    // update the cardestaken by two
    void Player::setCardesTaken(){
        cardes_Taken += 2;
    }
    // update the cardestaken by any value
    void Player::setCardesTaken_byValue(int num){
        cardes_Taken += num;
    }

    // get the number of cardestaken
    int Player::cardesTaken() {
        return cardes_Taken;
    }
    
    // get the name of the player
    string Player::getName(){
        return name;
    }

}  // namespace ariel

