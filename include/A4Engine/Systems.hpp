#pragma once

#include <A4Engine/Export.hpp>
#include <entt/entt.hpp>
#include <A4Engine/SDLppRenderer.hpp>

class SDLppTexture;

class A4ENGINE_API Systems
{
public:
	Systems() = default;
	~Systems() = default;

	static void RenderSystem(entt::registry& registry, SDLppRenderer& renderer);
	static void VelocitySystem(entt::registry& registry, float elapsedTime);
};