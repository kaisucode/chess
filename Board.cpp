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

void Board::setSrc(sf::Vector2i cell)
{
	if(this->grid[cell.y][cell.x].isOccupied && this->grid[cell.y][cell.x].player == playerTurn){
		this->src = cell;
		this->validMoves.clear();
		mapValidMoves();
		if (this->validMoves.size())
			this->srcIsSet = true;
	}
}

void Board::executeMove(sf::Vector2i dest)
{
	// cout << "move executing" << endl;
	this->grid[dest.y][dest.x] = this->grid[this->src.y][this->src.x];
	this->grid[this->src.y][this->src.x] = ChessPiece();
	this->srcIsSet = false;
	if(playerTurn)	// end of round
		this->firstRound = false;
	// this->playerTurn = !this->playerTurn; // don't change order of this line and the one above
	this->firstRound = false; // comment this out when player turns are reactivated
}

void Board::mapValidMoves(){
	ChessPiece chessPiece = getGridPiece(this->src);
	string chessPieceName = chessPiece.name.erase(0, 6);

	if (chessPieceName == "pawn"){
		pawnMovements();
	}
	else if (chessPieceName == "rook"){
		straightMovements();
	}
	else if (chessPiece.name == "knight"){
		knightMovements();
	}
	else if (chessPiece.name == "bishop"){
		diagonalMovements();
	}
	else if (chessPiece.name == "queen"){
		straightMovements();
		diagonalMovements();
	}
	else if (chessPiece.name == "king"){
		kingMovements();
	}
}

bool Board::determineCellAndShouldContinue(sf::Vector2i cell){
	if(!getGridPiece(cell).isOccupied){						// empty
		this->validMoves.push_back(cell);
		return true;
	}
	else if (!(getGridPiece(cell).player == playerTurn))	// enemy
		this->validMoves.push_back(cell);
	return false;											// ally
}

void Board::straightMovements()
{
	// vertical movement
	int num = this->src.y;
	for(int i = num - 1; i >= 0; i--){
		sf::Vector2i nextCell(this->src.x, i);
		if(!determineCellAndShouldContinue(nextCell))
			break;
	}
	for(int i = num + 1; i < 8; i++){
		sf::Vector2i nextCell(this->src.x, i);
		if(!determineCellAndShouldContinue(nextCell))
			break;
	}
	// horizontal movement
	num = this->src.x;
	for(int i = num - 1; i >= 0; i--){
		sf::Vector2i nextCell(i, this->src.y);
		if(!determineCellAndShouldContinue(nextCell))
			break;
	}
	for(int i = num + 1; i < 8; i++){
		sf::Vector2i nextCell(i, this->src.y);
		if(!determineCellAndShouldContinue(nextCell))
			break;
	}
}

void Board::diagonalMovements()
{
	vector<sf::Vector2i> op = {
		sf::Vector2i(1, 1), 
		sf::Vector2i(1, -1), 
		sf::Vector2i(-1, 1), 
		sf::Vector2i(-1, -1)
	};

	for(int i = 0; i < op.size(); i++){
		sf::Vector2i nextCell(this->src.x + op[i].x, this->src.y + op[i].y);
		while(withinBoard(nextCell)){
			if(!determineCellAndShouldContinue(nextCell))
				break;
			nextCell = sf::Vector2i(nextCell.x + op[i].x, nextCell.y + op[i].y);
		}
	}
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

void Board::knightMovements(){
	vector<sf::Vector2i> destDeltas = {
		sf::Vector2i(-2, 1), 
		sf::Vector2i(-2, -1), 
		sf::Vector2i(2, 1), 
		sf::Vector2i(2, -1), 
		sf::Vector2i(-1, -2), 
		sf::Vector2i(1, -2), 
		sf::Vector2i(1, 2), 
		sf::Vector2i(-1, 2), 
	};

	for(int i = 0; i < destDeltas.size(); i++){
		sf::Vector2i newDest(this->src + destDeltas[i]);
		if (withinBoard(newDest) && (!getGridPiece(newDest).isOccupied || getGridPiece(newDest).player != playerTurn))
			this->validMoves.push_back(newDest);
	}
}

void Board::kingMovements(){
	for(int i = -1; i <= 1; i++){
		for(int j = -1; j <= 1; j++){
			sf::Vector2i nextCell(this->src.x + i, this->src.y + j);
			if (i == 0 && j == 0)
				continue;
			else if(withinBoard(nextCell))
				determineCellAndShouldContinue(nextCell);
		}
	}
}
