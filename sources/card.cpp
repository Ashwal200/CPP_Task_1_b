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
    Shape Card::getShape() { return shape; }
	Number Card::getNumber() { return number; }



}