#include"Queen.h"
#include"Piece.h"

using namespace std;

/* Check move is valid for Rook */
bool Queen::validMoveRook(int fileTo, int rankTo, ChessBoard &chessboard) {
  
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

/* Check move is valid for Bishop */
bool Queen::validMoveBishop(int fileTo, int rankTo, ChessBoard &chessboard) {

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

/* Check move is valid for Queen */
bool Queen::validMove(int fileTo, int rankTo, ChessBoard &chessboard) {

  bool answer = false;
  
  // Move is valid if condition for bishop or rook is valid
  if (validMoveRook(fileTo, rankTo, chessboard) || validMoveBishop(fileTo, rankTo, chessboard)) {
    return true;
  }
  
  return answer;
}

/* Retrieve piece name */
string Queen::getName() {
  return "Queen";
}
