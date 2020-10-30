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
		int playerTurn;
		bool srcIsSet;
		bool firstRound;
		Board();
		void setSrc(sf::Vector2i cell);
		bool isValidMove(sf::Vector2i dest);
		void executeMove(sf::Vector2i dest);
		bool straightMovementsClear(sf::Vector2i dest);
		bool diagonalMovementsClear(sf::Vector2i dest);
};
