#include"King.h"
#include"Piece.h"

using namespace std;

/* Check move is valid for King */
bool King::validMove(int fileTo, int rankTo, ChessBoard &chessboard) {

  int file = (*this).coordinates[0];
  int rank = (*this).coordinates[1];
  int colour = (*this).colour;
  
  bool answer = false;
  bool valid = false;
  
    // King's left column options
  if ( (fileTo == file - 1 && rankTo == rank - 1) || (fileTo == file - 1 && rankTo == rank) || (fileTo == file - 1 && rankTo == rank + 1) ){

    // are empty or can be eaten
    valid = validity(fileTo, rankTo, chessboard, colour);
    if (valid) {
      return true;
    }
  }

  // King's own column options
  else if ( (fileTo == file && rankTo == rank - 1) || (fileTo == file && rankTo == rank + 1) ) {

    // are empty or can be eaten
    valid = validity(fileTo, rankTo, chessboard, colour);
    if (valid) {
      return true;
    }
  }

  // King's right column options
  else if ( (fileTo == file + 1 && rankTo == rank - 1) || (fileTo == file + 1 && rankTo == rank) || (fileTo == file + 1 && rankTo == rank + 1) ) {
    
    // are empty or can be eaten
    valid = validity(fileTo, rankTo, chessboard, colour);
    if (valid) {
      return true;
    }
  }

  return answer;
}

/* Retrieve piece name */
string King::getName() {
  return "King";
}

/* Update hasMoved */
void King::updateMoved() {
  this->hasMoved = true;
}

/* Get move status */
bool King::getMovedStatus() {
  return this->hasMoved;
}

/* Update check status */
void King::setCheck() {
    this->inCheck = true;
}

void King::unsetCheck() {
  this->inCheck = false;
}

/* Get check status */
bool King::getCheckStatus() {
  return this->inCheck;
}
