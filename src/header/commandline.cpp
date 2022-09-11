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
            std::cout << r << " | ";
            for (File f = AFILE; f <= EFILE; f++)
            {
                std::cout << ConvPieceToFENChar(b->GetSquare(Square{f, r})) << " ";
            }
            std::cout << std::endl;
        }
    }
}
