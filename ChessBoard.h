#ifndef CHESSBOARD_H
#define CHESSBOARD_H

#include <vector>
#include <string>
#include <stdio.h>

#include"Pawn.h"
#include"Queen.h"
#include"King.h"
#include"Rook.h"
#include"Bishop.h"
#include"Knight.h"

class Piece;

using namespace std;

class ChessBoard {

  friend class Piece;
  friend class Pawn;
  friend class Bishop;
  friend class Rook;
  friend class Queen;
  
 public:

  /* Set up pieces on the chessboard in default positions 
     Blacks are in row 7-8. Whites are in row 1-2. */
  ChessBoard();

  /* Submit a move to the board 
     where each position defined as coordinates (A-H, 1-8) are accepted */
  void submitMove(string posFrom, string posTo);

  /* Reset the board for new game - all pieces placed at default positions */
  void resetBoard() ;

  /* Free memory of pieces */
  ~ChessBoard();
  
 private:
 
  /* Chessboard information includes:
     - number of moves made
     - all pieces currently on chessboard */
  int numberOfMoves;
  vector<Piece*> board;

  /* --- Helper functions - retrieve information about chessboard --- */

  /* Places all pieces in default position on chessboard */
  void BoardPopulate(ChessBoard &chessboard);

  /* Check if check has occured */ 
  bool checkForCheck(int kingFile, int kingRank, ChessBoard &chessboard, int playingColour);

  /* Update piece position on chessboard */
  void updatePiece(Piece* pieceToMove, int newFile, int newRank);

  /* Get king position on chessboard */
  Piece* retrieveKing(int colour, ChessBoard &chessboard);

  /* Delete an eaten piece from chessboard */
  void eat(Piece* pieceToMove, Piece* pieceToEat, ChessBoard &chessboard);

  /* Get a piece at position (x, y) on chessboard */
  Piece* retrievePiece(int file, int rank, ChessBoard &chessboard);

  /* Check if any piece can make any move on board */
  bool anymoveAvailable(int colour, ChessBoard &chessboard);

  /* Check no piece between source and destination */
  bool checkBetween(int file, int rank, int until, vector<int> pair, ChessBoard &chessboard);

  /* --- Castling Implementation --- */
  
  /* Recognise a castling move */
  bool isCastlingMove(Piece* pieceToMove, int fileTo, int rankTo);
    
  /* Determines if conditions are met to castle */
  bool conditionsMet(Piece* pieceToMove, int rookFile, int rookRank, int until, ChessBoard &chessboard, vector<int> positions);

  /* Castle if conditions are met */
  void castle(Piece* pieceToMove, int fileTo, int rankTo, ChessBoard &chessboard);

};

#endif
