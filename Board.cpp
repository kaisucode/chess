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

	this->black_pieces.insert(pair<string, ChessPiece>("black_rook_1", ChessPiece(1, 1, 0)));
	this->black_pieces.insert(pair<string, ChessPiece>("black_knight_1", ChessPiece(1, 1, 0)));
}

