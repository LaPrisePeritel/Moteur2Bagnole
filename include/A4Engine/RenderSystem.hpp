#pragma once

#include <A4Engine/Export.hpp>
#include <entt/entt.hpp>
#include <A4Engine/SDLppRenderer.hpp>
#include <SDL.h>
#include <A4Engine/Transform.hpp>
#include <A4Engine/Sprite.hpp>

class SDLppTexture;

class A4ENGINE_API RenderSystem
{
public:
	RenderSystem() = default;
	~RenderSystem() = default;

	static void Render(entt::registry& registry, SDLppRenderer& renderer);
};