#pragma once

#include <vector>

using std::vector;

class Piece
{
	public:
		enum Type {
			KING,
			QUEEN,
			BISHOP,
			KNIGHT,
			ROOK,
			PAWN,
			EMPTY,
		} type;

		bool isBlack = false;

		vector<vector<Piece*>>* board;

		Piece(const Type& pieceType);
};
