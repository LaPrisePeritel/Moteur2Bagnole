#include <A4Engine/SDLpp.hpp>
#include <A4Engine/SDLppRenderer.hpp>
#include <A4Engine/SDLppWindow.hpp>
#include <A4Engine/ResourceManager.hpp>
#include <A4Engine/InputManager.hpp>
#include <entt/entt.hpp>
#include <A4Engine/Sprite.hpp>
#include <A4Engine/RigidBodyComponent.hpp>
#include <A4Engine/SpritesheetComponent.hpp>
#include <A4Engine/GraphicsComponent.hpp>
#include <A4Engine/CollisionShape.hpp>
#include <A4Engine/Transform.hpp>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>
#include <A4Engine/RenderSystem.hpp>
#include <A4Engine/CameraComponent.hpp>
#include <A4Engine/AnimationSystem.hpp>
#include <A4Engine/VelocitySystem.hpp>
#include <A4Engine/PhysicsSystem.hpp>
#include <dr_wav.h>
#include <A4Engine/AudioClip.hpp>
#include <A4Engine/AudioSystem.hpp>

void InitializeBasics(entt::registry& registry);
void InitializeInput();
void InitializeAudio();
entt::entity InitializePlayer(entt::registry& registry);
entt::entity InitializeCamera(entt::registry& registry);
entt::entity CreateBox(entt::registry& registry, std::shared_ptr<CollisionShape> shape);
void InitializeLevel(entt::registry& registry);
void HandleCameraMovement(entt::registry& registry, entt::entity camera, entt::entity player, float deltaTime);

struct InputComponent
{
	bool left = false;
	bool right = false;
	bool jump = false;
};

struct PlayerControlled {};

void PlayerControllerSystem(entt::registry& registry)
{
	auto view = registry.view<RigidBodyComponent, InputComponent>();
	for (entt::entity entity : view)
	{
		auto& entityInput = view.get<InputComponent>(entity);
		auto& entityPhysics = view.get<RigidBodyComponent>(entity);

		Vector2f velocity = Vector2f(0.f, 0.f);
		velocity.y = entityPhysics.GetLinearVelocity().y;

		if (entityInput.left)
			velocity.x -= 500.f;

		if (entityInput.right)
			velocity.x += 500.f;

		if (entityInput.jump && velocity.y < 1.f)
			velocity.y = -800.f;

		entityPhysics.SetLinearVelocity(velocity);
	}
}

void PlayerInputSystem(entt::registry& registry)
{
	auto view = registry.view<PlayerControlled, InputComponent>();
	for (entt::entity entity : view)
	{
		auto& entityInput = view.get<InputComponent>(entity);
		entityInput.left = InputManager::Instance().IsActive("MoveLeft");
		entityInput.right = InputManager::Instance().IsActive("MoveRight");
		entityInput.jump = InputManager::Instance().IsActive("Jump");
	}
}

int main() 
{
	SDLpp sdl;
	SDLppWindow window("Vesqui en folie !", 1920, 1200);
	SDLppRenderer renderer(window, "", SDL_RENDERER_PRESENTVSYNC);
	
	ResourceManager resourceManager(renderer);
	InputManager inputManager;
	entt::registry registry;

	AudioSystem audioSystem;
	audioSystem.SetGeneralGain(0.1f);

	RenderSystem renderSystem(renderer, registry);
	PhysicsSystem physicsSystem(registry);
	physicsSystem.SetGravity({ 0.f, 981.f });
	physicsSystem.SetDamping(0.9f);

	InitializeBasics(registry);
	entt::entity cameraEntity = InitializeCamera(registry);
	entt::entity player = InitializePlayer(registry);
	registry.get<RigidBodyComponent>(player).TeleportTo({ 150.f, 850.f });

	Uint64 lastUpdate = SDL_GetPerformanceCounter();

	bool isOpen = true;
	while (isOpen)
	{
		Uint64 now = SDL_GetPerformanceCounter();
		float deltaTime = (float)(now - lastUpdate) / SDL_GetPerformanceFrequency();
		lastUpdate = now;

		SDL_Event event;
		while (SDLpp::PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				isOpen = false;

			InputManager::Instance().HandleEvent(event);
		}

		renderer.SetDrawColor(101, 100, 124, 255);
		renderer.Clear();

		renderSystem.Update(deltaTime);
		physicsSystem.Update(deltaTime);

		PlayerInputSystem(registry);
		PlayerControllerSystem(registry);
		HandleCameraMovement(registry, cameraEntity, player, deltaTime);

		physicsSystem.DebugDraw(renderer, registry.get<Transform>(cameraEntity).GetTransformMatrix().Inverse());

		renderer.Present();
	}

	return 0;
}

