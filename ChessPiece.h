struct Position{
	int x;
	int y;
};

class ChessPiece{
	public: 
		bool is_occupied;
		int player;
		std::string piece;
		ChessPiece();
		ChessPiece(int player, std::string piece);
};
