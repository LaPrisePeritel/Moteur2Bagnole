#include <A4Engine/Sprite.hpp>
#include <A4Engine/SDLppRenderer.hpp>
#include <A4Engine/SDLppTexture.hpp>

Sprite::Sprite(std::shared_ptr<const SDLppTexture> texture) :
Sprite(std::move(texture), texture->GetRect())
{
}

Sprite::Sprite(std::shared_ptr<const SDLppTexture> texture, const SDL_Rect& rect) :
m_texture(std::move(texture)),
m_rect(rect),
m_width(rect.w),
m_height(rect.h)
{
}

void Sprite::Draw(SDLppRenderer& renderer, int x, int y)
{
	SDL_Rect dest;
	dest.x = x;
	dest.y = y;
	dest.w = m_width;
	dest.h = m_height;

	renderer.RenderCopy(*m_texture, m_rect, dest);
}

int Sprite::GetHeight() const
{
	return m_height;
}

int Sprite::GetWidth() const
{
	return m_width;
}

void Sprite::Resize(int width, int height)
{
	m_width = width;
	m_height = height;
}

void Sprite::SetRect(SDL_Rect rect)
{
	m_rect = rect;
}
