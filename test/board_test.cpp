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

    if (b.GetSquare(AFILE, RANK1) != WKING)
        return mcet::genTestErr("GetSquare(AFILE, RANK1) is wrong");
    if (b.GetSquare(BFILE, RANK1) != WQUEEN)
        return mcet::genTestErr("GetSquare(BFILE, RANK1) is wrong");
    if (b.GetSquare(CFILE, RANK1) != WBISHOP)
        return mcet::genTestErr("GetSquare(CFILE, RANK1) is wrong");
    if (b.GetSquare(DFILE, RANK1) != WKNIGHT)
        return mcet::genTestErr("GetSquare(DFILE, RANK1) is wrong");
    if (b.GetSquare(EFILE, RANK1) != WROOK)
        return mcet::genTestErr("GetSquare(EFILE, RANK1) is wrong");
    for (File i = AFILE; i < EFILE; i++)
    {
        if (b.GetSquare(i, RANK2) != WPAWN)
            return mcet::genTestErr("GetSquare(" + std::to_string(static_cast<int>(i)) + ", RANK2) is wrong");
    }
    for (File i = AFILE; i < EFILE; i++)
    {
        if (b.GetSquare(i, RANK3) != EMPTYSQ)
            return mcet::genTestErr("GetSquare(" + std::to_string(static_cast<int>(i)) + ", RANK3) is wrong");
        if (b.GetSquare(i, RANK4) != EMPTYSQ)
            return mcet::genTestErr("GetSquare(" + std::to_string(static_cast<int>(i)) + ", RANK4) is wrong");
    }
    for (File i = AFILE; i < EFILE; i++)
    {
        if (b.GetSquare(i, RANK5) != BPAWN)
            return mcet::genTestErr("GetSquare(" + std::to_string(static_cast<int>(i)) + ", RANK5) is wrong");
    }
    if (b.GetSquare(AFILE, RANK6) != BROOK)
        return mcet::genTestErr("GetSquare(6, 0) is wrong");
    if (b.GetSquare(BFILE, RANK6) != BKNIGHT)
        return mcet::genTestErr("GetSquare(6, 1) is wrong");
    if (b.GetSquare(CFILE, RANK6) != BBISHOP)
        return mcet::genTestErr("GetSquare(6, 2) is wrong");
    if (b.GetSquare(DFILE, RANK6) != BQUEEN)
        return mcet::genTestErr("GetSquare(6, 3) is wrong");
    if (b.GetSquare(EFILE, RANK6) != BKING)
        return mcet::genTestErr("GetSquare(6, 4) is wrong");

    return mcet::NoErr;
}