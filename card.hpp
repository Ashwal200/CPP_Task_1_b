#ifndef CARD_HPP
#define CARD_HPP


#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

namespace ariel{

enum Shape {club = 1, diamond, heart, spade};
enum Number {two = 2, three, four, five, six, seven, eight, nine, ten, jack, queen, king, ace};

class Card
{
private:
    Shape shape;
    Number number;
public:
    Card(){}
    Card(Number num , Shape str);
    Shape getShape();
	Number getNumber();
};

}


#endif


// https://www.tutorialspoint.com/how-to-use-enums-in-cplusplus