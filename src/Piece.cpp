#include "../include/Piece.h"

Piece::Piece(const Piece::Type& pieceType, const vector<vector<Piece*>>* board, bool isBlack = false)
	: board(board),
	type(pieceType),
	isBlack(isBlack)
{

}


