#pragma once

#include <string>
#include <SDL.h>

class SDLppWindow
{
	public:
		SDLppWindow(const std::string& title, int width, int height, Uint32 flags = 0);
		SDLppWindow(const std::string& title, int x, int y, int width, int height, Uint32 flags = 0);
		SDLppWindow(const SDLppWindow&) = delete; // constructeur par copie
		~SDLppWindow();

		SDL_Window* GetHandle();

		SDLppWindow& operator=(const SDLppWindow&) = delete; // opérateur d'affectation par copie

	private:
		SDL_Window* m_window;
};
