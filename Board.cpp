#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
using namespace std;

// #include "ChessPiece.h"
#include "Board.h"

Board::Board(){
	this->texture.loadFromFile("assets/board.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setPosition(200, 200);

	this->black_pieces.insert(pair<string, ChessPiece>("black_rook_1", ChessPiece(1, 1, 0)));
	this->black_pieces.insert(pair<string, ChessPiece>("black_knight_1", ChessPiece(1, 1, 0)));

	// ResourceHolder<sf::Texture, Textures::ID> textures;
	// textures.load(Textures::black_pawn, "assets/black_pawn.png");
	// sf::Sprite black_pawn(textures.get(Textures::black_pawn));

}

