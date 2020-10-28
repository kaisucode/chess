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

	ChessPiece black_knight("assets/black_knight.png", 0, 3, 4);
	this->black_pieces.insert(pair<string, ChessPiece>("black_knight", black_knight));
}

