/*
test board.h
*/

#include <iostream>
#include <string>
#include "../src/header/board.h"
#include "../src/header/util/error.h"

using namespace minichess_AI;

// prototype declaration
MCError TestGetSquare();

int main()
{
    MCError e;
    if ((e = TestGetSquare()) != mcet::NoErr)
    {
        if (e == mcet::TestErr)
        {
            std::cout << "Test Error : " + e.GetMessage() << std::endl;
        }
    }
}

// GetSquare
MCError TestGetSquare()
{
    Board b;

    if (b.GetSquare(1, 0) != WKING)
        return mcet::genTestErr("GetSquare(1, 0) is wrong");
    if (b.GetSquare(1, 1) != WQUEEN)
        return mcet::genTestErr("GetSquare(1, 1) is wrong");
    if (b.GetSquare(1, 2) != WBISHOP)
        return mcet::genTestErr("GetSquare(1, 2) is wrong");
    if (b.GetSquare(1, 3) != WKNIGHT)
        return mcet::genTestErr("GetSquare(1, 3) is wrong");
    if (b.GetSquare(1, 4) != WROOK)
        return mcet::genTestErr("GetSquare(1, 4) is wrong");
    for (int i = 0; i < 5; i++)
    {
        if (b.GetSquare(2, i) != WPAWN)
            return mcet::genTestErr("GetSquare(2, " + std::to_string(i) + ") is wrong");
    }
    for (int i = 0; i < 5; i++)
    {
        if (b.GetSquare(3, i) != EMPTYSQ)
            return mcet::genTestErr("GetSquare(3, " + std::to_string(i) + ") is wrong");
        if (b.GetSquare(4, i) != EMPTYSQ)
            return mcet::genTestErr("GetSquare(4, " + std::to_string(i) + ") is wrong");
    }
    for (int i = 0; i < 5; i++)
    {
        if (b.GetSquare(5, i) != BPAWN)
            return mcet::genTestErr("GetSquare(5, " + std::to_string(i) + ") is wrong");
    }
    if (b.GetSquare(6, 0) != BROOK)
        return mcet::genTestErr("GetSquare(6, 0) is wrong");
    if (b.GetSquare(6, 1) != BKNIGHT)
        return mcet::genTestErr("GetSquare(6, 1) is wrong");
    if (b.GetSquare(6, 2) != BBISHOP)
        return mcet::genTestErr("GetSquare(6, 2) is wrong");
    if (b.GetSquare(6, 3) != BQUEEN)
        return mcet::genTestErr("GetSquare(6, 3) is wrong");
    if (b.GetSquare(6, 4) != BKING)
        return mcet::genTestErr("GetSquare(6, 4) is wrong");
    if (b.GetSquare(7, 3) != EMPTYSQ)
        return mcet::genTestErr("GetSquare(7, 3) is wrong");
    if (b.GetSquare(3, 5) != EMPTYSQ)
        return mcet::genTestErr("GetSquare(3, 5) is wrong");

    return mcet::NoErr;
}