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
	this->firstRound = true;

	vector<string> pieceOrder = {"rook", "knight", "bishop", "queen", "king", "bishop", "knight", "rook"};
	for(int row = 0; row < 8; row++)
	{
		vector<ChessPiece> aRow;
		switch(row) 
		{
			case 0:
				for(int i = 0; i < 8; i++)
					aRow.push_back(ChessPiece(1, "black_" + pieceOrder[i]));
				break;
			case 1: 
				aRow.resize(8, ChessPiece(1, "black_pawn"));
				break;
			case 6: 
				aRow.resize(8, ChessPiece(0, "white_pawn"));
				break;
			case 7: 
				for(int i = 0; i < 8; i++)
					aRow.push_back(ChessPiece(0, "white_" + pieceOrder[i]));
				break;
			default: 
				aRow.resize(8, ChessPiece());
				break;
		}
		this->grid.push_back(aRow);
	}
}

bool Board::isValidMove(sf::Vector2i dest){

	ChessPiece chessPiece = this->grid[this->src.y][this->src.x];
	ChessPiece destCell = this->grid[dest.y][dest.x];

	// same cell
	if (this->src.y == dest.y && this->src.x == dest.x)
		return false;
	// out of bounds
	else if (dest.y > 7 || dest.y < 0 || dest.x > 7 || dest.x < 0){
		return false;
	}
	// occupied by ally
	else if (destCell.isOccupied && destCell.player == chessPiece.player){
		return false;
	}

	string chessPieceName = chessPiece.name.erase(0, 6);
	if (chessPieceName == "pawn"){
		// if first move for either player, then allow a pawn to move two squares
		int acc = (chessPiece.player) ? 1 : -1;
		return this->src.x == dest.x && 
			(this->src.y + acc == dest.y || (firstRound && (this->src.y + 2*acc == dest.y)));
	}
	else if (chessPieceName == "rook"){
		return straightMovementsValid(dest);
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

	cout << "idk what is happening: " << chessPieceName << endl;
	return true;
}

void Board::setSrc(sf::Vector2i cell)
{
	if(this->grid[cell.y][cell.x].isOccupied && this->grid[cell.y][cell.x].player == isBlackTurn){
		this->srcIsSet = true;
		this->src = cell;
	}
}

void Board::executeMove(sf::Vector2i dest)
{
	cout << "move executing" << endl;
	this->grid[dest.y][dest.x] = this->grid[this->src.y][this->src.x];
	this->grid[this->src.y][this->src.x] = ChessPiece();
	this->srcIsSet = false;
}

bool Board::straightMovementsValid(sf::Vector2i dest)
{
	if (this->src.y != dest.y && this->src.x != dest.x)
		return false;
	else if(this->src.y == dest.y)
	{
		int val = (dest.x - this->src.x) > 0 ? 1 : -1;
		int start = min(this->src.x + val, dest.x);
		int end = max(this->src.x + val, dest.x);
		for(int i = start; i <= end; i++)
		{
			if(this->grid[this->src.y][i].isOccupied)
				return false;
		}
	}

	else if(this->src.x == dest.x)
	{
		int val = (dest.y - this->src.y) > 0 ? 1 : -1;
		int start = min(this->src.y + val, dest.y);
		int end = max(this->src.y + val, dest.y);

		for(int i = start; i <= end; i++)
		{
			if(this->grid[i][this->src.x].isOccupied)
				return false;
		}
	}
	return true;
}

bool Board::diagonalMovementsValid(Position src, Position dest)
{
	return true;
}

