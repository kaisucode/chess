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

// void load_chess_pieces(ResourceHolder<sf::Texture, string> textures, vector<string> white_pieces, vector<string> black_pieces){
//     return;
// }

int main()
{
	vector<string> white_pieces = generate_chess_piece_names("white_");
	vector<string> black_pieces = generate_chess_piece_names("black_");

    // create the window
	sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	// create a central resource manager
	ResourceHolder<sf::Texture, string> textures;
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

	// load board
	Board board = Board();


	sf::RectangleShape rectangle(sf::Vector2f(CELL_SIZE * SCALE, CELL_SIZE * SCALE));
	rectangle.setFillColor(sf::Color::Transparent);
	rectangle.setOutlineThickness(4);
	rectangle.setOutlineColor(sf::Color(100, 250, 50));

	// rectangle.setOutlineThickness(0);
	// rectangle.setFillColor(sf::Color(100, 250, 50));

	int foo = SCALE * (3 * CELL_SIZE + MARGINS);
	rectangle.setPosition(foo, foo);

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

					int col_spacing = SCALE * (col * CELL_SIZE + MARGINS + 3);
					int row_spacing = SCALE * (row * CELL_SIZE + MARGINS + 3);

					sprite_map[name].setPosition(col_spacing, row_spacing);
					window.draw(sprite_map[name]);
				}
			}
		}

		window.draw(rectangle);

		if (sf::Mouse::isButtonPressed(sf::Mouse::Left)){
			sf::Vector2i mousePos = sf::Mouse::getPosition(window);
			cout << "x: " << mousePos.x << "\ny: " << mousePos.y << endl;

			int x_coor = (mousePos.x - MARGINS) / (SCALE * CELL_SIZE);
			int y_coor = (mousePos.y - MARGINS) / (SCALE * CELL_SIZE);
			cout << "x_coor: " << x_coor << "\ny_coor: " << y_coor << endl;
		}

		// if (sprite.getPosition().x <= Mouse::getPosition().x + 100 && sprite.getPosition().x >= Mouse::getPosition().x - 100 && sprite.getPosition().y <= Mouse::getPosition().y +100 && sprite.getPosition().y >= Mouse::getPosition -100)



        // end the current frame
        window.display();
    }

    return 0;
}
