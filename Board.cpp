#include <SFML/Graphics.hpp>
#include <iostream>
#include <string>
#include <map>
#include <vector>
using namespace std;

// #include "ChessPiece.h"
#include "Board.h"

Board::Board(){
	this->texture.loadFromFile("assets/board.png");
	this->sprite.setTexture(this->texture);

	for(int row = 0; row < 8; row++)
	{
		vector<ChessPiece> a_row;
		switch(row) 
		{
			case 0:
				a_row.push_back(ChessPiece(1, "black_rook"));
				a_row.push_back(ChessPiece(1, "black_knight"));
				a_row.push_back(ChessPiece(1, "black_bishop"));
				a_row.push_back(ChessPiece(1, "black_queen"));
				a_row.push_back(ChessPiece(1, "black_king"));
				a_row.push_back(ChessPiece(1, "black_bishop"));
				a_row.push_back(ChessPiece(1, "black_knight"));
				a_row.push_back(ChessPiece(1, "black_rook"));
				break;
			case 1: 
				a_row.resize(8, ChessPiece(1, "black_pawn"));
				break;
			case 6: 
				a_row.resize(8, ChessPiece(0, "white_pawn"));
				break;
			case 7: 
				a_row.push_back(ChessPiece(0, "white_rook"));
				a_row.push_back(ChessPiece(0, "white_knight"));
				a_row.push_back(ChessPiece(0, "white_bishop"));
				a_row.push_back(ChessPiece(0, "white_queen"));
				a_row.push_back(ChessPiece(0, "white_king"));
				a_row.push_back(ChessPiece(0, "white_bishop"));
				a_row.push_back(ChessPiece(0, "white_knight"));
				a_row.push_back(ChessPiece(0, "white_rook"));
				break;
			default: 
				a_row.resize(8, ChessPiece());
				break;
		}
		this->grid.push_back(a_row);
	}
}

