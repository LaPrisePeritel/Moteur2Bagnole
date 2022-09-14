#include "SDLppRenderer.hpp"
#include "SDLppWindow.hpp"

SDLppRenderer::SDLppRenderer(SDLppWindow& window)
{
	m_renderer = SDL_CreateRenderer(window.GetHandle(), 0, 0);
}

SDLppRenderer::~SDLppRenderer()
{
	SDL_DestroyRenderer(m_renderer);
}

void SDLppRenderer::Clear()
{
	SDL_RenderClear(m_renderer);
}

SDL_Renderer* SDLppRenderer::GetHandle()
{
	return m_renderer;
}

void SDLppRenderer::Present()
{
	SDL_RenderPresent(m_renderer);
}

void SDLppRenderer::SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a)
{
	SDL_SetRenderDrawColor(m_renderer, r, g, b, a);
}
