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
MCError TestSetBoardFEN();
MCError TestIsChecked();

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
    if ((e = TestSetBoardFEN()) != mcet::NoErr)
    {
        if (e == mcet::TestErr)
        {
            std::cout << "Test Error : " + e.GetMessage() << std::endl;
        }
    }
    if ((e = TestIsChecked()) != mcet::NoErr)
    {
        if (e == mcet::TestErr)
        {
            std::cout << "Test Error : " + e.GetMessage() << std::endl;
        }
        else if (e == mcet::FENErr)
        {
            std::cout << "FEN Error : " + e.GetMessage() << std::endl;
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

MCError TestSetBoardFEN()
{
    Board b;
    MCError e;

    // wrong FEN test

    // wrong piece placement (too many piece)
    if (b.SetBoardFEN("2bk1/pp1pp/n3pq/rRPPP/P4/KQBN1 w Kk d3") != mcet::FENErr)
    {
        return mcet::genTestErr("Wrong piece placement error due to too many piece doesn't work in SetBoardFEN");
    }
    // wrong piece placement (too many enpty squares)
    if (b.SetBoardFEN("2bk1/pp1pp/n2p2/rRPPP/P4/KQBN1 w Kk d3") != mcet::FENErr)
    {
        return mcet::genTestErr("Wrong piece placement error due to too many enpty squares doesn't work in SetBoardFEN");
    }
    // wrong piece placement (too many ranks)
    if (b.SetBoardFEN("2bk1/pp1pp/n2pq/rRPPP/P4/KQBN1/5 w Kk d3") != mcet::FENErr)
    {
        return mcet::genTestErr("Wrong piece placement error due to too many ranks doesn't work in SetBoardFEN");
    }
    // wrong piece placement (wrong character)
    if (b.SetBoardFEN("2bk1/pp1pp/n2vq/rRPPP/P4/KQBN1 w Kk d3") != mcet::FENErr)
    {
        return mcet::genTestErr("Wrong piece placement error due to wrong character doesn't work in SetBoardFEN");
    }
    // wrong color setting (wrong character)
    if (b.SetBoardFEN("2bk1/pp1pp/n2pq/rRPPP/P4/KQBN1 v Kk d3") != mcet::FENErr)
    {
        return mcet::genTestErr("Wrong color setting error due to wrong character doesn't work in SetBoardFEN");
    }
    // wrong color setting (too many color setting)
    if (b.SetBoardFEN("2bk1/pp1pp/n2pq/rRPPP/P4/KQBN1 wb Kk d3") != mcet::FENErr)
    {
        return mcet::genTestErr("Wrong color setting error due to too many color setting doesn't work in SetBoardFEN");
    }
    // wrong castling setting (wrong character)
    if (b.SetBoardFEN("2bk1/pp1pp/n2pq/rRPPP/P4/KQBN1 w Kc d3") != mcet::FENErr)
    {
        return mcet::genTestErr("Wrong castling setting error due to wrong character doesn't work in SetBoardFEN");
    }
    // wrong castling setting (overused characters)
    if (b.SetBoardFEN("2bk1/pp1pp/n2pq/rRPPP/P4/KQBN1 w KK d3") != mcet::FENErr)
    {
        return mcet::genTestErr("Wrong castling setting error due to overuse of characters doesn't work in SetBoardFEN");
    }
    // wrong enpassant setting (wrong character)
    if (b.SetBoardFEN("2bk1/pp1pp/n2pq/rRPPP/P4/KQBN1 w Kk f3") != mcet::FENErr)
    {
        return mcet::genTestErr("Wrong enpassant setting error due to wrong character doesn't work in SetBoardFEN");
    }

    // no error test

    int *files;
    files = new int[5];

    // first

    if ((e = b.SetBoardFEN("2bk1/pp1pp/n2pq/rRPPP/P4/KQBN1 w Kk d3")) != mcet::NoErr)
    {
        return mcet::genTestErr("Unexpected error is returned : " + e.GetMessage());
    }

    files = b.GetBoard();
    if (
        (files[AFILE] != BPAWN * RANK5W + BKNIGHT * RANK4W + BROOK * RANK3W + WPAWN * RANK2W + WKING * RANK1W) ||
        (files[BFILE] != BPAWN * RANK5W + WROOK * RANK3W + WQUEEN * RANK1W) ||
        (files[CFILE] != BBISHOP * RANK6W + WPAWN * RANK3W + WBISHOP * RANK1W) ||
        (files[DFILE] != BKING * RANK6W + BPAWN * RANK5W + BPAWN * RANK4W + WPAWN * RANK3W + WKNIGHT * RANK1W) ||
        (files[EFILE] != BPAWN * RANK5W + BQUEEN * RANK4W + WPAWN * RANK3W))
    {
        return mcet::genTestErr("In SetBoardFEN, piece placement is wrong");
    }
    if (b.GetTurn() != cWhite)
    {
        return mcet::genTestErr("In SetBoardFEN, color setting is wrong");
    }
    if (b.GetCastlingPossibility(cWhite) != true || b.GetCastlingPossibility(cBlack) != true)
    {
        return mcet::genTestErr("In SetBoardFEN, castling possibility setting is wrong");
    }
    if (b.GetEnpassantAblePawnFile() != DFILE)
    {
        return mcet::genTestErr("In SetBoardFEN, enpassant setting is wrong");
    }

    // second

    if ((e = b.SetBoardFEN("3nk/1p1bq/pPpNr/B1P2/PKQ1p/4R b - -")) != mcet::NoErr)
    {
        return mcet::genTestErr("Unexpected error is returned : " + e.GetMessage());
    }

    files = b.GetBoard();
    if (
        (files[AFILE] != BPAWN * RANK4W + WBISHOP * RANK3W + WPAWN * RANK2W) ||
        (files[BFILE] != BPAWN * RANK5W + WPAWN * RANK4W + WKING * RANK2W) ||
        (files[CFILE] != BPAWN * RANK4W + WPAWN * RANK3W + WQUEEN * RANK2W) ||
        (files[DFILE] != BKNIGHT * RANK6W + BBISHOP * RANK5W + WKNIGHT * RANK4W) ||
        (files[EFILE] != BKING * RANK6W + BQUEEN * RANK5W + BROOK * RANK4W + BPAWN * RANK2W + WROOK * RANK1W))
    {
        return mcet::genTestErr("In SetBoardFEN, piece placement is wrong");
    }
    if (b.GetTurn() != cBlack)
    {
        return mcet::genTestErr("In SetBoardFEN, color setting is wrong");
    }
    if (b.GetCastlingPossibility(cWhite) != false || b.GetCastlingPossibility(cBlack) != false)
    {
        return mcet::genTestErr("In SetBoardFEN, castling possibility setting is wrong");
    }
    if (b.GetEnpassantAblePawnFile() != FILEERR)
    {
        return mcet::genTestErr("In SetBoardFEN, enpassant setting is wrong");
    }

    return mcet::NoErr;
}

MCError TestIsChecked()
{
    Board b;
    MCError e;

    // knight

    e = b.SetBoardFEN("3nk/1p1bq/pPpNr/B1P2/PKQ1p/4R w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != true)
        return mcet::genTestErr("IsChecked is wrong in knight test case 1");
    e = b.SetBoardFEN("3K1/1kP2/2n1q/1p3/1P3/5 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != true || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in knight test case 2");
    e = b.SetBoardFEN("2N2/1nNkN/n1nNN/1NnN1/nNKnn/1n1n1 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in knight test case 3");
    e = b.SetBoardFEN("2k1N/p3r/1nP1p/pP2Q/P1K2/5 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != true || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in knight test case 4");
    e = b.SetBoardFEN("5/5/1q3/2kp1/N1bPp/K3R w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != true)
        return mcet::genTestErr("IsChecked is wrong in knight test case 5");

    // bishop

    e = b.SetBoardFEN("1n3/k1p2/2Pp1/1K1Pp/3BP/4R w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != true)
        return mcet::genTestErr("IsChecked is wrong in bishop test case 1");
    e = b.SetBoardFEN("3r1/1n3/k2Pb/p1P1P/2K2/3R1 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != true || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in bishop test case 2");
    e = b.SetBoardFEN("5/P4/2k1b/qN1n1/2KB1/5 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in bishop test case 3");
    e = b.SetBoardFEN("5/q4/2K2/5/bRpk1/5 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != true || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in bishop test case 4");
    e = b.SetBoardFEN("5/2k2/1nr1b/B2p1/3Q1/1KR2 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in bishop test case 5");

    // king

    e = b.SetBoardFEN("5/5/1Kk2/5/5/5 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != true || b.IsChecked(cBlack) != true)
        return mcet::genTestErr("IsChecked is wrong in king test case 1");
    e = b.SetBoardFEN("k4/1K3/5/5/5/5 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != true || b.IsChecked(cBlack) != true)
        return mcet::genTestErr("IsChecked is wrong in king test case 2");
    e = b.SetBoardFEN("5/5/5/5/4K/4k w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != true || b.IsChecked(cBlack) != true)
        return mcet::genTestErr("IsChecked is wrong in king test case 3");
    e = b.SetBoardFEN("5/5/5/3K1/1k3/5 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in king test case 4");
    e = b.SetBoardFEN("5/3K1/5/3k1/5/5 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in king test case 5");

    // queen

    e = b.SetBoardFEN("r3k/1ppbq/p3p/1P3/PKPP1/1Q2R w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != true || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in queen test case 1");
    e = b.SetBoardFEN("r1b2/1k3/5/1pKQ1/pB3/5 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != true)
        return mcet::genTestErr("IsChecked is wrong in queen test case 2");
    e = b.SetBoardFEN("5/2k2/5/2K1q/p2r1/2B2 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != true || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in queen test case 3");
    e = b.SetBoardFEN("3Q1/q3p/1n1kP/2N2/3K1/5 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != true)
        return mcet::genTestErr("IsChecked is wrong in queen test case 4");
    e = b.SetBoardFEN("3K1/3Q1/2P2/1k3/4n/3q1 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in queen test case 5");

    // rook

    e = b.SetBoardFEN("3k1/1R3/2n2/2N2/5/1K1r1 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != true || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in rook test case 1");
    e = b.SetBoardFEN("2b2/2k2/1r1p1/1p1K1/1P2N/2R2 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != true)
        return mcet::genTestErr("IsChecked is wrong in rook test case 2");
    e = b.SetBoardFEN("1N1B1/5/3P1/1krR1/5/2K2 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != true || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in rook test case 3");
    e = b.SetBoardFEN("3R1/5/3K1/5/3k1/3r1 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in rook test case 4");
    e = b.SetBoardFEN("2n2/1R2k/4r/BpK2/2PR1/4q w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != true)
        return mcet::genTestErr("IsChecked is wrong in rook test case 5");

    return mcet::NoErr;
}