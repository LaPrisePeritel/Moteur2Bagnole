#include <A4Engine/CameraComponent.hpp>
#include <A4Engine/GraphicsComponent.hpp>
#include <A4Engine/InputManager.hpp>
#include <A4Engine/ResourceManager.hpp>
#include <A4Engine/Sprite.hpp>
#include <A4Engine/Transform.hpp>
#include <A4Engine/SDLpp.hpp>
#include <A4Engine/SDLppRenderer.hpp>
#include <A4Engine/SDLppWindow.hpp>
#include <dr_wav.h>
#include <A4Engine/AudioClip.hpp>
#include <A4Engine/AudioSystem.hpp>

int main()
{
	SDLpp sdl;
	SDLppWindow window("Test audio", 1280, 720);
	SDLppRenderer renderer(window, "", SDL_RENDERER_PRESENTVSYNC);

	ResourceManager resourceManager(renderer);

	AudioSystem audioSystem;
	audioSystem.SetGeneralGain(0.1f);

	// On va faire des trucs !
	auto audioClip = ResourceManager::Instance().GetAudioClip("assets/siren.wav");
	audioClip->SetLooping(true);
	audioClip->Play();

	InputManager inputManager;

	inputManager.BindKeyPressed(SDLK_LEFT, "MoveLeft");
	inputManager.BindKeyPressed(SDLK_RIGHT, "MoveRight");

	Sprite ambulance(resourceManager.GetTexture("assets/ambulance.png"));
	ambulance.Resize(ambulance.GetWidth() * 0.1f, ambulance.GetHeight() * 0.1f);
	ambulance.SetOrigin(Vector2f(0.5f, 0.5f));

	Transform cameraTransform;
	Transform ambulanceTransform;
	ambulanceTransform.SetPosition(Vector2f(640, 360));

	Uint64 lastUpdate = SDL_GetPerformanceCounter();

	bool isOpen = true;
	while (isOpen)
	{
		Uint64 now = SDL_GetPerformanceCounter();
		float deltaTime = (float)(now - lastUpdate) / SDL_GetPerformanceFrequency();
		lastUpdate = now;

		SDL_Event event;
		while (sdl.PollEvent(&event))
		{
			if (event.type == SDL_QUIT)
				isOpen = false;

			inputManager.HandleEvent(event);
		}
		
		renderer.SetDrawColor(0, 127, 255, 255);
		renderer.Clear();

		Vector2f oldPosition = ambulanceTransform.GetGlobalPosition();

		if (inputManager.IsActive("MoveLeft"))
			ambulanceTransform.Translate(Vector2f(-1000.f * deltaTime, 0.f));

		if (inputManager.IsActive("MoveRight"))
			ambulanceTransform.Translate(Vector2f(1000.f * deltaTime, 0.f));

		Vector2f ambulancePos = ambulanceTransform.GetGlobalPosition();
		Vector2f velocity = (ambulancePos - oldPosition) / deltaTime;

		Vector3f ambulanceSourcePos(ambulancePos.x / 100.f, ambulancePos.y / 100.f, 0.f);
		Vector3f ambulanceSourceVel(velocity.x / 100.f, velocity.y / 100.f, 0.f);

		audioClip->SetSourcePosition(ambulanceSourcePos);
		audioClip->SetSourceVelocity(ambulanceSourceVel);

		ambulance.Draw(renderer, cameraTransform.GetTransformMatrix() * ambulanceTransform.GetTransformMatrix());

		renderer.Present();
	}
}