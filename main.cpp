#include <SDL.h>
#include <SDL_image.h>
#include <iostream>
#include <vector>

#include "include/Game.h"
#include "include/Piece.h"

using namespace std;

int main(int argc, char** argv) {
	Game game("Chess", 600, 600);

	SDL_Texture* board  = game.loadTexture("resources/board0.png");
	SDL_Texture* pieces = game.loadTexture("resources/figures.png");

	vector<vector<Piece*>> board = {
		{ Piece() },
	};

	/*const int piecesWidth  = 340;
	const int piecesHeight = 120;

	SDL_Rect knightSource;
	knightSource.x = (piecesWidth / 6) * 1;
	knightSource.y = (piecesHeight / 2) * 0;
	knightSource.w = piecesWidth / 6;
	knightSource.h = piecesHeight / 2;

	SDL_Rect knightDestination;
	knightDestination.x = (game.width / 8) * 0;
	knightDestination.y = (game.width / 8) * 0;
	knightDestination.w = game.width / 8;
	knightDestination.h = game.height / 8;*/

	SDL_Event event;
	while (game.running) {
		while (SDL_PollEvent(&event)) {
			switch (event.type)
			{
				case SDL_QUIT:
					game.running = false;
					break;
				case SDL_MOUSEBUTTONDOWN:
					cout << "Pressed!" << endl;
					break;
				case SDL_MOUSEBUTTONUP:
					cout << "Released!" << endl;
					break;
				default:
					break;
			}
		}

		SDL_RenderClear(game.renderer);

		SDL_RenderCopy(game.renderer, board, NULL, NULL);

		SDL_RenderCopy(game.renderer, pieces, &knightSource, &knightDestination);

		SDL_RenderPresent(game.renderer);
	}

	return 0;
}
