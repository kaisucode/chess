#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include "constants.h"
#include "Board.h"
#include "ResourceHolder.h"
using namespace std;

vector<string> generateChessPieceNames(string color)
{
	vector<string> chessPieceNames = {"king", "queen", "bishop", "knight", "rook", "pawn"};
	vector<string> newVector;
	for(int i = 0; i < NUM_OF_PIECE_TYPES; i++)
		newVector.push_back(color + chessPieceNames[i]);
	return newVector;
}

map<string, sf::Sprite> generateSpriteMap(ResourceHolder<sf::Texture, string> &textures, vector<string> whitePieces, vector<string> blackPieces){
	std::map<string, sf::Sprite> spriteMap;
	for(int i = 0; i < NUM_OF_PIECE_TYPES; i++)
	{
		textures.load(whitePieces[i], "assets/" + whitePieces[i] + ".png");
		textures.load(blackPieces[i], "assets/" + blackPieces[i] + ".png");
		spriteMap.insert(pair<string, sf::Sprite>(whitePieces[i], textures.get(whitePieces[i])));
		spriteMap.insert(pair<string, sf::Sprite>(blackPieces[i], textures.get(blackPieces[i])));
		spriteMap[whitePieces[i]].setScale(SCALE, SCALE);
		spriteMap[blackPieces[i]].setScale(SCALE, SCALE);
	}
	return spriteMap;
}

void renderPieces(sf::RenderWindow &window, Board &board, map<string, sf::Sprite> &spriteMap){
	for(int row = 0; row < 8; row++){
		for(int col = 0; col < 8; col++){
			if(board.grid[row][col].isOccupied)
			{
				string name = board.grid[row][col].name;

				int colSpacing = SCALE * (col * CELL_SIZE + MARGINS + 3);
				int rowSpacing = SCALE * (row * CELL_SIZE + MARGINS + 3);

				spriteMap[name].setPosition(colSpacing, rowSpacing);
				window.draw(spriteMap[name]);
			}
		}
	}
}

sf::Vector2i coorToCells(sf::Vector2i mousePos){
	int row = ((mousePos.y / SCALE) - MARGINS) / CELL_SIZE;
	int col = ((mousePos.x / SCALE) - MARGINS) / CELL_SIZE;
	return sf::Vector2i(col, row);
}

sf::Vector2f cellToCoor(sf::Vector2i cell){
	float row = SCALE * (cell.y * CELL_SIZE + MARGINS);
	float col = SCALE * (cell.x * CELL_SIZE + MARGINS);
	return sf::Vector2f(col, row);
}

void renderOutline(sf::RenderWindow &window, sf::RectangleShape rect, sf::Vector2i cell)
{
	sf::Vector2f coordinates = cellToCoor(cell);
	rect.setPosition(coordinates);
	window.draw(rect);
}

sf::RectangleShape generateOutline(sf::Color color)
{
	sf::RectangleShape rect(sf::Vector2f(CELL_SIZE * SCALE, CELL_SIZE * SCALE));
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(4);
	rect.setOutlineColor(color);
	return rect;
}

int main()
{
	vector<string> whitePieces = generateChessPieceNames("white_");
	vector<string> blackPieces = generateChessPieceNames("black_");

    // create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	// create a central resource manager
	ResourceHolder<sf::Texture, string> textures;
	std::map<string, sf::Sprite> spriteMap = generateSpriteMap(textures, whitePieces, blackPieces);

	// create board
	Board board = Board();

	sf::RectangleShape cursor = generateOutline(sf::Color(100, 250, 50));
	sf::RectangleShape srcHighlight = generateOutline(sf::Color(255, 0, 0));

    // run the program as long as the window is open
    while (window.isOpen())
    {
        sf::Event event;
        while (window.pollEvent(event))
        {
            // "close requested" event: we close the window
            if (event.type == sf::Event::Closed)
                window.close();
        }

        // clear the window with black color
        window.clear(sf::Color::Black);

        // draw everything here...
		window.draw(board.sprite);
		renderPieces(window, board, spriteMap);

		if(board.srcIsSet){
			renderOutline(window, srcHighlight, board.src);
			sf::Vector2i mouseCell = coorToCells(sf::Mouse::getPosition(window));

			if(board.isValidMove(mouseCell)){
				renderOutline(window, cursor, coorToCells(sf::Mouse::getPosition(window)));

				if (sf::Mouse::isButtonPressed(sf::Mouse::Right)){
					board.executeMove(mouseCell);
				}
			}
		}
		else
			renderOutline(window, cursor, coorToCells(sf::Mouse::getPosition(window)));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			board.setSrc(coorToCells(sf::Mouse::getPosition(window)));
			// cout << "row: " << mouseCells.y << "\ncol: " << mouseCells.x << endl;
		}

        // end the current frame
        window.display();
    }

    return 0;
}
