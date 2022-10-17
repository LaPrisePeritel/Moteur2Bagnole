#include <A4Engine/Systems.hpp>
#include <A4Engine/Transform.hpp>
#include <A4Engine/Sprite.hpp>
#include <A4Engine/Components.hpp>

void Systems::RenderSystem(entt::registry& registry, SDLppRenderer& renderer)
{
	auto cameraView = registry.view<Transform, CameraComponent>();
	auto view = registry.view<Transform, Sprite>();

	Transform currentCameraTransform;

	for (entt::entity entity : cameraView)
	{
		auto& tranform = cameraView.get<Transform>(entity);
		currentCameraTransform = tranform;
	}

	for (entt::entity entity : view)
	{
		auto& transform = view.get<Transform>(entity);
		auto& sprite = view.get<Sprite>(entity);

		auto newPosition = transform.GetPosition() - currentCameraTransform.GetPosition();
		auto newScale = transform.GetScale() * currentCameraTransform.GetScale();
		auto newRotation = transform.GetRotation() - currentCameraTransform.GetRotation();

		Transform newTransform;
		newTransform.SetPosition(newPosition);
		newTransform.SetScale(newScale);
		newTransform.SetRotation(newRotation);

		sprite.Draw(renderer, newTransform);
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
