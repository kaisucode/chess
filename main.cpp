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
		black_pawn,
	};
}

int main()
{
    // create the window
    sf::RenderWindow window(sf::VideoMode(800, 600), "My window");

	// load board
	Board board = Board();

	ResourceHolder<sf::Texture, Textures::ID> textures;
	textures.load(Textures::black_pawn, "assets/black_pawn.png");
	sf::Sprite black_pawn(textures.get(Textures::black_pawn));
	black_pawn.setPosition(200, 200);

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
		window.draw(black_pawn);

		// std::map<string, ChessPiece>::iterator it = board.black_pieces.find("black_knight");

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
