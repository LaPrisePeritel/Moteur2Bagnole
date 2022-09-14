#include "SDLppWindow.hpp"

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
