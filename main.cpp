#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

#include "constants.h"
#include "Board.h"
#include "ResourceHolder.h"
using namespace std;

int main()
{
	vector<string> chess_piece_names = {"king", "queen", "bishop", "knight", "rook", "pawn"};
	vector<string> white_pieces, black_pieces;
	for(int i = 0; i < chess_piece_names.size(); i++)
	{
		string white_new_name = "white_" + chess_piece_names[i];
		string black_new_name = "black_" + chess_piece_names[i];
		white_pieces.push_back(white_new_name);
		black_pieces.push_back(black_new_name);
	}

    // create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	// create a central resource manager
	ResourceHolder<sf::Texture, string> textures;
	std::map<string, sf::Sprite> sprite_map;

	for(int i = 0; i < chess_piece_names.size(); i++)
	{
		textures.load(white_pieces[i], "assets/" + white_pieces[i] + ".png");
		textures.load(black_pieces[i], "assets/" + black_pieces[i] + ".png");

		// textures.get(white_pieces[i]).setScale(3, 3);
		// textures.get(black_pieces[i]).setScale(3, 3);

		sprite_map.insert(pair<string, sf::Sprite>(white_pieces[i], textures.get(white_pieces[i])));
		sprite_map.insert(pair<string, sf::Sprite>(black_pieces[i], textures.get(black_pieces[i])));

		sprite_map[white_pieces[i]].setScale(SCALE, SCALE);
		sprite_map[black_pieces[i]].setScale(SCALE, SCALE);
	}

	// load board
	Board board = Board();


	sf::RectangleShape rectangle(sf::Vector2f(22*SCALE, 22*SCALE));
	rectangle.setFillColor(sf::Color(100, 250, 50));
	rectangle.setPosition(6, 6);

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
		for(int row = 0; row < 8; row++){
			for(int col = 0; col < 8; col++){
				if(board.grid[row][col].is_occupied)
				{
					string name = board.grid[row][col].name;

					int col_spacing = MARGINS + SCALE * (col*22 + 3);
					int row_spacing = MARGINS + SCALE * (row*22 + 3);

					sprite_map[name].setPosition(col_spacing, row_spacing);
					window.draw(sprite_map[name]);
				}
			}
		}

		window.draw(rectangle);
        // end the current frame
        window.display();
    }

    return 0;
}