void InitializeBasics(entt::registry& registry)
{
	InitializeInput();
	InitializeAudio();
	InitializeLevel(registry);
}

void InitializeInput() 
{
	InputManager::Instance().BindKeyPressed(SDLK_q, "MoveLeft");
	InputManager::Instance().BindKeyPressed(SDLK_d, "MoveRight");
	InputManager::Instance().BindKeyPressed(SDLK_SPACE, "Jump");
}

void InitializeAudio() 
{
	auto mainThemeClip = ResourceManager::Instance().GetAudioClip("assets/MainTheme.wav");
	mainThemeClip->SetLooping(true);
	mainThemeClip->Play();
}

entt::entity InitializePlayer(entt::registry& registry)
{
	std::shared_ptr<Sprite> sprite = std::make_shared<Sprite>(ResourceManager::Instance().GetTexture("assets/ball.png"));
	sprite->SetOrigin({ 0.5f, 0.5f });
	sprite->Resize(60.f, 60.f);

	std::shared_ptr<CollisionShape> collider = std::make_shared<CircleShape>(30.f);

	entt::entity entity = registry.create();
	registry.emplace<GraphicsComponent>(entity, std::move(sprite));
	registry.emplace<Transform>(entity);
	registry.emplace<InputComponent>(entity);
	registry.emplace<PlayerControlled>(entity);

	auto& entityBody = registry.emplace<RigidBodyComponent>(entity, 1.f);
	entityBody.AddShape(std::move(collider));

	return entity;
}

entt::entity InitializeCamera(entt::registry& registry)
{
	entt::entity entity = registry.create();
	registry.emplace<CameraComponent>(entity);
	registry.emplace<Transform>(entity);

	return entity;
}

entt::entity CreateBox(entt::registry& registry, Vector2f boxSize)
{
	std::shared_ptr<CollisionShape> startPlatformShape = std::make_shared<BoxShape>(boxSize.x, boxSize.y);

	std::shared_ptr<Sprite> box = std::make_shared<Sprite>(ResourceManager::Instance().GetTexture("assets/rock.png"));
	box->SetOrigin({ 0.5f, 0.5f });
	box->Resize(boxSize.x, boxSize.y);

	entt::entity entity = registry.create();
	registry.emplace<GraphicsComponent>(entity, std::move(box));
	registry.emplace<Transform>(entity);

	auto& entityPhysics = registry.emplace<RigidBodyComponent>(entity, RigidBodyComponent::Kinematic{});
	entityPhysics.AddShape(std::move(startPlatformShape));

	return entity;
}

void InitializeLevel(entt::registry& registry)
{
	entt::entity startPlatform = CreateBox(registry, Vector2f(1000.f, 280.f));
	registry.get<RigidBodyComponent>(startPlatform).TeleportTo({ 400.f, 1200.f }, 180.f);

	entt::entity firstPlatform = CreateBox(registry, Vector2f(400.f, 100.f));
	registry.get<RigidBodyComponent>(firstPlatform).TeleportTo({ 1200.f, 800.f }, 180.f);
	
	entt::entity secondPlatform = CreateBox(registry, Vector2f(400.f, 100.f));
	registry.get<RigidBodyComponent>(secondPlatform).TeleportTo({ 600.f, 400.f }, 180.f);
}

void HandleCameraMovement(entt::registry& registry, entt::entity camera, entt::entity player, float deltaTime)
{
	Transform& cameraTransform = registry.get<Transform>(camera);
	Transform& playerTransform = registry.get<Transform>(player);

	if (playerTransform.GetGlobalPosition().x < cameraTransform.GetGlobalPosition().x + 400.f)
		cameraTransform.Translate(Vector2f(-700.f * deltaTime, 0.f));

	if (playerTransform.GetGlobalPosition().x > cameraTransform.GetGlobalPosition().x + 1520.f)
		cameraTransform.Translate(Vector2f(700.f * deltaTime, 0.f));

	if (playerTransform.GetGlobalPosition().y < cameraTransform.GetGlobalPosition().y + 400.f)
		cameraTransform.Translate(Vector2f(0.f, -700.f * deltaTime));

	if (playerTransform.GetGlobalPosition().y > cameraTransform.GetGlobalPosition().y + 800.f)
		cameraTransform.Translate(Vector2f(0.f, 700.f * deltaTime));
}