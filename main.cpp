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
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	// create a central resource manager
	ResourceHolder<sf::Texture, Textures::ID> textures;

	textures.load(Textures::black_king, "assets/black_king.png");
	textures.load(Textures::black_queen, "assets/black_queen.png");
	textures.load(Textures::black_bishop, "assets/black_bishop.png");
	textures.load(Textures::black_knight, "assets/black_knight.png");
	textures.load(Textures::black_rook, "assets/black_rook.png");
	textures.load(Textures::black_pawn, "assets/black_pawn.png");

	textures.load(Textures::white_king, "assets/white_king.png");
	textures.load(Textures::white_queen, "assets/white_queen.png");
	textures.load(Textures::white_bishop, "assets/white_bishop.png");
	textures.load(Textures::white_knight, "assets/white_knight.png");
	textures.load(Textures::white_rook, "assets/white_rook.png");
	textures.load(Textures::white_pawn, "assets/white_pawn.png");

	sf::Sprite black_king(textures.get(Textures::black_king));
	sf::Sprite black_queen(textures.get(Textures::black_queen));
	sf::Sprite black_bishop(textures.get(Textures::black_bishop));
	sf::Sprite black_knight(textures.get(Textures::black_knight));
	sf::Sprite black_rook(textures.get(Textures::black_rook));
	sf::Sprite black_pawn(textures.get(Textures::black_pawn));

	sf::Sprite white_king(textures.get(Textures::white_king));
	sf::Sprite white_queen(textures.get(Textures::white_queen));
	sf::Sprite white_bishop(textures.get(Textures::white_bishop));
	sf::Sprite white_knight(textures.get(Textures::white_knight));
	sf::Sprite white_rook(textures.get(Textures::white_rook));
	sf::Sprite white_pawn(textures.get(Textures::white_pawn));

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

		black_pawn.setPosition(200, 200);
		window.draw(black_pawn);

		black_pawn.setPosition(500, 200);
		window.draw(black_pawn);

		window.draw(black_queen);

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
