#include <A4Engine/Systems.hpp>
#include <A4Engine/Transform.hpp>
#include <A4Engine/Sprite.hpp>
#include <A4Engine/Components.hpp>

void Systems::RenderSystem(entt::registry& registry, SDLppRenderer& renderer)
{
	auto view = registry.view<Transform, Sprite>();
	auto cameraView = registry.view<Transform, CameraComponent>();

	for (entt::entity entity : view)
	{
		auto& entityPos = view.get<Transform>(entity);
		auto& entityDrawable = view.get<Sprite>(entity);

		entityDrawable.Draw(renderer, entityPos);
	}

	for (entt::entity entity : cameraView)
	{
		auto& entityPos = cameraView.get<Transform>(entity);
		cameraView.get<CameraComponent>(entity);
		// Camera System
	}
}

void Systems::VelocitySystem(entt::registry& registry, float elapsedTime)
{
	auto view = registry.view<Transform, VelocityComponent>();
	for (entt::entity entity : view)
	{
		auto& entityPos = view.get<Transform>(entity);
		auto& entityVel = view.get<VelocityComponent>(entity);

		entityPos.Translate(Vector2f(entityVel.x * elapsedTime, entityVel.y * elapsedTime));
	}
}
