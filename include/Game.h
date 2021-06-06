#pragma once

#include <SDL.h>
#include <functional>

using std::function;

class Game
{
	public:
		int width;
		int height;
		bool running = true;
		SDL_Window* window;
		SDL_Renderer* renderer;

		Game(const char* title, int _width, int _height);
		~Game();

		SDL_Texture* loadTexture(const char* filePath);
};
