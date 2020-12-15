#include"Rook.h"
#include"Piece.h"

using namespace std;

/* Check move is valid for Rook */
bool Rook::validMove(int fileTo, int rankTo, ChessBoard &chessboard) {
  
  int file = (*this).coordinates[0];
  int rank = (*this).coordinates[1];
  
  bool answer = false;
  vector<int> pair;

  // Moves vertically - check nothing in between source/destination
  if ( (fileTo == file && rankTo != rank) ) {
    // Upwards
    if (rankTo > rank) {
      pair = {0 , 1};
      int until = rankTo - rank;
      if (!chessboard.checkBetween(file, rank, until, pair, chessboard)) {
	return true;
      }
    }
    // Downwards
    else if (rankTo < rank) {
      pair = {0, -1};
      int until = rank - rankTo;
      if (!chessboard.checkBetween(file, rank, until, pair, chessboard)) {
	return true;
      }
    }
  }
  // Moves horizontally - check nothing in between source/destination
  else if ( (rankTo == rank && fileTo != file) ) {
    // Rightwards
    if (fileTo > file) {
      pair = {1, 0};
      int until = fileTo - file;
      if (!chessboard.checkBetween(file, rank, until, pair, chessboard)) {
	return true;
      }
    }
    // Leftwards
    else if (fileTo < file) {
      pair = {-1, 0};
      int until = file - fileTo;
      if (!chessboard.checkBetween(file, rank, until, pair, chessboard)) {
	return true;
      }
    }
  }
  
  return answer;
}

/* Retrieve piece name */
string Rook::getName() {
  return "Rook";
}

void Rook::updateMoved() {
  this->hasMoved = true;
}

/* Get move status */
bool Rook::getMovedStatus() {
  return this->hasMoved;
}
