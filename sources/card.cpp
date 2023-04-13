#include <iostream>
#include <fstream>
#include <sstream>
#include <stdexcept>
using namespace std;

#include "card.hpp"
using namespace ariel;


namespace ariel{
    
    Card::Card(Number num , Shape str)
    {
        number = num;
        shape = str;
    }
    // Return the value of the shape on the card
    Shape Card::getShape() { return shape; }
    // Return the number on the card
	Number Card::getNumber() { return number; }



}