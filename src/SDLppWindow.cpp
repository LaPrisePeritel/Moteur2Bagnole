#include "SDLppWindow.hpp"

SDLppWindow::SDLppWindow(const std::string& title, int width, int height, Uint32 flags) :
SDLppWindow(title, SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, width, height, flags)
{
}

SDLppWindow::SDLppWindow(const std::string& title, int x, int y, int width, int height, Uint32 flags)
{
	m_window = SDL_CreateWindow(title.c_str(), x, y, width, height, flags);
}

SDLppWindow::~SDLppWindow()
{
	SDL_DestroyWindow(m_window);
}

SDL_Window* SDLppWindow::GetHandle()
{
	return m_window;
}
