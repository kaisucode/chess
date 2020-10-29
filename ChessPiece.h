struct Position{
	int x;
	int y;
};

class ChessPiece{
	public: 
		Position pos;
		int player;
		ChessPiece(int player, int x, int y);
};
