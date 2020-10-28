CC				= g++
CFLAGS		= -std=c++11
LDFLAGS 	= -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
TARGET 		= main
OBJFILES	= main.o ChessPiece.o Board.o 

# all: $(TARGET)

main: $(OBJFILES)
	$(CC) $(CFLAGS) $(OBJFILES) -o $(TARGET) $(LDFLAGS)

main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Board.o: Board.h Board.cpp
	g++ -std=c++11 -c Board.cpp

ChessPiece.o: ChessPiece.h ChessPiece.cpp
	g++ -std=c++11 -c ChessPiece.cpp

clean:
	rm -f $(TARGET) $(OBJFILES)
