#ifndef CARD_HPP
#define CARD_HPP


#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

namespace ariel{
// Shape represents the suits of playing cards: club, diamond, heart, and spade. 
// Each of these values is an integer value start at 1.
enum Shape {club = 1, diamond, heart, spade};

// Number represents the face values of playing cards: two lose to ten, as well as jack, queen, and king.
// Each of these values is an integer value starting at 2.
enum Number {two = 2, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace};

class Card
{
// Private members
private:
    Shape shape;
    Number number;
public:
    Card(Number num , Shape str);
    Shape getShape();
	Number getNumber();
};

}


#endif


// https://www.tutorialspoint.com/how-to-use-enums-in-cplusplus