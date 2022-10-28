/*
minichess AI Generation 1
This is a intelligence for minichess played in Kodaisai.

minichess
--|-----------
  | a b c d e
--|-----------
6 | r n b q k
5 | p p p p p
4 |
3 |
2 | P P P P P
1 | K Q B N R

about FEN
- The expressions are almost same.
- Differences:
  - No queen side castling
  - No fifty move rule
*/

#include "collection.h"
#include <string>

using namespace minichess_AI;
using std::string;

int main()
{
  Board b, copy;
  minichessAI AI;
  CommandLine cmd;
  string in;
  Square bf, bt, mvf, mvt;
  Piece bp, pr;
  MCError e;

  cmd.ChangeSetting(MCCSetting{true, true, true});

  while (!b.IsMated())
  {
    copy = b;
    cmd.DisplayBoard(&b);
    std::cout << "evaluation : " << AI.evaluate(b) << std::endl;
    std::cout << "user > ";
    getline(std::cin, in);

    if (in == "mb")
    {
      b = copy;
    }
    else if (in == "bm")
    {
      AI.GetBestMove(&bf, &bt, &bp);
      b.MoveForce(bf, bt, bp);
    }
    else
    {
      mvf = Square{File(in[0] - 'a'), Rank(in[1] - '1')};
      mvt = Square{File(in[2] - 'a'), Rank(in[3] - '1')};
      pr = ConvFENCharToPiece(in[4]);
      e = b.Move(mvf, mvt, pr);
      if (e != mcet::NoErr)
      {
        std::cout << e.DisplayError() << std::endl;
      }
    }
  }
}