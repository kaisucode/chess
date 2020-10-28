#include <SFML/Graphics.hpp>
#include <iostream>

#include "ChessPiece.h"
using namespace std;

// 0 is white
// 1 is black
ChessPiece::ChessPiece(string img_url, int player, int x, int y){
	this->texture.loadFromFile("assets/black_knight.png");
	this->sprite.setTexture(this->texture);
	this->pos = {x, y};
	this->player = player;
	this->sprite.setPosition(this->pos.x * 10, this->pos.y * 10);
}

