#pragma once

#include <SDL.h>

class SDLppWindow;

class SDLppRenderer
{
	public:
		SDLppRenderer(SDLppWindow& window);
		~SDLppRenderer();

		void Clear();
		void Present();
		void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

	private:
		SDL_Renderer* m_renderer;
};