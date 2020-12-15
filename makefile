OBJ = ChessMain.o ChessBoard.o Piece.o Pawn.o Bishop.o King.o Queen.o Knight.o Rook.o
EXE = chess
CXX = g++
CXXFLAGS = -Wall -g -Wextra -MMD

$(EXE): $(OBJ)
	$(CXX) $^ -o $@

%.o: %.cpp makefile
	$(CXX) $(CXXFLAGS) -c $<

-include $(OBJ:.o=.d)

clean:
	rm -f $(OBJ) $(EXE) $(OBJ:.o=.d)

.PHONY: clean
