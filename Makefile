objects=main.o ChessPiece.o Board.o ResourceHolder.o
main: $(objects)
	g++ -std=c++11 $(objects) -o main -lsfml-audio -lsfml-graphics -lsfml-window -lsfml-system
# main.o: main.cpp constants.h
main.o: main.cpp
	g++ -std=c++11 -c main.cpp

Board.o: Board.h Board.cpp
	g++ -std=c++11 -c Board.cpp

ChessPiece.o: ChessPiece.h ChessPiece.cpp
	g++ -std=c++11 -c ChessPiece.cpp

ResourceHolder.o: ResourceHolder.h ResourceHolder.cpp
	g++ -std=c++11 -c ResourceHolder.cpp

clean:
	rm -f main
	rm -f *.o
