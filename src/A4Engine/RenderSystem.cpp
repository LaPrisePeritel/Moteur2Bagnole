#include <A4Engine/RenderSystem.hpp>

void RenderSystem::Render(entt::registry& registry, SDLppRenderer& renderer)
{
	auto view = registry.view<Transform, Sprite>();
	for (entt::entity entity : view)
	{
		auto& entityPos = view.get<Transform>(entity);
		auto& entityDrawable = view.get<Sprite>(entity);

		entityDrawable.Draw(renderer, entityPos);
	}
}
