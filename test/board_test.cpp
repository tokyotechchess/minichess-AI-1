/*
test board.h
*/

#include <iostream>
#include "../src/header/board.h"

using namespace minichess_AI;

// prototype declaration
bool TestGetSquare();

int main()
{
    if (TestGetSquare() == false)
        std::cout << "Error : GetSquare" << std::endl;
}

// GetSquare
bool TestGetSquare()
{
    Board b;

    if (b.GetSquare(0, 0) != WKING)
        return false;

    return true;
}