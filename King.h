#ifndef KING_H
#define KING_H

#include"Piece.h"

using namespace std;

class King: public Piece {

  friend class ChessBoard;
  
 private:
  bool hasMoved;
  bool inCheck;
  
 King(bool hasMoved, bool inCheck) : hasMoved(hasMoved), inCheck(inCheck) {}
  
  /* Check valid move (1 step in any direction) */
  bool validMove(int fileTo, int rankTo, ChessBoard &chessboard) override;

  /* Retrieve piece name */
  string getName() override;

  /* Update hasMoved */
  void updateMoved() override;

  /* Update check */
  void setCheck() override;
  void unsetCheck() override;
  
  /* Get Move status */
  bool getMovedStatus() override;

  /* Get check status */
  bool getCheckStatus() override;
};

#endif
