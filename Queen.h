#ifndef QUEEN_H
#define QUEEN_H

#include"Piece.h"
#include"ChessBoard.h"

using namespace std;

class Queen: public Piece {
  
 private:
  
  /* Check move is valid for Bishop */
  bool validMoveBishop(int fileTo, int rankTo, ChessBoard &chessboard);

  /* Check move is valid for Rook */
  bool validMoveRook(int fileTo, int rankTo, ChessBoard &chessboard);

  /* Check valid move for Queen */
  bool validMove(int fileTo, int rankTo, ChessBoard &chessboard) override;

  /* Retrieve piece name */
  string getName() override;
};

#endif
