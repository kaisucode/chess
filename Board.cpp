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
	this->playerTurn = 0;
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
		int acc = (chessPiece.player) ? 1 : -1;

		bool canMoveForward = (this->src.x == dest.x 	// same col
				&& (this->src.y + acc == dest.y			// one step forward
					|| (firstRound && (this->src.y + 2*acc == dest.y)))	// or two if it's the first round
				&& (!this->grid[dest.y][dest.x].isOccupied));			// nothing in front

		bool canKillDiagonallyForward = ((this->src.y + acc == dest.y)		// one step forward
				&& (this->src.x + 1 == dest.x || this->src.x - 1 == dest.x)	// diagonal
				&& (this->grid[dest.y][dest.x].isOccupied)					// contains someone
				&& (this->grid[dest.y][dest.x].player != playerTurn));		// is the enemy
		return (canMoveForward || canKillDiagonallyForward);
	}
	else if (chessPieceName == "rook"){
		return straightMovementsClear(dest);
	}
	// else if (chessPiece.name == "knight"){
	// }
	else if (chessPiece.name == "bishop"){
		return diagonalMovementsClear(dest);
	}
	else if (chessPiece.name == "queen"){
			return (straightMovementsClear(dest) || diagonalMovementsClear(dest));
	}
	else if (chessPiece.name == "king"){
		int horizontalDifference = this->src.x - dest.x;
		int verticalDifference = this->src.y - dest.y;
		bool withinOneBlock = (abs(horizontalDifference) <= 1 && abs(verticalDifference) <= 1);
		return (withinOneBlock && (straightMovementsClear(dest) || diagonalMovementsClear(dest)));
	}

	cout << "idk what is happening: " << chessPieceName << endl;
	return true;
}

void Board::setSrc(sf::Vector2i cell)
{
	if(this->grid[cell.y][cell.x].isOccupied && this->grid[cell.y][cell.x].player == playerTurn){
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
	this->firstRound = false;
	// this->playerTurn = !this->playerTurn;
}

bool Board::straightMovementsClear(sf::Vector2i dest)
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
			if(this->grid[this->src.y][i].isOccupied && this->grid[this->src.y][i].player == playerTurn)
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
			if(this->grid[i][this->src.x].isOccupied && this->grid[i][this->src.x].player == playerTurn)
				return false;
		}
	}
	return true;
}

bool Board::diagonalMovementsClear(sf::Vector2i dest)
{
	// slope of 1 or -1 check
	double slope = (this->src.y - dest.y) / (this->src.x - dest.x);

	if (slope == 1.0)
	{
		return true;
	}
	else if (slope == -1.0)
	{
		return true;
	}
	else
		return false;
	
	return true;
}

