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
		sf::Vector2i src;
		sf::Vector2i dest;
		bool srcIsSet;
		bool isBlackTurn;
		Board();
		void setSrc(sf::Vector2i cell);
		bool isValidMove(Position src, Position dest);
		bool straightMovementValid(Position src, Position dest);
		bool diagonalMovementValid(Position src, Position dest);
};
