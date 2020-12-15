#include"ChessBoard.h"
#include"Piece.h"

#include <string.h>
#include <iostream>
#include <cstdlib>
#include <stdlib.h>

using namespace std;

const int BLACK = 0;
const int WHITE = 1;

const int BLACK_START = 55;
const int WHITE_START = 50;

const int FILE_POS = 0;
const int RANK_POS = 1;
const int COORDINATES = 2;

const int NB_PAWNS = 8;

/* Check input is valid (i.e. Row between 1 and 8 and Column between A and H) */
int checkInput(string position) {

  int correct = 0;
  
  int length = position.length();
  if (length != COORDINATES)
    return -1;

  int file = (int) position[0];
  if (!(file >= 'A' && file <= 'H')) {
    return -1;
  }

  int rank = (int) position[1];
  if (!(rank >= '1' && rank <= '8')) {
    return -1;
  }

  return correct;
}

/* Get a piece at position (x, y) on chessboard */
Piece* ChessBoard::retrievePiece(int file, int rank, ChessBoard &chessboard) {

  vector<int> coordinates = {file, rank};
  Piece* retrievedPiece = nullptr;
  
  for (int unsigned i = 0; i < chessboard.board.size(); i++) {
    Piece* pieceI = chessboard.board.at(i);
    if (coordinates.at(0) == (*pieceI).coordinates.at(0))
      if (coordinates.at(1) == (*pieceI).coordinates.at(1)) {
	retrievedPiece = pieceI;
	return retrievedPiece;
      }
  }
  
  return retrievedPiece;
}

/* Update a piece position on chessboard */
void ChessBoard::updatePiece(Piece* pieceToMove, int newFile, int newRank) {

  (*pieceToMove).coordinates.at(0) = newFile;
  (*pieceToMove).coordinates.at(1) = newRank;
}

/* Delete an eaten piece from chessboard */
void ChessBoard::eat(Piece* pieceToMove, Piece* pieceToEat, ChessBoard &chessboard) {

  for (int unsigned i = 0; i < chessboard.board.size(); i++) {
    Piece* pieceI = chessboard.board.at(i);
    
    if ((*pieceToEat).coordinates.at(0) == (*pieceI).coordinates.at(0) && (*pieceToEat).coordinates.at(1) == (*pieceI).coordinates.at(1)) {

      (chessboard.board).erase((chessboard.board).begin() + i);
    }
  }

  // Piece has been deleted, now update position of piece that eated
  updatePiece(pieceToMove, (*pieceToEat).coordinates.at(0), (*pieceToEat).coordinates.at(1));
  
}

/* Check if check has occured */ 
bool ChessBoard::checkForCheck(int kingFile, int kingRank, ChessBoard &chessboard, int playingColour) {
  
  bool answer = false;
  
  for (int unsigned i = 0; i < chessboard.board.size(); i++) {
    Piece* pieceI = chessboard.board.at(i);
    if ((*pieceI).colour != playingColour) {
      // For any piece of other player, can it eat the king
      bool valid = (*pieceI).validMove(kingFile, kingRank, chessboard);
      if (valid == true) {
	return true;
      }
    }
  }
  
  return answer;

}

/* Output other player's colour */
int swapPlayer(int colour) {
  if (colour == 1) {
    return 0;
  }
  else {
    return 1;
  }
}

/* Output other player's colour name */
string colourName(int colour) {
  if (colour == 1) {
    return "WHITE";
  }
  else {
    return "BLACK";
  }
}

/* Get king position on chessboard */
Piece* ChessBoard::retrieveKing(int colour, ChessBoard &chessboard) {

  for (int unsigned i = 0; i < chessboard.board.size(); i++) {
    Piece* pieceI = chessboard.board.at(i);
    if ( (*pieceI).colour == colour && (*pieceI).getName() == "King") {
      return pieceI;
    }
  }
  
  return nullptr;
}

