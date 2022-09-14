#pragma once

#include <string>
#include <SDL.h>

class SDLppWindow
{
	public:
		SDLppWindow(const std::string& title, int x, int y, int width, int height, Uint32 flags);
		~SDLppWindow();

		SDL_Window* GetHandle();

	private:
		SDL_Window* m_window;
};