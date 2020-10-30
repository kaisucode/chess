#include <SFML/Graphics.hpp>
#include <iostream>

#include "ChessPiece.h"

ChessPiece::ChessPiece(){
	this->isOccupied = false;
}

// 0 is white
// 1 is black
ChessPiece::ChessPiece(int player, std::string name){
	this->isOccupied = true;
	this->player = player;
	this->name = name;
}