/* Check if any piece can make any move on board */
bool ChessBoard::anymoveAvailable(int colour, ChessBoard &chessboard) {
  
  bool answer = false;
  int fileI, rankJ;
  
  for (int unsigned i = 0; i < chessboard.board.size(); i++) {
    Piece* pieceI = chessboard.board.at(i);
    if ( (*pieceI).colour == colour) {
      for (int i = 'A'; i <= 'H'; i++) {
	for (int j = '1'; j <= '8'; j++) {
	  fileI = i;
	  rankJ = j;
	  Piece* pieceToEat = chessboard.retrievePiece(fileI, rankJ, chessboard);
	  bool valid = (*pieceI).pieceValidMove(fileI, rankJ, chessboard, pieceToEat, pieceI);
	  if (valid) {
	    return true;
	  }
	}
      }
    }
  }

  return answer;
}

/* Check no piece between source and destination */
bool ChessBoard::checkBetween(int file, int rank, int until, vector<int> pair, ChessBoard &chessboard) {

  int fileI, rankI;

  for (int i = 1; i < until; i++) {
    
    fileI = (pair.at(0) * i + file);
    rankI = (pair.at(1) * i + rank);
    vector<int> coordinates = {fileI, rankI};

    // Is there a piece at each position between source and destination
    for (int unsigned i = 0; i < chessboard.board.size(); i++) {
      Piece* pieceI = chessboard.board.at(i);
      if (coordinates.at(0) == (*pieceI).coordinates.at(0)) {
	if (coordinates.at(1) == (*pieceI).coordinates.at(1)) {
	  return true;
	}
      }
    }
  }
  
  return false;
}

/* Checks conditions are met to castle King and Rook */
bool ChessBoard::conditionsMet(Piece* pieceToMove, int rookFile, int rookRank, int until, ChessBoard &chessboard, vector<int> positions) {

  bool answer = true;
  
  int KingFile = (*pieceToMove).coordinates.at(0);
  int KingRank = (*pieceToMove).coordinates.at(1);
  
  vector<int> pair = {1, 0};
  Piece* rook = retrievePiece(rookFile, rookRank, chessboard);

  // King is not in check
  if ( (*pieceToMove).getCheckStatus() == true ) {
    return false;
  }
  
  // Pieces have not already moved
  if ( (*pieceToMove).getMovedStatus() == true || (*rook).getMovedStatus() == true ) {
      return false;
  }
  
  // No pieces between king and rook
  if (checkBetween(KingFile, KingRank, until, pair, chessboard)) {
    return false;
  }

  // King is not in check in any of the positions it passes through
  for (int unsigned i = 0; i < positions.size(); i++) {
    int KingFileTo = positions.at(i) + KingFile;
    if (checkForCheck(KingFileTo, KingRank, chessboard, (*pieceToMove).colour)) {
      return false;
    }
  }
  
  return answer;
}

/* Check if move submitted is a castling move */
bool ChessBoard::isCastlingMove(Piece* pieceToMove, int fileTo, int rankTo) {

  if ( (fileTo == 'G' && rankTo == '1') && (*pieceToMove).getName() == "King") {
    return true;
  }
  else if ( (fileTo == 'C' && rankTo == '1') && (*pieceToMove).getName() == "King") {
    return true;
  }
  else if ( (fileTo == 'G' && rankTo == '8') && (*pieceToMove).getName() == "King") {
    return true;
  }
  else if ( (fileTo == 'C' && rankTo == '8') && (*pieceToMove).getName() == "King") {
    return true;
  }

  return false;

}

