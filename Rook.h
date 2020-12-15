#ifndef ROOK_H
#define ROOK_H

#include"Piece.h"
#include"ChessBoard.h"

using namespace std;

class Rook: public Piece {

  friend class ChessBoard;
  
 private:
  bool hasMoved;

  Rook(bool hasMoved) : hasMoved(hasMoved) {}

  /* Check valid move */
  bool validMove(int fileTo, int rankTo, ChessBoard &chessboard) override;

  /* Retrieve piece name */
  string getName() override;
  
  /* Update hasMoved */
  void updateMoved() override;

  /* Get moved status */
  bool getMovedStatus() override;
};

#endif
