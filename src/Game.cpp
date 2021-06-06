#include <iostream>
#include <SDL.h>
#include <SDL_image.h>

#include "..\include\Game.h"

using std::cout;
using std::endl;

Game::Game(const char* title, int _width, int _height)
    : window(nullptr),
    renderer(nullptr),
    width(_width),
    height(_height)
{
    if (SDL_Init(SDL_INIT_EVERYTHING) < 0) {
        cout << "SDL Couldn't init " << SDL_GetError() << endl;
        this->running = false;
    }

    // load support for PNG image format
    int flags   = IMG_INIT_PNG;
    int initted = IMG_Init(flags);

    if ((initted & flags) != flags) {
        cout << "Couldn't init sdl image " << IMG_GetError() << endl;
        this->running = false;
    }

    window = SDL_CreateWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, SDL_WINDOW_SHOWN);
    renderer = SDL_CreateRenderer(window, -1, SDL_RENDERER_ACCELERATED);

    SDL_SetRenderDrawColor(renderer, 0, 0, 0, 255);
}

Game::~Game()
{
    SDL_DestroyWindow(window);
    SDL_DestroyRenderer(renderer);
    SDL_Quit();
}

SDL_Texture* Game::loadTexture(const char* filePath)
{
    SDL_Texture* texture = NULL;
    texture = IMG_LoadTexture(renderer, filePath);

    if (texture == NULL) {
        cout << "Couldn't load texture " << SDL_GetError() << endl;
        this->running = false;
    }

    return texture;
}
