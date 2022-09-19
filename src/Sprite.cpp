#include "Sprite.hpp"
#include "SDLppRenderer.hpp"
#include "SDLppTexture.hpp"

Sprite::Sprite(const SDLppTexture& texture) :
Sprite(texture, texture.GetRect())
{
}

Sprite::Sprite(const SDLppTexture& texture, const SDL_Rect& rect) :
m_texture(texture),
m_rect(rect)
{
}

void Sprite::Draw(SDLppRenderer& renderer, int x, int y)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = m_rect.w;
	dest.h = m_rect.h;

	renderer.RenderCopy(m_texture, m_rect, dest);
}
