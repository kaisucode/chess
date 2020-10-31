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
		bool withinBoard(sf::Vector2i cell);
		bool determineCellAndShouldContinue(sf::Vector2i cell);
		void setSrc(sf::Vector2i cell);
		void executeMove(sf::Vector2i dest);
		void mapValidMoves();
		void straightMovements();
		void diagonalMovements();
		void pawnMovements();
		void knightMovements();
		void kingMovements();
		ChessPiece getGridPiece(sf::Vector2i cell);
};
