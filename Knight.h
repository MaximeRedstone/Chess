#ifndef KNIGHT_H
#define KNIGHT_H

#include"Piece.h"

using namespace std;

class Knight: public Piece {

 private:
  /* Check valid move (L-shape) */
  bool validMove(int fileTo, int rankTo, ChessBoard &chessboard) override;

  /* Retrieve piece name*/
  string getName() override;
};

#endif
