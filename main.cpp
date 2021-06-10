#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>
#include <cstdlib>

#include "include/Game.h"
#include "include/Piece.h"

using namespace std;

int main(int argc, char** argv) {
	Game game("Chess", 600, 600);

	SDL_Texture* boardTexture  = game.loadTexture("resources/board0.png");
	SDL_Texture* piecesTexture = game.loadTexture("resources/figures.png");

	vector<vector<int>> board = {
		{ -Piece::ROOK, -Piece::KNIGHT, -Piece::BISHOP, -Piece::QUEEN, -Piece::KING, -Piece::BISHOP, -Piece::KNIGHT, -Piece::ROOK },
		{ -Piece::PAWN, -Piece::PAWN, -Piece::PAWN, -Piece::PAWN, -Piece::PAWN, -Piece::PAWN, -Piece::PAWN, -Piece::PAWN, },
		{ Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, },
		{ Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, },
		{ Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, },
		{ Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, Piece::EMPTY, },
		{ Piece::PAWN, Piece::PAWN, Piece::PAWN, Piece::PAWN, Piece::PAWN, Piece::PAWN, Piece::PAWN, Piece::PAWN, },
		{ Piece::ROOK, Piece::KNIGHT, Piece::BISHOP, Piece::QUEEN, Piece::KING, Piece::BISHOP, Piece::KNIGHT, Piece::ROOK },
	};

	vector<Piece> pieces;

	for (int y = 0; y < 8; y++) {
		for (int x = 0; x < 8; x++) {
			int pieceType = board.at(y).at(x);

			// If there's a non empty
			if (pieceType != Piece::EMPTY) {
				bool isBlack = pieceType < 0;
				Piece::Type convertedPieceType = static_cast<Piece::Type>(abs(pieceType));

				pieces.push_back(Piece(&game, piecesTexture, convertedPieceType, &board, isBlack, x, y));
			}
		}
	}

	SDL_Event event;
	while (game.running) {
		// Clear The Screen
		SDL_SetRenderDrawColor(game.renderer, 0, 0, 0, 255);
		SDL_RenderClear(game.renderer);

		// Handle Events
		while (SDL_PollEvent(&event)) {
			if (event.type == SDL_QUIT) {
				game.running = false;
			}

			for (Piece& piece : pieces) {
				piece.handleEvent(&event);
			}
		}

		// Render the board
		SDL_RenderCopy(game.renderer, boardTexture, NULL, NULL);

		// Render the pieces
		for (Piece& piece : pieces) {
			piece.render();
		}

		SDL_RenderPresent(game.renderer);
	}

	return 0;
}
