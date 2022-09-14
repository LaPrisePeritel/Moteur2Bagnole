#pragma once

#include <SDL.h>
#include <string>

class SDLppRenderer;

class SDLppTexture
{
	public:
		SDLppTexture(const SDLppTexture&) = delete; // constructeur par copie
		SDLppTexture(SDLppTexture&& texture); // constructeur par mouvement
		~SDLppTexture();

		SDL_Texture* GetHandle();

		SDLppTexture& operator=(const SDLppTexture&) = delete; // opérateur d'assignation par copie
		//SDLppTexture& operator=(SDLppTexture&&); // opérateur d'assignation par mouvement

		static SDLppTexture LoadFromFile(SDLppRenderer& renderer, const std::string& filepath);

	private:
		SDLppTexture(SDL_Texture* texture);

		SDL_Texture* m_texture;
};