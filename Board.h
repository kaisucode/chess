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
		bool firstRound;
		Board();
		void setSrc(sf::Vector2i cell);
		bool isValidMove(sf::Vector2i dest);
		void executeMove(sf::Vector2i dest);
		bool straightMovementsValid(sf::Vector2i dest);
		bool diagonalMovementsValid(Position src, Position dest);
};
