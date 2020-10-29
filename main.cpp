#include <iostream>
#include <SFML/Graphics.hpp>
#include <string>

// #include "ChessPiece.h"
#include "Board.h"
#include "ResourceHolder.h"
using namespace std;

namespace Textures
{
	enum ID
	{
		black_king,
		black_queen,
		black_bishop,
		black_knight,
		black_rook,
		black_pawn,
		white_king,
		white_queen,
		white_bishop,
		white_knight,
		white_rook,
		white_pawn,
	};
}

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

		sprite_map.insert(pair<string, sf::Sprite>(white_pieces[i], textures.get(white_pieces[i])));
		sprite_map.insert(pair<string, sf::Sprite>(black_pieces[i], textures.get(black_pieces[i])));
	}

	// load board
	Board board = Board();

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

		sprite_map["white_pawn"].setPosition(200, 200);
		window.draw(sprite_map["white_pawn"]);

		sprite_map["white_pawn"].setPosition(500, 200);
		window.draw(sprite_map["white_pawn"]);

		window.draw(sprite_map["white_queen"]);

		// std::map<string, ChessPiece>::iterator it;
		// for(it = board.black_pieces.begin(); it != board.black_pieces.end(); it++)
		// {
			
		//     window.draw()
		// }

		// if(it != board.black_pieces.end()){
			// cout << it.pos.x << " " << it.pos.y << endl;
			// (*it)
			// window.draw(board.black_pieces.find("black_knight")->second.sprite);
		// }
		// else{
		//     cout << "oops" << endl;
		// }
		// window.draw(board.black_pieces[0].sprite);
	// this->black_pieces.insert(pair<string, ChessPiece>("black_knight", black_knight));

		// for(int i = 0; i< board.black_pieces.size(); i++){
		//     sf::Sprite temp = board.black_pieces[0].sprite;
		//     window.draw(temp);
			// window.draw(board.black_pieces[0].sprite);
		// }
		// ChessPiece black_knight = ChessPiece("assets/black_knight.png", 0, 3, 4);
		// window.draw(black_knight.sprite);


        // end the current frame
        window.display();
    }

    return 0;
}
