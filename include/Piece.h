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

		const vector<vector<Piece*>>* board;

		Piece(const Piece::Type& pieceType, const vector<vector<Piece*>>* board, bool isBlack);
};
