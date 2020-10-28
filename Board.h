#include "ChessPiece.h"
class Board{
	public: 
		sf::Sprite sprite;
		sf::Texture texture;
		std::map<std::string, ChessPiece> black_pieces;
		Board();
};
