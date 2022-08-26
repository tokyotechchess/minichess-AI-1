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
MCError TestMove();

int main()
{
    MCError e;
    if ((e = TestGetSquare()) != mcet::NoErr)
    {
        std::cout << e.DisplayError() << std::endl;
    }
    if ((e = TestSetSquare()) != mcet::NoErr)
    {
        std::cout << e.DisplayError() << std::endl;
    }
    if ((e = TestSetBoardFEN()) != mcet::NoErr)
    {
        std::cout << e.DisplayError() << std::endl;
    }
    if ((e = TestIsChecked()) != mcet::NoErr)
    {
        std::cout << e.DisplayError() << std::endl;
    }
    if ((e = TestMove()) != mcet::NoErr)
    {
        std::cout << e.DisplayError() << std::endl;
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
        return mcet::genTestErr("Unexpected error is returned : " + e.DisplayError());
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
        return mcet::genTestErr("Unexpected error is returned : " + e.DisplayError());
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

    // pawn

    e = b.SetBoardFEN("4k/3r1/2Pp1/2K2/qB3/5 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != true || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in pawn test case 1");
    e = b.SetBoardFEN("4k/1NpP1/1pP2/pPnp1/P4/K4 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != true)
        return mcet::genTestErr("IsChecked is wrong in pawn test case 2");
    e = b.SetBoardFEN("5/2PpP/PPpKp/PkpPP/pPp2/5 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in pawn test case 3");
    e = b.SetBoardFEN("PPkPP/P1P1P/PPPPP/ppppp/p1p1p/ppKpp w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in pawn test case 4");
    e = b.SetBoardFEN("4P/3kr/1pp2/2K2/B1b2/4n w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != true || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in pawn test case 5");

    // random

    e = b.SetBoardFEN("rnbqk/2p1p/1p2P/1QPp1/P2P1/K1BNR b Kk -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != true)
        return mcet::genTestErr("IsChecked is wrong in random test case 1");
    e = b.SetBoardFEN("rnbqk/4p/1pp1P/1QPp1/P2P1/K1BNR w Kk -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in random test case 2");
    e = b.SetBoardFEN("1r1kb/Q3p/3pq/P1n2/KP3/N2R1 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != true || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in random test case 3");
    e = b.SetBoardFEN("5/2k1p/Kp1r1/BP2Q/2b2/2R2 w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in random test case 4");
    e = b.SetBoardFEN("3k1/2PPr/3K1/5/p2nb/1qqqq b - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != true)
        return mcet::genTestErr("IsChecked is wrong in random test case 5");
    e = b.SetBoardFEN("ppKpp/ppppp/b1r1q/Q1R1B/PPPPP/PPkPP w - -");
    if (e != mcet::NoErr)
        return e;
    if (b.IsChecked(cWhite) != false || b.IsChecked(cBlack) != false)
        return mcet::genTestErr("IsChecked is wrong in random test case 6");

    return mcet::NoErr;
}

MCError TestMove()
{
    Board b, origin;
    MCError e;

    // illegals

    // wrong piece

    // white

    e = b.SetBoardFEN("rnbqk/4p/5/5/5/2K2 w - -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(AFILE, RANK6, AFILE, RANK5);
    if (e != mcet::MoveWPErr)
        return mcet::genTestErr("Move returns wrong error in wrong piece illegal test case 1 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in wrong piece illegal test case 1");
    e = b.Move(BFILE, RANK6, DFILE, RANK5);
    if (e != mcet::MoveWPErr)
        return mcet::genTestErr("Move returns wrong error in wrong piece illegal test case 2 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in wrong piece illegal test case 2");
    e = b.Move(CFILE, RANK6, BFILE, RANK5);
    if (e != mcet::MoveWPErr)
        return mcet::genTestErr("Move returns wrong error in wrong piece illegal test case 3 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in wrong piece illegal test case 3");
    e = b.Move(DFILE, RANK6, DFILE, RANK5);
    if (e != mcet::MoveWPErr)
        return mcet::genTestErr("Move returns wrong error in wrong piece illegal test case 4 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in wrong piece illegal test case 4");
    e = b.Move(EFILE, RANK6, DFILE, RANK5);
    if (e != mcet::MoveWPErr)
        return mcet::genTestErr("Move returns wrong error in wrong piece illegal test case 5 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in wrong piece illegal test case 5");
    e = b.Move(EFILE, RANK5, EFILE, RANK4);
    if (e != mcet::MoveWPErr)
        return mcet::genTestErr("Move returns wrong error in wrong piece illegal test case 6 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in wrong piece illegal test case 6");
    e = b.Move(AFILE, RANK1, AFILE, RANK2);
    if (e != mcet::MoveWPErr)
        return mcet::genTestErr("Move returns wrong error in wrong piece illegal test case 7 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in wrong piece illegal test case 7");

    // black

    e = b.SetBoardFEN("2k2/5/5/5/P4/KQBNR b - -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(EFILE, RANK1, EFILE, RANK2);
    if (e != mcet::MoveWPErr)
        return mcet::genTestErr("Move returns wrong error in wrong piece illegal test case 8 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in wrong piece illegal test case 8");
    e = b.Move(DFILE, RANK1, BFILE, RANK2);
    if (e != mcet::MoveWPErr)
        return mcet::genTestErr("Move returns wrong error in wrong piece illegal test case 9 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in wrong piece illegal test case 9");
    e = b.Move(CFILE, RANK1, DFILE, RANK2);
    if (e != mcet::MoveWPErr)
        return mcet::genTestErr("Move returns wrong error in wrong piece illegal test case 10 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in wrong piece illegal test case 10");
    e = b.Move(BFILE, RANK1, BFILE, RANK2);
    if (e != mcet::MoveWPErr)
        return mcet::genTestErr("Move returns wrong error in wrong piece illegal test case 11 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in wrong piece illegal test case 11");
    e = b.Move(AFILE, RANK1, BFILE, RANK2);
    if (e != mcet::MoveWPErr)
        return mcet::genTestErr("Move returns wrong error in wrong piece illegal test case 12 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in wrong piece illegal test case 12");
    e = b.Move(AFILE, RANK2, AFILE, RANK3);
    if (e != mcet::MoveWPErr)
        return mcet::genTestErr("Move returns wrong error in wrong piece illegal test case 13 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in wrong piece illegal test case 13");
    e = b.Move(EFILE, RANK6, EFILE, RANK5);
    if (e != mcet::MoveWPErr)
        return mcet::genTestErr("Move returns wrong error in wrong piece illegal test case 14 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in wrong piece illegal test case 14");

    // checked after move

    // already checked but don't avoid

    // white

    e = b.SetBoardFEN("2k2/4q/5/5/2PP1/KQBNR w - -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(AFILE, RANK1, BFILE, RANK2);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in checked after move illegal test case 1 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in checked after move illegal test case 1");
    e = b.Move(BFILE, RANK1, AFILE, RANK2);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in checked after move illegal test case 2 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in checked after move illegal test case 2");
    e = b.Move(CFILE, RANK1, AFILE, RANK3);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in checked after move illegal test case 3 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in checked after move illegal test case 3");
    e = b.Move(DFILE, RANK1, EFILE, RANK3);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in checked after move illegal test case 4 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in checked after move illegal test case 4");
    e = b.Move(EFILE, RANK1, EFILE, RANK2);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in checked after move illegal test case 5 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in checked after move illegal test case 5");
    e = b.Move(CFILE, RANK2, CFILE, RANK4);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in checked after move illegal test case 6 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in checked after move illegal test case 6");
    e = b.Move(DFILE, RANK2, DFILE, RANK3);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in checked after move illegal test case 7 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in checked after move illegal test case 7");

    // black

    e = b.SetBoardFEN("rnbqk/1pp2/5/5/Q4/2K2 b - -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(EFILE, RANK6, DFILE, RANK5);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in checked after move illegal test case 8 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in checked after move illegal test case 8");
    e = b.Move(DFILE, RANK6, EFILE, RANK5);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in checked after move illegal test case 9 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in checked after move illegal test case 9");
    e = b.Move(CFILE, RANK6, EFILE, RANK4);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in checked after move illegal test case 10 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in checked after move illegal test case 10");
    e = b.Move(BFILE, RANK6, AFILE, RANK4);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in checked after move illegal test case 11 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in checked after move illegal test case 11");
    e = b.Move(AFILE, RANK6, AFILE, RANK5);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in checked after move illegal test case 12 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in checked after move illegal test case 12");
    e = b.Move(CFILE, RANK5, CFILE, RANK3);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in checked after move illegal test case 13 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in checked after move illegal test case 13");
    e = b.Move(BFILE, RANK5, BFILE, RANK4);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in checked after move illegal test case 14 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in checked after move illegal test case 14");

    // not checked before move

    // white

    e = b.SetBoardFEN("2k2/4q/5/5/1R3/K4 w - -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(BFILE, RANK2, CFILE, RANK2);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in checked after move illegal test case 15 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in checked after move illegal test case 15");

    // black

    e = b.SetBoardFEN("4k/3r1/5/5/Q4/2K2 b - -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(DFILE, RANK5, CFILE, RANK5);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in checked after move illegal test case 16 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in checked after move illegal test case 16");

    // pawn

    // white

    // e3 is q but it has meanings
    e = b.SetBoardFEN("rnbqk/p3p/1p3/2pPq/PPP1P/KQBNR w - e3");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(CFILE, RANK2, CFILE, RANK3);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white pawn illegal test case 1 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white pawn illegal test case 1");
    e = b.Move(CFILE, RANK2, CFILE, RANK4);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white pawn illegal test case 2 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white pawn illegal test case 2");
    e = b.Move(BFILE, RANK2, BFILE, RANK4);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white pawn illegal test case 3 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white pawn illegal test case 3");
    e = b.Move(DFILE, RANK3, DFILE, RANK5);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white pawn illegal test case 4 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white pawn illegal test case 4");
    e = b.Move(DFILE, RANK3, CFILE, RANK4);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white pawn illegal test case 5 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white pawn illegal test case 5");
    e = b.Move(DFILE, RANK3, EFILE, RANK4);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white pawn illegal test case 6 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white pawn illegal test case 6");
    e = b.Move(AFILE, RANK2, BFILE, RANK3);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white pawn illegal test case 7 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white pawn illegal test case 7");
    e = b.Move(AFILE, RANK2, BFILE, RANK5);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white pawn illegal test case 8 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white pawn illegal test case 8");
    e = b.Move(AFILE, RANK2, CFILE, RANK4);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white pawn illegal test case 9 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white pawn illegal test case 9");

    // black

    // a4 is Q but it has meanings
    e = b.SetBoardFEN("rnbqk/p1ppp/QpP2/3P1/P3P/KQBNR b - a4");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(CFILE, RANK5, CFILE, RANK4);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black pawn illegal test case 1 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black pawn illegal test case 1");
    e = b.Move(CFILE, RANK5, CFILE, RANK3);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black pawn illegal test case 2 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black pawn illegal test case 2");
    e = b.Move(DFILE, RANK5, DFILE, RANK3);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black pawn illegal test case 3 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black pawn illegal test case 3");
    e = b.Move(BFILE, RANK4, BFILE, RANK2);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black pawn illegal test case 4 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black pawn illegal test case 4");
    e = b.Move(BFILE, RANK4, CFILE, RANK3);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black pawn illegal test case 5 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black pawn illegal test case 5");
    e = b.Move(BFILE, RANK4, AFILE, RANK3);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black pawn illegal test case 6 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black pawn illegal test case 6");
    e = b.Move(EFILE, RANK5, DFILE, RANK4);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black pawn illegal test case 7 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black pawn illegal test case 7");
    e = b.Move(EFILE, RANK5, DFILE, RANK2);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black pawn illegal test case 8 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black pawn illegal test case 8");
    e = b.Move(EFILE, RANK5, CFILE, RANK3);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black pawn illegal test case 9 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black pawn illegal test case 9");

    // king

    // white

    e = b.SetBoardFEN("2k2/5/5/5/5/K2NR w K -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(AFILE, RANK1, CFILE, RANK1);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white king illegal test case 1 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white king illegal test case 1");

    e = b.SetBoardFEN("2k2/r4/5/5/5/K3R w K -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(AFILE, RANK1, CFILE, RANK1);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white king illegal test case 2 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white king illegal test case 2");

    e = b.SetBoardFEN("2k2/1r3/5/5/5/K3R w K -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(AFILE, RANK1, CFILE, RANK1);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white king illegal test case 3 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white king illegal test case 3");

    e = b.SetBoardFEN("2k2/2r2/5/5/5/K3R w K -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(AFILE, RANK1, CFILE, RANK1);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white king illegal test case 4 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white king illegal test case 4");

    e = b.SetBoardFEN("2k2/5/5/5/5/K3R w - -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(AFILE, RANK1, CFILE, RANK1);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white king illegal test case 5 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white king illegal test case 5");

    e = b.SetBoardFEN("2k2/5/5/2K2/5/5 w - -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(CFILE, RANK3, EFILE, RANK5);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white king illegal test case 6 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white king illegal test case 6");

    e = b.SetBoardFEN("2k2/5/5/2K2/5/5 w - -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(CFILE, RANK3, AFILE, RANK3);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white king illegal test case 7 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white king illegal test case 7");

    e = b.SetBoardFEN("2k2/5/5/2K2/5/5 w - -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(CFILE, RANK3, CFILE, RANK1);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white king illegal test case 8 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white king illegal test case 8");

    // black

    e = b.SetBoardFEN("rn2k/5/5/5/5/2K2 b k -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(EFILE, RANK6, CFILE, RANK6);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black king illegal test case 1 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black king illegal test case 1");

    e = b.SetBoardFEN("r3k/5/5/5/4R/2K2 b k -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(EFILE, RANK6, CFILE, RANK6);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black king illegal test case 2 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black king illegal test case 2");

    e = b.SetBoardFEN("r3k/5/5/5/3R1/2K2 b k -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(EFILE, RANK6, CFILE, RANK6);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black king illegal test case 3 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black king illegal test case 3");

    e = b.SetBoardFEN("r3k/5/5/5/2R2/2K2 b k -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(EFILE, RANK6, CFILE, RANK6);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black king illegal test case 4 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black king illegal test case 4");

    e = b.SetBoardFEN("r3k/5/5/5/5/2K2 b - -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(EFILE, RANK6, CFILE, RANK6);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black king illegal test case 5 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black king illegal test case 5");

    e = b.SetBoardFEN("5/5/2k2/5/5/2K2 b - -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(CFILE, RANK4, AFILE, RANK2);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black king illegal test case 6 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black king illegal test case 6");

    e = b.SetBoardFEN("5/5/2k2/5/5/2K2 b - -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(CFILE, RANK4, EFILE, RANK4);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black king illegal test case 7 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black king illegal test case 7");

    e = b.SetBoardFEN("5/5/2k2/5/5/2K2 b - -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(CFILE, RANK4, CFILE, RANK6);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black king illegal test case 8 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black king illegal test case 8");

    // queen

    // white

    e = b.SetBoardFEN("4k/5/3P1/1pQ2/5/K4 w - -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(CFILE, RANK3, AFILE, RANK3);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white queen illegal test case 1 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white queen illegal test case 1");
    e = b.Move(CFILE, RANK3, EFILE, RANK5);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white queen illegal test case 2 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white queen illegal test case 2");
    e = b.Move(CFILE, RANK3, AFILE, RANK6);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white queen illegal test case 3 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white queen illegal test case 3");

    // black

    e = b.SetBoardFEN("4k/5/2qP1/1p3/5/K4 b - -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(CFILE, RANK4, EFILE, RANK4);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black queen illegal test case 1 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black queen illegal test case 1");
    e = b.Move(CFILE, RANK4, AFILE, RANK2);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black queen illegal test case 2 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black queen illegal test case 2");
    e = b.Move(CFILE, RANK4, EFILE, RANK1);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black queen illegal test case 3 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black queen illegal test case 3");

    // rook

    // white

    e = b.SetBoardFEN("4k/5/5/1pR2/2P2/K4 w - -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(CFILE, RANK3, AFILE, RANK3);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white rook illegal test case 1 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white rook illegal test case 1");
    e = b.Move(CFILE, RANK3, CFILE, RANK1);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white rook illegal test case 2 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white rook illegal test case 2");
    e = b.Move(CFILE, RANK3, EFILE, RANK1);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in white rook illegal test case 3 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in white rook illegal test case 3");

    // black

    e = b.SetBoardFEN("4k/2p2/2rP1/5/5/K4 b - -");
    if (e != mcet::NoErr)
        return e;

    origin = b;

    e = b.Move(CFILE, RANK4, EFILE, RANK4);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black rook illegal test case 1 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black rook illegal test case 1");
    e = b.Move(CFILE, RANK4, CFILE, RANK6);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black rook illegal test case 2 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black rook illegal test case 2");
    e = b.Move(CFILE, RANK4, AFILE, RANK6);
    if (e != mcet::MoveErr)
        return mcet::genTestErr("Move returns wrong error in black rook illegal test case 3 : " + e.DisplayError());
    if (origin != b)
        return mcet::genTestErr("Move is wrong in black rook illegal test case 3");

    return mcet::NoErr;
}