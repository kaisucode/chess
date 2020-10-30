#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include "constants.h"
#include "Board.h"
#include "ResourceHolder.h"
using namespace std;

vector<string> generate_chess_piece_names(string color)
{
	vector<string> chess_piece_names = {"king", "queen", "bishop", "knight", "rook", "pawn"};
	vector<string> new_vector;
	for(int i = 0; i < NUM_OF_PIECE_TYPES; i++){
		string new_name = color + chess_piece_names[i];
		new_vector.push_back(new_name);
	}
	return new_vector;
}

map<string, sf::Sprite> generate_sprite_map(ResourceHolder<sf::Texture, string> &textures, vector<string> white_pieces, vector<string> black_pieces){
	std::map<string, sf::Sprite> sprite_map;
	for(int i = 0; i < NUM_OF_PIECE_TYPES; i++)
	{
		textures.load(white_pieces[i], "assets/" + white_pieces[i] + ".png");
		textures.load(black_pieces[i], "assets/" + black_pieces[i] + ".png");
		sprite_map.insert(pair<string, sf::Sprite>(white_pieces[i], textures.get(white_pieces[i])));
		sprite_map.insert(pair<string, sf::Sprite>(black_pieces[i], textures.get(black_pieces[i])));
		sprite_map[white_pieces[i]].setScale(SCALE, SCALE);
		sprite_map[black_pieces[i]].setScale(SCALE, SCALE);
	}
	return sprite_map;
}

void renderPieces(sf::RenderWindow &window, Board &board, map<string, sf::Sprite> &sprite_map){
	for(int row = 0; row < 8; row++){
		for(int col = 0; col < 8; col++){
			if(board.grid[row][col].is_occupied)
			{
				string name = board.grid[row][col].name;

				int col_spacing = SCALE * (col * CELL_SIZE + MARGINS + 3);
				int row_spacing = SCALE * (row * CELL_SIZE + MARGINS + 3);

				sprite_map[name].setPosition(col_spacing, row_spacing);
				window.draw(sprite_map[name]);
			}
		}
	}
}

sf::Vector2i coor_to_cells(sf::Vector2i mousePos){
	int row = ((mousePos.y / SCALE) - MARGINS) / CELL_SIZE;
	int col = ((mousePos.x / SCALE) - MARGINS) / CELL_SIZE;
	return sf::Vector2i(col, row);
}

sf::Vector2f cell_to_coor(sf::Vector2i cell){
	float row_cell = SCALE * (cell.y * CELL_SIZE + MARGINS);
	float col_cell = SCALE * (cell.x * CELL_SIZE + MARGINS);
	return sf::Vector2f(col_cell, row_cell);
}

void renderOutline(sf::RenderWindow &window, sf::RectangleShape rect, sf::Vector2i cell)
{
	sf::Vector2f coordinates = cell_to_coor(cell);
	rect.setPosition(coordinates);
	window.draw(rect);
}

sf::RectangleShape generate_outline(sf::Color color)
{
	sf::RectangleShape rect(sf::Vector2f(CELL_SIZE * SCALE, CELL_SIZE * SCALE));
	rect.setFillColor(sf::Color::Transparent);
	rect.setOutlineThickness(4);
	rect.setOutlineColor(color);
	return rect;
}

int main()
{
	vector<string> white_pieces = generate_chess_piece_names("white_");
	vector<string> black_pieces = generate_chess_piece_names("black_");

    // create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	// create a central resource manager
	ResourceHolder<sf::Texture, string> textures;
	std::map<string, sf::Sprite> sprite_map = generate_sprite_map(textures, white_pieces, black_pieces);

	// create board
	Board board = Board();

	sf::RectangleShape cursor = generate_outline(sf::Color(100, 250, 50));
	sf::RectangleShape src_highlight = generate_outline(sf::Color(255, 0, 0));

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
		renderPieces(window, board, sprite_map);


		if(board.srcIsSet){
			renderOutline(window, src_highlight, board.src);
			if(board.isValidMove(coor_to_cells(sf::Mouse::getPosition(window)))){
				// cursor.setOutlineColor(sf::Color(255, 0, 0));
				renderOutline(window, cursor, coor_to_cells(sf::Mouse::getPosition(window)));
			}
		}
		else
			renderOutline(window, cursor, coor_to_cells(sf::Mouse::getPosition(window)));

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			sf::Vector2i mouseCells = coor_to_cells(sf::Mouse::getPosition(window));
			board.setSrc(mouseCells);
			cout << "row: " << mouseCells.y << "\ncol: " << mouseCells.x << endl;
		}

        // end the current frame
        window.display();
    }

    return 0;
}
