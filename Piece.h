#ifndef PIECE_H
#define PIECE_H

#include<vector>
#include<string>
#include<iostream>

class ChessBoard;

using namespace std;

class Piece {

  friend class ChessBoard;
  friend class Pawn;
  
 protected:

  /* Piece information includes:
     - coordinates: (65-72, 49-56)
     - colour: 0 = black, 1 = white */
  vector<int> coordinates;
  int colour;
  string colourname;

  /* Each piece type checks validity of move */
  virtual bool validMove(int fileTo, int rankTo, ChessBoard &chessboard) = 0;

  /* Overall Validity of move is confirmed if this does not yield the player in check */
  bool pieceValidMove(int fileTo, int rankTo, ChessBoard &chessboard, Piece* piecetoEat, Piece* pieceToMove);

  /* Free memory of pieces */
  virtual ~Piece() {};

  /* --- Helper functions - set piece information --- */
  
  /* Update hasMoved */
  virtual void updateMoved() {};

  /* Set check status true */
  virtual void setCheck() {};

  /* Set check status false */
  virtual void unsetCheck() {};
  
  /* --- Helper functions - retrieve information about pieces --- */

  /* Retrieve piece name */
  virtual string getName() = 0;

  /* Get move status */
  virtual bool getMovedStatus();

  /* Get check status */
  virtual bool getCheckStatus();
  
  /* Check a position is empty or occupied by other player's colour */
  bool checkPositionEmpty(vector<int> coordinates, ChessBoard &chessboard, int colour);

  /* Check destination is valid */
  bool validity(int fileTo, int rankTo, ChessBoard &chessboard, int colour);
};


#endif
