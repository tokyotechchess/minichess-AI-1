#include "commandline.h"

namespace minichess_AI
{
    MCError CommandLine::DisplayBoard(Board *b)
    {
        Piece Pieces[15] = {EMPTYSQ, WKING, WPAWN, WQUEEN, WROOK, WKNIGHT, WBISHOP, EMPTYSQ, EMPTYSQ, BKING, BPAWN, BQUEEN, BROOK, BKNIGHT, BBISHOP};
        std::cout << "--|-----------" << std::endl;
        std::cout << "  | a b c d e " << std::endl;
        std::cout << "--|-----------" << std::endl;
        for (Rank r = RANK6; r >= RANK1; r--)
        {
            std::cout << r << " | ";
            for (File f = AFILE; f <= EFILE; f++)
            {
                std::cout << ConvPieceToFENChar(Pieces[b->GetSquare(Square{f, r})]) << " ";
            }
            std::cout << std::endl;
        }
    }
}
