#include "ChessPiece.h"
struct Position{
	int row;
	int col;
};

class Board{
	public: 
		sf::Sprite sprite;
		sf::Texture texture;
		std::vector<std::vector<ChessPiece>> grid;
		Board();
		bool isValidMove(Position src, Position dest);
		bool straightMovementValid(Position src, Position dest);
		bool diagonalMovementValid(Position src, Position dest);
};
