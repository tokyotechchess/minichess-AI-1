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
MCError TestSetSquare();

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
    if ((e = TestSetSquare()) != mcet::NoErr)
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

// SetSquare
MCError TestSetSquare()
{
    Board b;
    b.SetSquare(AFILE, RANK1, WQUEEN);
    b.SetSquare(BFILE, RANK2, WKING);
    b.SetSquare(CFILE, RANK3, WPAWN);
    b.SetSquare(DFILE, RANK4, WBISHOP);
    b.SetSquare(EFILE, RANK5, WKNIGHT);
    b.SetSquare(AFILE, RANK6, WROOK);
    b.SetSquare(BFILE, RANK6, BQUEEN);
    b.SetSquare(BFILE, RANK5, BKING);
    b.SetSquare(CFILE, RANK4, BPAWN);
    b.SetSquare(DFILE, RANK3, BBISHOP);
    b.SetSquare(EFILE, RANK2, BKNIGHT);
    b.SetSquare(EFILE, RANK1, BROOK);
    b.SetSquare(CFILE, RANK1, EMPTYSQ);
    if (b.GetSquare(AFILE, RANK1) != WQUEEN)
        return mcet::genTestErr("SetSquare(AFILE, RANK1, WQUEEN) is wrong");
    if (b.GetSquare(BFILE, RANK2) != WKING)
        return mcet::genTestErr("SetSquare(BFILE, RANK2, WKING) is wrong");
    if (b.GetSquare(CFILE, RANK3) != WPAWN)
        return mcet::genTestErr("SetSquare(CFILE, RANK3, WPAWN) is wrong");
    if (b.GetSquare(DFILE, RANK4) != WBISHOP)
        return mcet::genTestErr("SetSquare(DFILE, RANK4, WBISHOP) is wrong");
    if (b.GetSquare(EFILE, RANK5) != WKNIGHT)
        return mcet::genTestErr("SetSquare(EFILE, RANK5, WKNIGHT) is wrong");
    if (b.GetSquare(AFILE, RANK6) != WROOK)
        return mcet::genTestErr("SetSquare(AFILE, RANK6, WROOK) is wrong");
    if (b.GetSquare(BFILE, RANK6) != BQUEEN)
        return mcet::genTestErr("SetSquare(AFILE, RANK6, WQUEEN) is wrong");
    if (b.GetSquare(BFILE, RANK5) != BKING)
        return mcet::genTestErr("SetSquare(BFILE, RANK5, WKING) is wrong");
    if (b.GetSquare(CFILE, RANK4) != BPAWN)
        return mcet::genTestErr("SetSquare(CFILE, RANK4, WPAWN) is wrong");
    if (b.GetSquare(DFILE, RANK3) != BBISHOP)
        return mcet::genTestErr("SetSquare(DFILE, RANK3, WBISHOP) is wrong");
    if (b.GetSquare(EFILE, RANK2) != BKNIGHT)
        return mcet::genTestErr("SetSquare(EFILE, RANK2, WKNIGHT) is wrong");
    if (b.GetSquare(EFILE, RANK1) != BROOK)
        return mcet::genTestErr("SetSquare(AFILE, RANK1, WROOK) is wrong");
    if (b.GetSquare(CFILE, RANK1) != EMPTYSQ)
        return mcet::genTestErr("SetSquare(CFILE, RANK1, EMPTYSQ) is wrong");

    return mcet::NoErr;
}