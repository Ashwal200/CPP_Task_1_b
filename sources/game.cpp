#include <iostream>
#include <vector>
#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
#include <cstdlib>
#include <ctime>
#include <random>
using namespace std;

#include "game.hpp"
#include "player.hpp"
#include "card.hpp"
using namespace ariel;

namespace ariel{
    int static flage = 0;
    Shape shape_arr[4] = {club, diamond, heart, spade };
	Number number_arr[14] = {two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace};
    // Game constructor
    Game::Game(Player& p1 , Player& p2) : player1(p1) , player2(p2) 
    {
        // check if one of the players is playing, and cannot play in two different game concurrency
        if(player1.getStatus() || player2.getStatus())
        {
            throw invalid_argument("Can't play on two games concurrency");
        }

        draw_counter = 0;
        setFlage();
        play_flage = true;

        // Change the status of each player that he in a game
        player1.setStatus();
        player2.setStatus();

        // create a new packet, and shuffle it
        create_pack();

        // split the packet for the players, each player get 26 cards
        split_pack();

        
    }

    // set the counter for the draw parts
    void Game::setFlage(){
        flage = 1;
    }
    // add to the counter if there is a draw
    void Game::addFlage(){
        flage += 2;
    }
    // get the value 
    int Game::getFlage(){
        return flage;
    }

