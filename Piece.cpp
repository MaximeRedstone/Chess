#include "Piece.h"
#include "ChessBoard.h"

/* Check destination is valid */
bool Piece::validity(int fileTo, int rankTo, ChessBoard &chessboard, int colour) {

  vector<int> coordinates = {fileTo, rankTo};
  if (checkPositionEmpty(coordinates, chessboard, colour)) {
    return true;
  }

  return false;
}

/* Check position is empty or occupied by other player's colour */
bool Piece::checkPositionEmpty(vector<int> coordinates, ChessBoard &chessboard, int colour) {

  bool move = false;
  
  Piece* pieceI = (chessboard).retrievePiece(coordinates.at(0), coordinates.at(1), chessboard);
  if (pieceI != nullptr) {
    move = false;
    if ( (*pieceI).colour != colour )  {
      move = true;
    }
  }
  else {
    move = true;
  }

  return move;

}

/* Get move status */
bool Piece::getMovedStatus() {
  return false;
}

/* Get check status */
bool Piece::getCheckStatus() {
  return false;
}

/* Overall Validity of move is confirmed if this does not yield the player in check */
bool Piece::pieceValidMove(int fileTo, int rankTo, ChessBoard &chessboard, Piece* pieceToEat, Piece* pieceToMove) {

  bool valid = false;

  int fileFrom = (*pieceToMove).coordinates.at(0);
  int rankFrom = (*pieceToMove).coordinates.at(1);

  if (validMove(fileTo, rankTo, chessboard)) {

    // If destination is a piece of different colour - simulate eating it
    if (pieceToEat != nullptr) {
      if ((*pieceToMove).colour != (*pieceToEat).colour) {
	chessboard.eat(pieceToMove, pieceToEat, chessboard);
	
	Piece* king = chessboard.retrieveKing((*pieceToMove).colour, chessboard);

	// Check this move doesn't yield own king in check
	if (chessboard.checkForCheck((*king).coordinates.at(0), (*king).coordinates.at(1), chessboard, (*pieceToMove).colour)) {
	  valid = false;
	}
	else {
	  valid = true;
	}

	// Reset board to before simulation
	chessboard.updatePiece(pieceToMove, fileFrom, rankFrom);
	(chessboard.board).push_back(pieceToEat);
      }
    }
    
    // If no piece to eat - simulate moving piece
    else {
      
      chessboard.updatePiece(pieceToMove, fileTo, rankTo);

      Piece* king = chessboard.retrieveKing((*pieceToMove).colour, chessboard);

      // Check this move doesn't yield own king in check
      if (chessboard.checkForCheck((*king).coordinates.at(0), (*king).coordinates.at(1), chessboard, (*pieceToMove).colour)) {
	valid = false;
      }
      else {
	valid = true;
      }

      // Reset board to before simulation
      chessboard.updatePiece(pieceToMove, fileFrom, rankFrom);
    }
  }

  return valid;
}

