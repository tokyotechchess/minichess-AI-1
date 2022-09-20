#include "commandline.h"

namespace minichess_AI
{
    MCError CommandLine::DisplayBoard(Board *b)
    {
        std::cout << "--|-----------" << std::endl;
        std::cout << "  | a b c d e " << std::endl;
        std::cout << "--|-----------" << std::endl;
        for (Rank r = RANK6; r >= RANK1; r--)
        {
            std::cout << r + 1 << " | ";
            for (File f = AFILE; f <= EFILE; f++)
            {
                std::cout << ConvPieceToFENChar(b->GetSquare(Square{f, r})) << " ";
            }
            std::cout << std::endl;
        }

        MCCSetting setting;
        if (setting.displayCastlingPossibility == true)
        {
            std::cout << "CastlingPossibility" << std::endl;
            std::cout << "  White  ";
            (b->GetCastlingPossibility(cWhite) == true) ? std::cout << "Yes" << std::endl : std::cout << "No" << std::endl;
            std::cout << "  Black  ";
            (b->GetCastlingPossibility(cBlack) == true) ? std::cout << "Yes" << std::endl : std::cout << "No" << std::endl;
        }
        if (setting.displayEnpassantAbleFile == true)
        {
            std::cout << "EnpassantAbleFile" << std::endl;
            if (b->GetEnpassantAblePawnFile() == FILEERR)
            {
                std::cout << "  -" << std::endl;
            }
            else
            {
                std::cout << "  " << char(b->GetEnpassantAblePawnFile() + 'a') << std::endl;
            }
        }
    }
}
