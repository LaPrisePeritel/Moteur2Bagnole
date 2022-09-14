#pragma once

#include <SDL.h>

class SDLppWindow;

class SDLppRenderer
{
	public:
		SDLppRenderer(SDLppWindow& window);
		SDLppRenderer(const SDLppRenderer&) = delete; // constructeur par copie
		~SDLppRenderer();

		void Clear();
		SDL_Renderer* GetHandle();
		void Present();
		void SetDrawColor(Uint8 r, Uint8 g, Uint8 b, Uint8 a);

		SDLppRenderer& operator=(const SDLppRenderer&) = delete; // opérateur d'assignation par copie

	private:
		SDL_Renderer* m_renderer;
};