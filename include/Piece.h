#pragma once

#include <SDL.h>
#include <SDL_image.h>
#include <vector>

#include "../include/Game.h"

using std::vector;

class Piece
{
	public:
		enum Type {
			ROOK = 1,
			KNIGHT = 2,
			BISHOP = 3,
			QUEEN = 4,
			KING = 5,
			PAWN = 6,
			EMPTY = 0,
		} type;

		bool isBlack = false;

		const vector<vector<int>>* board;

		Piece(Game* _game, SDL_Texture* _piecesTexture, const Piece::Type& pieceType, const vector<vector<int>>* board, bool isBlack, int _positionX, int _positionY);

		void handleEvent(SDL_Event* evnt);
		void render();

	private:
		bool movingPiece = false;

		int positionX;
		int positionY;

		const int pieceWidth = 340 / 6;
		const int pieceHeight = (120 / 2) - 1;

		int squareSize;

		Game* game;
		SDL_Texture* piecesTexture;
};
