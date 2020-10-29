#include <SFML/Graphics.hpp>
#include <iostream>

#include "ChessPiece.h"

ChessPiece::ChessPiece(){
	this->is_occupied = false;
}

// 0 is white
// 1 is black
ChessPiece::ChessPiece(int player, std::string piece){
	this->is_occupied = true;
	this->player = player;
	this->piece = piece;
}

