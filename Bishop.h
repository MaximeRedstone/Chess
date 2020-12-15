#ifndef BISHOP_H
#define BISHOP_H

#include"Piece.h"
#include"ChessBoard.h"

using namespace std;

class Bishop: public Piece {
  
 private:
  
  /* Check valid move */
  bool validMove(int fileTo, int rankTo, ChessBoard &chessboard) override;

  /* Retrieve piece name */
  string getName() override;
};

#endif
