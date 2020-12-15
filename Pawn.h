#ifndef PAWN_H
#define PAWN_H

#include"Piece.h"
#include"ChessBoard.h"

using namespace std;

class Pawn: public Piece {

 private:
  /* Check valid move */
  bool validMove(int fileTo, int rankTo, ChessBoard &chessboard) override;

  /* Retrieve piece name */
  string getName() override;
};

#endif
