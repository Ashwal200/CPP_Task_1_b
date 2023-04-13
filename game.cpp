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
    Shape shape_arr[4] = {club, diamond, heart, spade };
	Number number_arr[14] = {two, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace};
    // constructor
    Game::Game(Player& p1 , Player& p2) : player1(p1) , player2(p2) 
    {
        flage = 1;
        play_flage = true;
        create_pack();

        split_pack();

        // for( int i = 0 ; i < player2.stacksize() ; i++){
        //     cout << i << " - number : " << player2.getCard().getNumber() << " , type : " << player2.getCard().getShape() << endl;
        // }
        
    }

    void Game::create_pack(){
        // Creating the deck of cards, 52 cards
        for (int i = 0; i < 13; i++) {
            for (int j = 0; j < 4 ; j++) {
                shuffle_pack.push_back(Card(number_arr[i], shape_arr[j]));
            }
        }
        shuffle_cards();
    }

    void Game::shuffle_cards() {
        srand(time(NULL)); // seed the random number generator

        int n = shuffle_pack.size();
        for (int i = 0; i < n; i++) {
            // Choose a random index from i to n - 1
            int j = i + rand() % (n - i);

            // Swap the ith and jth elements
            swap(shuffle_pack[size_t(i)], shuffle_pack[size_t(j)]);
        }
    }
         
    void swap(int& a, int& b) {
        int temp = a;
        a = b;
        b = temp;
    }

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
        if (player1.stacksize() == 1)
        {
            play_flage = false;
        }
        
        if (player1.stacksize() == 0 || player2.stacksize() == 0){
            play_flage = false;
            throw logic_error("The pack need to be with cards !");
        }
        if (&player1 == &player2){
            throw logic_error("The player's need to be differents !");
        }
        Card player_1_card = player1.getCard();
        Card player_2_card = player2.getCard();
        
        log.push_back(pair<Card, Card>(player_1_card, player_2_card));
        
        int num_of_1_card = player1.getCard().getNumber();
        int num_of_2_card = player2.getCard().getNumber();


        if (num_of_1_card < num_of_2_card)
        {
            for (int i = 0; i < 2*flage; i++)
            {
                player2.setCardesTaken();
                player2.setWins_counter();
            }
            flage = 1;
        }

        if (num_of_1_card > num_of_2_card)
        {
            for (int i = 0; i < 2*flage; i++)
            {
                player1.setCardesTaken();
                player1.setWins_counter();
            }
            flage = 1;
        }
        
        if (num_of_1_card == num_of_2_card && player1.stacksize() > 1)
        {
            cout << "DRAW !" << endl;
            // undercover card
            log.push_back(pair<Card, Card>(player1.getCard(), player2.getCard()));

            cout << "DRAW !!" << endl;
            flage += 2;

            // card to fight
            playTurn();

        }

        else if (num_of_1_card == num_of_2_card && player1.stacksize() == 0)
        {
            cout << "DRAW ! with 0" << endl;
            for (int i = 0; i < flage; i++)
            {
                player1.cardesTaken();
                player2.cardesTaken();
            }
            play_flage = false;
            
        }
        
        else if (num_of_1_card == num_of_2_card && player1.stacksize() == 1)
        {
            cout << "DRAW ! with 1" << endl;
            for (int i = 0; i < flage; i++)
            {
                player1.cardesTaken();
                player2.cardesTaken();
            }
            player1.getCard();
            player2.getCard();
            play_flage = false;
            
        }

        
        
    }



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

    void Game::playAll()
    {
        while (play_flage != false)
        {
            playTurn();
        }        

    }



    void Game::printLastTurn()
    {
        pair<Card, Card> last_turn = log[log.size() - 1];
        cout << player1.getName() << " played "  << get_number_name(last_turn.first.getNumber()) << " of " << get_shape_name(last_turn.first.getShape()) << endl;
        cout << player2.getName() << " played "  << get_number_name(last_turn.second.getNumber()) << " of " << get_shape_name(last_turn.second.getShape()) << endl;
    }



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

    
    void Game::printLog()
    {
        while (log.size() > 0)
        {
            pair<Card, Card> turn = log[log.size() - 1];
            cout << player1.getName() << " played "  << get_number_name(turn.first.getNumber()) << " of " << get_shape_name(turn.first.getShape()) << " ------ " << player2.getName() << " played "  << get_number_name(turn.second.getNumber()) << " of " << get_shape_name(turn.second.getShape()) << endl;
            log.pop_back();
        }

    }

    
    void Game::printStats()
    {
        cout << "Game stats of " << player1.getName() << " :\n   win rate: " << player1.getWins_counter() <<"\n   cards won: "<< player1.cardesTaken() << "\n   draw wins: " << endl;
        cout << "Game stats of " << player2.getName() << " :\n   win rate: " << player2.getWins_counter() <<"\n   cards won: "<< player2.cardesTaken() << "\n   draw wins: " << endl;
    }

   
}

