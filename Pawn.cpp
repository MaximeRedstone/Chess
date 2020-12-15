#include "Pawn.h"

using namespace std;

const int BLACK = 0;
const int WHITE = 1;
const int BLACK_START = 55;
const int WHITE_START = 50;
const int MOVE_FORWARD_TWO = 2;

/* Check move is valid for Pawn */
bool Pawn::validMove(int fileTo, int rankTo, ChessBoard &chessboard) {

  int file = (*this).coordinates[0];
  int rank = (*this).coordinates[1];

  bool answer = false;
  Piece* piece = chessboard.retrievePiece(fileTo, rankTo, chessboard);

  // For each colour - two cases 
  if (this->colour == BLACK) {
    
    // Pawn's first move
    if (rank == BLACK_START) {
      // Moves one or two forward
      if ( (fileTo == file && (rankTo == rank - 1 || rankTo == rank - 2) && piece == nullptr) ) {
	int until = MOVE_FORWARD_TWO;
	vector<int> pair = {0, -1};
	if (!chessboard.checkBetween(file, rank, until, pair, chessboard)) {
	  return true;
	}
      }
      // Moves diagonally if can take a piece
      else if ( (fileTo == file - 1 && rankTo == rank - 1 && piece != nullptr && (*piece).colour == WHITE) || (fileTo == file + 1 && rankTo == rank - 1 && piece != nullptr && (*piece).colour == WHITE)) {
	return true;
      }
    }
    
    // Pawn's subsequent move
    else {
      // Moves one forward or diagonally if can take a piece
      if ( (fileTo == file && rankTo == rank - 1 && piece == nullptr)  || (fileTo == file - 1 && rankTo == rank - 1 && piece != nullptr && (*piece).colour == WHITE) || (fileTo == file + 1 && rankTo == rank - 1 && piece != nullptr && (*piece).colour == WHITE) ) {
	  return true;
      }
    }
  }
  
  else if (this->colour == WHITE) {

    // Pawn's first move
    if (rank == WHITE_START) {
      // Moves one or two forward
      if ( (fileTo == file && (rankTo == rank + 1 || rankTo == rank + 2) && piece == nullptr) ) { 
	int until = MOVE_FORWARD_TWO;
	vector<int> pair = {0, 1};
	if (!chessboard.checkBetween(file, rank, until, pair, chessboard)) {
	  return true;
	}
      }
      // Moves diagonally if can take a piece
      else if ( (fileTo == file - 1 && rankTo == rank + 1 && piece != nullptr && (*piece).colour == BLACK) || (fileTo == file + 1 && rankTo == rank + 1 && piece != nullptr && (*piece).colour == BLACK)) {
	return true;
      }
    }
    // Pawn's subsequent move
    else {
      // Moves one forward or diagonally if can take a piece
      if ( (fileTo == file && rankTo == rank + 1 && piece == nullptr)  || (fileTo == file - 1 && rankTo == rank + 1 && piece != nullptr && (*piece).colour == BLACK) || (fileTo == file + 1 && rankTo == rank + 1 && piece != nullptr && (*piece).colour == BLACK) ) {
	return true;
      }
    }
  }
  
  return answer;
}

/* Retrieve piece name */
string Pawn::getName() {
  return "Pawn";
}
