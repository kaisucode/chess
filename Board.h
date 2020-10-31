#include "ChessPiece.h"
struct Position{
	int row;
	int col;
};

class Board{
	public: 
		sf::Sprite sprite;
		sf::Texture texture;
		sf::Vector2i src;
		std::vector<std::vector<ChessPiece>> grid;
		std::vector<sf::Vector2i> validMoves;
		int playerTurn;
		bool srcIsSet;
		bool firstRound;
		Board();
		void setSrc(sf::Vector2i cell);
		bool isValidMove(sf::Vector2i dest);
		void executeMove(sf::Vector2i dest);
		bool straightMovementsClear();
		bool diagonalMovementsClear(sf::Vector2i dest);
		void mapValidMoves();
};