/* Determines if castling is valid, if yes moves pieces */
void ChessBoard::castle(Piece* pieceToMove, int fileTo, int rankTo, ChessBoard &chessboard) {

  vector<int> positionsLeft = {-1, -2};
  vector<int> positionsRight = {1, 2};
  
  // White King move right
  if ( fileTo == 'G' && rankTo == '1' ) {
    int rookFile = 'H';
    int rookRank = '1';
    Piece* rook = retrievePiece(rookFile, rookRank, chessboard);
    if (conditionsMet(pieceToMove, rookFile, rookRank, 2, chessboard, positionsRight)) {
      updatePiece(pieceToMove, 71, 49);
      updatePiece(rook, 70, 49);
      cout << (*pieceToMove).colourname << " King castled with Rook from E1 to G1! \n";
    }
    else {
      cout << "Invalid castling attempt from E1 to G1. \n";
    }
  }

  // White King move left
  else if ( fileTo == 'C' && rankTo == '1') {
    int rookFile = 'A';
    int rookRank = '1';
    Piece* rook = retrievePiece(rookFile, rookRank, chessboard);
    if (conditionsMet(pieceToMove, rookFile, rookRank, 3, chessboard, positionsLeft)) {
      updatePiece(pieceToMove, 67, 49);
      updatePiece(rook, 68, 49);
      cout << (*pieceToMove).colourname << " King castled with Rook from E1 to C1! \n";
    }
    else {
      cout << "Invalid castling attempt from E1 to C1. \n";
    }
  }

  // Black King move right
  else if ( fileTo == 'G' && rankTo == '8' ) {
    int rookFile = 'A';
    int rookRank = '8';
    Piece* rook = retrievePiece(rookFile, rookRank, chessboard);
    if (conditionsMet(pieceToMove, rookFile, rookRank, 2, chessboard, positionsRight)) {
      updatePiece(pieceToMove, 71, 56);
      updatePiece(rook, 70, 56);
      cout << (*pieceToMove).colourname << " King castled with Rook from E8 to G8! \n";
    }
    else {
      cout << "Invalid castling attempt from E8 to G8. \n";
    }
  }

  // Black King move left 
  else if ( fileTo == 'C' && rankTo == '8' ) {
    int rookFile = 'G';
    int rookRank = '8';
    Piece* rook = retrievePiece(rookFile, rookRank, chessboard);
    if (conditionsMet(pieceToMove, rookFile, rookRank, 3, chessboard, positionsLeft)) {
      updatePiece(pieceToMove, 67, 56);
      updatePiece(rook, 68, 56);
      cout << (*pieceToMove).colourname << " King castled with Rook from E8 to C8! \n";
    }
    else {
      cout << "Invalid castling attempt from E8 to C8. \n";
    }
  }
}