    // create a packet from the number that in the arrays
    // number from 2-Ace any number get club, diamond, heart, and spade 
    void Game::create_pack(){
        // Creating the deck of cards, 52 cards
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 4 ; j++) {
                shuffle_pack.push_back(Card(number_arr[i], shape_arr[j]));
            }
        }
        shuffle_cards();
    }

    // shuffle the cards in the packet, using random numbers
    void Game::shuffle_cards() {
        srand(time(NULL)); // seed the random number generator

        int n = shuffle_pack.size();
        for (int i = 0; i < n; i++) {
            // Choose a random index from i to n - 1
            int j = i + rand() % (n - i);

            // Swap the cards in the i place with the j place
            swap(shuffle_pack[size_t(i)], shuffle_pack[size_t(j)]);
        }
    }
    // swap function for the shuffle function
    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

    // split the cards between the players
    void Game::split_pack(){
        for (int i = 0; i < 26; i++) {
            player1.setCard(shuffle_pack[size_t(i)]);
        }
        for (int i = 26; i < 52; i++) {
            player2.setCard(shuffle_pack[size_t(i)]);
        }
    }




    void Game::playTurn()
    {
        // if one of the players don't have cards throw exception
        if (player1.stacksize() == 0 || player2.stacksize() == 0){
            throw logic_error("The pack need to be with cards !");
            return;
        }

        // if we only have one turn to play change the flage to false for the playAll function
        if (player1.stacksize() == 1)
        {
            play_flage = false;
        }
        
        // if the players that playing is the same player throw exception.
        if (&player1 == &player2){
            throw logic_error("The player's need to be differents !");
            return;
        }

        Card player_1_card = player1.getCard();
        Card player_2_card = player2.getCard();
        // put in the log the pairs of cards that we play with
        log.push_back(pair<Card, Card>(player_1_card, player_2_card));
        
        int num_of_1_card = player_1_card.getNumber();
        int num_of_2_card = player_2_card.getNumber();

        // in our assigment we told that 2 is bigger then ace
        if (num_of_1_card == 14 && num_of_2_card == 2)
        {
            for (int i = 0; i < getFlage(); i++)
            {
                player2.setCardesTaken();
                player2.setWins_counter();
            }
            setFlage();
        }
        // same
        else if (num_of_2_card == 14 && num_of_1_card == 2)
        {
            for (int i = 0; i < getFlage(); i++)
            {
                player1.setCardesTaken();
                player1.setWins_counter();
            }
            setFlage();
        }
        // check which card is bigger using the number of the cards, and update the players.
        else if (num_of_1_card < num_of_2_card)
        {
            for (int i = 0; i < getFlage(); i++)
            {
                player2.setCardesTaken();
                player2.setWins_counter();
            }
            // reset the draw counter
            setFlage();
        }
        // check which card is bigger using the number of the cards, and update the players.
        else if (num_of_1_card > num_of_2_card)
        {
            for (int i = 0; i < getFlage(); i++)
            {
                player1.setCardesTaken();
                player1.setWins_counter();
            }
            // reset the draw counter
            setFlage();
        }
        // if we have draw and we have enough cards to kepp playing
        else if (num_of_1_card == num_of_2_card && player1.stacksize() > 1)
        {
            draw_counter++;
            // undercover card to the log
            log.push_back(pair<Card, Card>(player1.getCard(), player2.getCard()));

            // add 2 to the draw counter
            addFlage();

            // card to fight
            playTurn();

        }
        // if there is a draw and we can't keep playing split the cards that are in the "air"
        else if (num_of_1_card == num_of_2_card && player1.stacksize() == 0)
        {
            draw_counter++;
            int split = (getFlage() + 1)/2;
            player1.setCardesTaken_byValue(split);
            player2.setCardesTaken_byValue(split);

            play_flage = false;
            
        }
        // if there is a draw and we can't keep playing split the cards that are in the "air", and add the last card that we did't use.
        else if (num_of_1_card == num_of_2_card && player1.stacksize() == 1)
        {
            draw_counter++;
            int split = (getFlage() + 1 + 2)/2;
            player1.setCardesTaken_byValue(split);
            player2.setCardesTaken_byValue(split);

            player1.getCard();
            player2.getCard();
            play_flage = false;
            
        }
        
    }


    // return the number name of the Card
    string Game::get_number_name(int num){
        switch (num)
        {
            case 11:
                return "Jack";
                break;
            case 12:
                return "Queen";
                break;
            case 13:
                return "King";
                break;
            case 14:
                return "Ace";
                break;
            default:
                string str_num;
                stringstream ss;
                ss << num;
                ss >> str_num;
                return str_num;
        }
    }
    // return the shape name of the Card
    string Game::get_shape_name(int num)
    {
        switch(num) {
            case 1:
                return "Clubs";
                break;
            case 2:
                return "Diamonds";
                break;
            case 3:
                return "Hearts";
                break;
            case 4:
                return "Spades";
                break;
            default:
                return "Not exist!";
        }
    }

    // play the playturn until we have a winner or draw
    void Game::playAll()
    {
        while (play_flage != false)
        {
            playTurn();
        }        
        // update the status that the player are free to play in another game
        player1.setStatus();
        player2.setStatus();

    }


    // print the last turn that play and we have sigh it in the log
    void Game::printLastTurn()
    {
        pair<Card, Card> last_turn = log[log.size() - 1];
        cout << player1.getName() << " played "  << get_number_name(last_turn.first.getNumber()) << " of " << get_shape_name(last_turn.first.getShape()) << endl;
        cout << player2.getName() << " played "  << get_number_name(last_turn.second.getNumber()) << " of " << get_shape_name(last_turn.second.getShape()) << endl;
    }


    // print the name of the winner, the player with the most cardestaken if there isn't print Draw
    void Game::printWiner()
    {
        string winner = "";
        if(player1.cardesTaken() > player2.cardesTaken()){
            winner = player1.getName();
        }

        if(player1.cardesTaken() < player2.cardesTaken()){
            winner = player2.getName();
        }

        else{
            winner = "The game ends with draw !";
        }
        cout << winner << endl;
    }

    // print all the turns that play and we have sigh it inthe log
    void Game::printLog()
    {
        int i = 1;
        while (log.size() > 0)
        {
            pair<Card, Card> turn = log[log.size() - 1];
            cout << i << " -- " << player1.getName() << " played "  << get_number_name(turn.first.getNumber()) << " of " << get_shape_name(turn.first.getShape()) << " ------ " << player2.getName() << " played "  << get_number_name(turn.second.getNumber()) << " of " << get_shape_name(turn.second.getShape()) << endl;
            log.pop_back();
            i++;
        }

    }

    // print stats about the game
    void Game::printStats()
    {
        cout << "Game stats of " << player1.getName() << " :\n   win rate: " << player1.getWins_counter() <<"\n   cards won: "<< player1.cardesTaken() << "\n" <<endl;
        cout << "Game stats of " << player2.getName() << " :\n   win rate: " << player2.getWins_counter() <<"\n   cards won: "<< player2.cardesTaken() << endl;
        cout << "The number of Draws is : " << draw_counter << endl;
    }

   
}


