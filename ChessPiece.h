class ChessPiece{
	public: 
		bool is_occupied;
		int player;
		std::string name;
		ChessPiece();
		ChessPiece(int player, std::string name);
};