/* Submit a move to the board */
void ChessBoard::submitMove(string posFrom, string posTo) {
  
  // Check input coordinates are valid
  int errorFrom = checkInput(posFrom);
  int errorTo = checkInput(posTo);
  if (errorFrom != -1 && errorTo != -1) {

    int fileFrom = posFrom[FILE_POS];
    int rankFrom = posFrom[RANK_POS];

    int fileTo = posTo[FILE_POS];
    int rankTo = posTo[RANK_POS];
    
    // Retrieve pieces at specified positions
    Piece* pieceToMove = retrievePiece(fileFrom, rankFrom, *this);
    Piece* pieceToEat = retrievePiece(fileTo, rankTo, *this);

    // Check piece to move exists
    if (pieceToMove != nullptr) {

      // Check right team is playing
      if ( (*this).numberOfMoves % 2 == 0 && (*pieceToMove).colour == BLACK ) {
	cout << "It is not Black's turn to move! \n";
	
      }
      else if ( (*this).numberOfMoves % 2 != 0 && (*pieceToMove).colour == WHITE ){
	cout << "It is not White's turn to move! \n";
      }
      
      else if ( ((*this).numberOfMoves % 2 == 0 && (*pieceToMove).colour == WHITE) || ((*this).numberOfMoves % 2 != 0 && (*pieceToMove).colour == BLACK) ) {

	// Check for Castling move
	if (isCastlingMove(pieceToMove, fileTo, rankTo)) {
	  castle(pieceToMove, fileTo, rankTo, *this);
	  (*this).numberOfMoves++;
	}
	
	else {
	// Check move is valid
	  bool valid = (*pieceToMove).pieceValidMove(fileTo, rankTo, *this, pieceToEat, pieceToMove);
	  if (valid == true) {
	    (*this).numberOfMoves++;
	    // Keep track of piece movement
	    if ((*pieceToMove).getName() == "Rook" || (*pieceToMove).getName() == "King") {
	      (*pieceToMove).updateMoved();
	    }
	    // If destination contains piece - eat it 
	    if (pieceToEat != nullptr) {
	      if ((*pieceToMove).colour != (*pieceToEat).colour) {
		eat(pieceToMove, pieceToEat, *this);
		
		cout << (*pieceToMove).colourname << "'s " << (*pieceToMove).getName() << " moves from " << posFrom << " to " << posTo << " taking " << (*pieceToEat).colourname << "'s " << (*pieceToEat).getName() << "\n";
	      }
	      else {
		cout << "Cannot eat your own pieces \n";
	      }
	    }
	    // If no piece to eat - move piece
	    else {
	      cout << (*pieceToMove).colourname << "'s " << (*pieceToMove).getName() << " moves from " << posFrom << " to " << posTo << "\n";
	      
	      updatePiece(pieceToMove, fileTo, rankTo);
	    }
	    
	    // Check if moves yields other player's king in check
	    int otherColour = swapPlayer((*pieceToMove).colour);
	    string otherColourName = colourName(otherColour);
	    Piece* king = retrieveKing(otherColour, *this);
	    
	    if (checkForCheck((*king).coordinates.at(0), (*king).coordinates.at(1), *this, otherColour) && !anymoveAvailable(otherColour, *this)) {
	      
	    cout << otherColourName << " is in checkmate! \n";
	    }
	    else if (checkForCheck((*king).coordinates.at(0), (*king).coordinates.at(1), *this, otherColour)) {
	      cout << otherColourName << " is in check! \n";
	      
	      // Update King check status
	      (*king).setCheck();
	    }
	    else if (!anymoveAvailable(otherColour, *this)) {
	      cout << otherColourName << " is in stalemate! \n";
	    }
	    else {
	      (*king).unsetCheck();
	    }
	  }
	  // Invalid move
	  else {
	    cout << (*pieceToMove).colourname << "'s " << (*pieceToMove).getName() << " cannot move to: " << posTo << "!\n";
	  }
	}
      }
    }
    // No piece at input position
    else if (pieceToMove == nullptr) {
      cout << "There is no piece at position " << posFrom << "!\n";
    }
  }
  // Wrong inputs
  else {
    if (errorFrom == -1) {
      cout << "Invalid position input: " << posFrom << "\n";
    }
    else if (errorTo == -1) {
      cout << "Invalid position input: " << posTo << "\n";
    }
  }
}

