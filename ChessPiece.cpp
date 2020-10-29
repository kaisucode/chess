#include <SFML/Graphics.hpp>
#include <iostream>

#include "ChessPiece.h"
using namespace std;

// 0 is white
// 1 is black
ChessPiece::ChessPiece(int player, int x, int y){
	this->pos = {x, y};
	this->player = player;
}

