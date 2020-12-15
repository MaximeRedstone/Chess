#include"Knight.h"
#include"Piece.h"

using namespace std;

/* Check move is valid for Knight */
bool Knight::validMove(int fileTo, int rankTo, ChessBoard &chessboard) {

  int file = (*this).coordinates[0];
  int rank = (*this).coordinates[1];
  int colour = (*this).colour;
  
  bool answer = false;
  bool valid = false;

  // Knight bottom left options
  if ( (fileTo == file - 1 && rankTo == rank - 2) || (fileTo == file - 2 && rankTo == rank -1) ) {
    valid = validity(fileTo, rankTo, chessboard, colour);
    if (valid) {
      return true;
    }
  }

  // Knight top left options
  else if ((fileTo == file - 1 && rankTo == rank + 2) || (fileTo == file - 2 && rankTo == rank + 1)) {
    valid = validity(fileTo, rankTo, chessboard, colour);
    if (valid) {
      return true;
    }
  }

  // Knight top right options
  else if ( (fileTo == file + 1 && rankTo == rank + 2) || (fileTo == file + 2 && rankTo == rank + 1) ) {
    valid = validity(fileTo, rankTo, chessboard, colour);
    if (valid) {
      return true;
    }
  }

  // Knight bottom right options
  else if ( (fileTo == file + 1 && rankTo == rank - 2) || (fileTo == file + 2 && rankTo == rank -1) ) {
    valid = validity(fileTo, rankTo, chessboard, colour);
    if (valid) {
      return true;
    }
  }

  return answer;
}

/* Retrive piece name */
string Knight::getName() {
  return "Knight";
}
