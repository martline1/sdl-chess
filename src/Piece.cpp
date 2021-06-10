#include <SDL.h>
#include <iostream>

#include "../include/Piece.h"

using std::cout;
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
		case SDL_MOUSEBUTTONDOWN:
			movingPiece = true;
			break;
		case SDL_MOUSEBUTTONUP:
			movingPiece = false;
			break;
		default:
			break;
	}
}

void Piece::render() {
	// Don't render if is an empty piece
	if (type == Piece::Type::EMPTY) {
		movingPiece = false;
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

		cout << "x: " << mouseX << ", y: " << mouseY << endl;

		SDL_Rect destinationMouse;
		destination.x = squareSize * mouseX;
		destination.y = squareSize * mouseY;
		destination.w = squareSize;
		destination.h = squareSize;

		SDL_RenderCopy(game->renderer, piecesTexture, &source, &destinationMouse);

		SDL_SetTextureAlphaMod(piecesTexture, 255);
	}
}
