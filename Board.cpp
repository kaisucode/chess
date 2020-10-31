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

bool Board::withinBoard(sf::Vector2i cell){
	return (cell.x >= 0 && cell.x <= 7 && cell.y >= 0 && cell.y <= 7);
}

ChessPiece Board::getGridPiece(sf::Vector2i cell){
	return this->grid[cell.y][cell.x];
}

void Board::mapValidMoves(){
	ChessPiece chessPiece = getGridPiece(this->src);
	string chessPieceName = chessPiece.name.erase(0, 6);

	if (chessPieceName == "pawn"){
		pawnMovements();
	}
	else if (chessPieceName == "rook"){
		straightMovementsClear();
	}
	// else if (chessPiece.name == "knight"){
	// }
	// else if (chessPiece.name == "bishop"){
	//     return diagonalMovementsClear();
	// }
	// else if (chessPiece.name == "queen"){
	//     return (straightMovementsClear() || diagonalMovementsClear());
	// }
	// else if (chessPiece.name == "king"){
	//     int horizontalDifference = this->src.x - dest.x;
	//     int verticalDifference = this->src.y - dest.y;
	//     bool withinOneBlock = (abs(horizontalDifference) <= 1 && abs(verticalDifference) <= 1);
	//     return (withinOneBlock && (straightMovementsClear() || diagonalMovementsClear(dest)));
	// }

}

// bool Board::isValidMove(sf::Vector2i dest){

//     ChessPiece chessPiece = this->grid[this->src.y][this->src.x];
//     ChessPiece destCell = this->grid[dest.y][dest.x];

//     // same cell
//     if (this->src.y == dest.y && this->src.x == dest.x)
//         return false;
//     // out of bounds
//     else if (dest.y > 7 || dest.y < 0 || dest.x > 7 || dest.x < 0){
//         return false;
//     }
//     // occupied by ally
//     else if (destCell.isOccupied && destCell.player == chessPiece.player){
//         return false;
//     }

//     string chessPieceName = chessPiece.name.erase(0, 6);
//     if (chessPieceName == "pawn"){
//         int acc = (chessPiece.player) ? 1 : -1;

//         bool canMoveForward = (this->src.x == dest.x 	// same col
//                 && (this->src.y + acc == dest.y			// one step forward
//                     || (firstRound && (this->src.y + 2*acc == dest.y)))	// or two if it's the first round
//                 && (!this->grid[dest.y][dest.x].isOccupied));			// nothing in front

//         bool canKillDiagonallyForward = ((this->src.y + acc == dest.y)		// one step forward
//                 && (this->src.x + 1 == dest.x || this->src.x - 1 == dest.x)	// diagonal
//                 && (this->grid[dest.y][dest.x].isOccupied)					// contains someone
//                 && (this->grid[dest.y][dest.x].player != playerTurn));		// is the enemy
//         return (canMoveForward || canKillDiagonallyForward);
//     }
//     else if (chessPieceName == "rook"){
//         return straightMovementsClear();
//     }
//     // else if (chessPiece.name == "knight"){
//     // }
//     else if (chessPiece.name == "bishop"){
//         return diagonalMovementsClear(dest);
//     }
//     else if (chessPiece.name == "queen"){
//         return (straightMovementsClear() || diagonalMovementsClear(dest));
//     }
//     else if (chessPiece.name == "king"){
//         int horizontalDifference = this->src.x - dest.x;
//         int verticalDifference = this->src.y - dest.y;
//         bool withinOneBlock = (abs(horizontalDifference) <= 1 && abs(verticalDifference) <= 1);
//         return (withinOneBlock && (straightMovementsClear() || diagonalMovementsClear(dest)));
//     }

//     cout << "idk what is happening: " << chessPieceName << endl;
//     return true;
// }

void Board::setSrc(sf::Vector2i cell)
{
	if(this->grid[cell.y][cell.x].isOccupied && this->grid[cell.y][cell.x].player == playerTurn){
		this->srcIsSet = true;
		this->src = cell;
		this->validMoves.clear();
		mapValidMoves();
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

void Board::straightMovementsClear()
{
	// vertical movement
	int num = this->src.y;
	for(int i = num - 1; i >= 0; i--){
		sf::Vector2i nextCell(this->src.x, i);
		if(!getGridPiece(nextCell).isOccupied)
			this->validMoves.push_back(nextCell);
		else if (getGridPiece(nextCell).player == playerTurn)	// ally
			break;
		else{	// enemy
			this->validMoves.push_back(nextCell);
			break;
		}
	}
	for(int i = num + 1; i < 8; i++){
		sf::Vector2i nextCell(this->src.x, i);
		if(!getGridPiece(nextCell).isOccupied)
			this->validMoves.push_back(nextCell);
		else if (getGridPiece(nextCell).player == playerTurn)	// ally
			break;
		else{	// enemy
			this->validMoves.push_back(nextCell);
			break;
		}
	}
	// horizontal movement
	num = this->src.x;
	for(int i = num - 1; i >= 0; i--){
		sf::Vector2i nextCell(i, this->src.y);
		if(!getGridPiece(nextCell).isOccupied)
			this->validMoves.push_back(nextCell);
		else if (getGridPiece(nextCell).player == playerTurn)	// ally
			break;
		else{	// enemy
			this->validMoves.push_back(nextCell);
			break;
		}
	}
	for(int i = num + 1; i < 8; i++){
		sf::Vector2i nextCell(i, this->src.y);
		if(!getGridPiece(nextCell).isOccupied)
			this->validMoves.push_back(nextCell);
		else if (getGridPiece(nextCell).player == playerTurn)	// ally
			break;
		else{	// enemy
			this->validMoves.push_back(nextCell);
			break;
		}
	}
}

void Board::diagonalMovementsClear()
{
}

void Board::pawnMovements()
{
	int acc = (this->playerTurn) ? 1 : -1;

	// vertical movements
	sf::Vector2i cellInFront(this->src.x, this->src.y + acc);
	if (withinBoard(cellInFront) && !getGridPiece(cellInFront).isOccupied){
		this->validMoves.push_back(cellInFront);
		sf::Vector2i twoCellsInFront(this->src.x, this->src.y + acc * 2);
		if (firstRound && withinBoard(twoCellsInFront) && !getGridPiece(twoCellsInFront).isOccupied){
			this->validMoves.push_back(twoCellsInFront);
		}
	}

	// diagonal movements
	sf::Vector2i cellFrontLeft(this->src.x - 1, this->src.y + acc);
	sf::Vector2i cellFrontRight(this->src.x + 1, this->src.y + acc);
	if (withinBoard(cellFrontLeft) 
			&& getGridPiece(cellFrontLeft).isOccupied 
			&& getGridPiece(cellFrontLeft).player != playerTurn){
		this->validMoves.push_back(cellFrontLeft);
	}
	if (withinBoard(cellFrontRight) 
			&& getGridPiece(cellFrontRight).isOccupied 
			&& getGridPiece(cellFrontRight).player != playerTurn){
		this->validMoves.push_back(cellFrontRight);
	}
}

