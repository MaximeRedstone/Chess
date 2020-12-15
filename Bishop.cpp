#include"Bishop.h"
#include"Piece.h"

using namespace std;

/* Check move is valid for Bishop */
bool Bishop::validMove(int fileTo, int rankTo, ChessBoard &chessboard) {

  int file = (*this).coordinates[0];
  int rank = (*this).coordinates[1];

  bool answer = false;
  vector<int> pair;

  // Moves diagonally
  if (abs(file - fileTo) == abs(rank - rankTo)) {
    // Top Right
    if ( fileTo > file && rankTo > rank) {
      pair = {1, 1};
      int until = rankTo - rank;
      if (!chessboard.checkBetween(file, rank, until, pair, chessboard)) {
	return true;
      }
    }
    // Top Left
    else if ( fileTo < file && rankTo > rank) {
      pair = {-1, 1};
      int until = rankTo - rank;
      if (!chessboard.checkBetween(file, rank, until, pair, chessboard)) {
	return true;
      }
    }
    // Bottom Left
    else if (fileTo < file && rankTo < rank) {
      pair = {-1, -1};
      int until = rank - rankTo;
      if (!chessboard.checkBetween(file, rank, until, pair, chessboard)) {
	return true;
      }
    }
    // Bottom Right
    else if (fileTo > file && rankTo < rank) {
      pair = {1, -1};
      int until = rank - rankTo;
      if (!chessboard.checkBetween(file, rank, until, pair, chessboard)) {
	return true;
      }
    }
  }
  
  return answer;
}

/* Retrieve piece name */
string Bishop::getName() {
  return "Bishop";
}
