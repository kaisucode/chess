class ChessPiece{
	public: 
		bool isOccupied;
		int player;
		std::string name;
		ChessPiece();
		ChessPiece(int player, std::string name);
};
