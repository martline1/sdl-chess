#include <SDL.h>
#include <math.h>
#include <string>
#include <iostream>

#include "../include/Piece.h"

using std::cout;
using std::string;
using std::endl;

Piece::Piece(Game* _game, SDL_Texture* _piecesTexture, const Piece::Type& pieceType, const vector<vector<int>>* board, bool isBlack, int _positionX, int _positionY)
	: game(_game),
	piecesTexture(_piecesTexture),
	board(board),
	type(pieceType),
	isBlack(isBlack),
	positionX(_positionX),
	positionY(_positionY)
{
	this->squareSize = game->width / 8;
}

void Piece::handleEvent(SDL_Event* evnt) {
	switch (evnt->type)
	{
		case SDL_MOUSEBUTTONDOWN: {
			int mouseX, mouseY;

			SDL_GetMouseState(&mouseX, &mouseY);

			bool intersectX = mouseX > squareSize * positionX && mouseX < squareSize * (positionX + 1);
			bool intersectY = mouseY > squareSize * positionY && mouseY < squareSize * (positionY + 1);

			// If the mouse is pressed over this piece, then we're moving the piece
			movingPiece = intersectX && intersectY;
			break;
		}
		case SDL_MOUSEBUTTONUP: {
			if (movingPiece) {
				requestNewPosition = true;
			}

			break;
		}
		default:
			break;
	}
}

void Piece::render() {
	// Don't render if it's an empty piece
	if (type == Piece::Type::EMPTY) {
		movingPiece        = false;
		requestNewPosition = false;
		return;
	}

	int sourceX = type - 1;

	SDL_Rect source;
	source.x = pieceWidth * sourceX;
	source.y = pieceHeight * (isBlack ? 0 : 1);
	source.w = pieceWidth;
	source.h = pieceHeight;

	SDL_Rect destination;
	destination.x = squareSize * positionX;
	destination.y = squareSize * positionY;
	destination.w = squareSize;
	destination.h = squareSize;

	SDL_RenderCopy(game->renderer, piecesTexture, &source, &destination);

	if (movingPiece) {
		SDL_SetTextureAlphaMod(piecesTexture, 120);

		int mouseX, mouseY;

		SDL_GetMouseState(&mouseX, &mouseY);

		int newPositionX = std::ceil(mouseX / squareSize), newPositionY = std::ceil(mouseY / squareSize);

		SDL_Rect destinationMouse;
		destinationMouse.x = squareSize * newPositionX;
		destinationMouse.y = squareSize * newPositionY;
		destinationMouse.w = squareSize;
		destinationMouse.h = squareSize;

		SDL_RenderCopy(game->renderer, piecesTexture, &source, &destinationMouse);

		SDL_SetTextureAlphaMod(piecesTexture, 255);

		if (requestNewPosition) {
			positionX = newPositionX;
			positionY = newPositionY;

			movingPiece        = false;
			requestNewPosition = false;
		}
	}
	else {
		movingPiece        = false;
		requestNewPosition = false;
	}
}
