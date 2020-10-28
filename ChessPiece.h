struct Position{
	int x;
	int y;
};

class ChessPiece{
	public: 
		sf::Sprite sprite;
		sf::Texture texture;
		Position pos;
		int player;
		ChessPiece(std::string img_url, int player, int x, int y);
};
