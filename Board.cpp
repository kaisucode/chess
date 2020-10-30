#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <vector>
#include "constants.h"
#include "Board.h"
using namespace std;

Board::Board(){
	this->texture.loadFromFile("assets/board.png");
	this->sprite.setTexture(this->texture);
	this->sprite.setScale(SCALE, SCALE);
	this->src = sf::Vector2i(-1, -1);
	this->dest = sf::Vector2i(-1, -1);
	this->isBlackTurn = false;
	this->srcIsSet = false;

	vector<string> piece_order = {"rook", "knight", "bishop", "queen", "king", "bishop", "knight", "rook"};
	for(int row = 0; row < 8; row++)
	{
		vector<ChessPiece> a_row;
		switch(row) 
		{
			case 0:
				for(int i = 0; i < 8; i++)
					a_row.push_back(ChessPiece(1, "black_" + piece_order[i]));
				break;
			case 1: 
				a_row.resize(8, ChessPiece(1, "black_pawn"));
				break;
			case 6: 
				a_row.resize(8, ChessPiece(0, "white_pawn"));
				break;
			case 7: 
				for(int i = 0; i < 8; i++)
					a_row.push_back(ChessPiece(0, "white_" + piece_order[i]));
				break;
			default: 
				a_row.resize(8, ChessPiece());
				break;
		}
		this->grid.push_back(a_row);
	}
}

bool Board::isValidMove(sf::Vector2i dest){

	ChessPiece chessPiece = this->grid[this->src.y][this->src.x];
	ChessPiece dest_cell = this->grid[dest.y][dest.x];

	// same cell
	if (this->src.y == dest.y && this->src.x == dest.x)
		return false;
	// out of bounds
	else if (dest.y > 7 || dest.y < 0 || dest.x > 7 || dest.x < 0){
		return false;
	}
	// occupied by ally
	else if (dest_cell.is_occupied && dest_cell.player == chessPiece.player){
		return false;
	}
	// empty cell
	else if (!chessPiece.is_occupied){
		return false;
	}


	if (chessPiece.name == "pawn"){
		// if first move for either player, then allow a pawn to move two squares
	}
	else if (chessPiece.name == "rook"){
		return straightMovementValid(src, dest);
	}
	// else if (chessPiece.name == "knight"){
	// }
	// else if (chessPiece.name == "bishop"){
	//     return diagonalMovementValid(src, dest);
	// }
	// else if (chessPiece.name == "queen"){
	//     if (src.row == dest.row || src.col == dest.col)
	//         return straightMovementValid(src, dest);
	//     else 
	//         return diagonalMovementValid(src, dest);
	// }
	// else if (chessPiece.name == "king"){
	// }

	cout << "idk what is happening" << endl;
	return true;
}

void Board::setSrc(sf::Vector2i cell)
{
	if(this->grid[cell.y][cell.x].is_occupied && this->grid[cell.y][cell.x].player == isBlackTurn){
		this->srcIsSet = true;
		this->src = cell;
	}
}

bool Board::straightMovementsValid(Position src, Position dest)
{
	if(src.row == dest.row)
	{
		int val = (dest.col-src.col) > 0 ? 1 : -1;
		for(int i = src.col; i <= dest.col; i+=val)
		{
			if(this->grid[src.row][i].is_occupied)
				return false;
		}
	}
	else if (src.col == dest.col)
	{
		int val = (dest.row-src.row) > 0 ? 1 : -1;
		for(int i = src.row; i <= dest.row; i+=val)
		{
			if(this->grid[i][src.col].is_occupied)
				return false;
		}
	}
	return true;
}

bool Board::diagonalMovementsValid(Position src, Position dest)
{
	return true;
}