void ChessBoard::BoardPopulate(ChessBoard &chessboard) {
  
  // Place all pieces in default position
  int rankBlackPawn = '7';
  int rankWhitePawn = '2';

  // Black Pawns
  for (int i = 0; i < NB_PAWNS; i++) {
    Piece* piece = new Pawn;
    int file = i + 'A';
    (*piece).coordinates = { file, rankBlackPawn };
    (*piece).colour = BLACK;
    (*piece).colourname = "Black";
    chessboard.board.push_back(piece);
  }

  // White Pawns
  for (int i = 0; i < NB_PAWNS; i++) {
    Piece* piece = new Pawn;
    int file = i + 'A';
    (*piece).coordinates = { file, rankWhitePawn };
    (*piece).colour = WHITE;
    (*piece).colourname = "White";
    chessboard.board.push_back(piece);
  }

  // Default rank for white/black pieces
  int rankBlack = '8';
  int rankWhite = '1';

  // Default file for pieces
  vector<int> rook = {'A', 'H'};
  vector<int> knight = {'B', 'G'};
  vector<int> bishop = {'C', 'F'};
  vector<int> queenAndKing = {'D', 'E'};

  // Rook (Black and White)
  for (int unsigned i = 0; i < rook.size(); i++) {
    Piece* piece = new Rook(false);
    (*piece).coordinates = { rook[i], rankBlack};
    (*piece).colour = BLACK;
    (*piece).colourname = "Black";
    chessboard.board.push_back(piece);
  }
  
  for (int unsigned i = 0; i < rook.size(); i++) {
    Piece* piece = new Rook(false);
    (*piece).coordinates = { rook[i], rankWhite};
    (*piece).colour = WHITE;
    (*piece).colourname = "White";
    chessboard.board.push_back(piece);
  }

  // Knight (Black and White)
  for (int unsigned i = 0; i < knight.size(); i++) {
    Piece* piece = new Knight;
    (*piece).coordinates = { knight[i], rankBlack};
    (*piece).colour = BLACK;
    (*piece).colourname = "Black";
    chessboard.board.push_back(piece);
  }
  
  for (int unsigned i = 0; i < knight.size(); i++) {
    Piece* piece = new Knight;
    (*piece).coordinates = { knight[i], rankWhite};
    (*piece).colour = WHITE;
    (*piece).colourname = "White";
    chessboard.board.push_back(piece);
  }

  // Bishop (Black and White)
  for (int unsigned i = 0; i < bishop.size(); i++) {
    Piece* piece = new Bishop;
    (*piece).coordinates = { bishop[i], rankBlack};
    (*piece).colour = BLACK;
    (*piece).colourname = "Black";
    chessboard.board.push_back(piece);
  }
  
  for (int unsigned i = 0; i < bishop.size(); i++) {
    Piece* piece = new Bishop;
    (*piece).coordinates = { bishop[i], rankWhite};
    (*piece).colour = WHITE;
    (*piece).colourname = "White";
    chessboard.board.push_back(piece);
  }

  // Queen and King Black
  for (int unsigned i = 0; i < queenAndKing.size(); i++) {
    if (i == 0) {
      Piece* piece = new Queen;
      (*piece).coordinates = { queenAndKing[i], rankBlack};
      (*piece).colour = BLACK;
      (*piece).colourname = "Black";
      chessboard.board.push_back(piece);
    }
    else {
      Piece* piece = new King(false, false);
      (*piece).coordinates = { queenAndKing[i], rankBlack};
      (*piece).colour = BLACK;
      (*piece).colourname = "Black";
      chessboard.board.push_back(piece);
    }
  }

  // Queen and King White
  for (int unsigned i = 0; i < queenAndKing.size(); i++) {
    if (i == 0) {
      Piece* piece = new Queen;
      (*piece).coordinates = { queenAndKing[i], rankWhite};
      (*piece).colour = WHITE;
      (*piece).colourname = "White";
      chessboard.board.push_back(piece);
    }
    else {
      Piece* piece = new King(false, false);
      (*piece).coordinates = { queenAndKing[i], rankWhite};
      (*piece).colour = WHITE;
      (*piece).colourname = "White";
      chessboard.board.push_back(piece);
    }
  }

  chessboard.numberOfMoves = 0;
  
  cout << "A new chess game is started! \n";
  
}

/* Reset the board for new game - all pieces placed at default positions */
void ChessBoard::resetBoard() {
  
  for (int unsigned i = 0; i < board.size(); i++) {
    delete board[i];
  }
 
  board.clear();

  BoardPopulate(*this);

}

/* Set board in default position */
ChessBoard::ChessBoard() {

  resetBoard();
  
}

/* Free memory of pieces */
ChessBoard::~ChessBoard() {

  for (int unsigned i = 0; i < board.size(); i++) {
      delete board[i];
  }

  board.clear();
  
}

