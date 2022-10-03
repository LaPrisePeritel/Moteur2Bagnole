#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include <A4Engine/InputManager.hpp>
#include <A4Engine/ResourceManager.hpp>
#include <A4Engine/SDLpp.hpp>
#include <A4Engine/SDLppWindow.hpp>
#include <A4Engine/SDLppRenderer.hpp>
#include <A4Engine/SDLppTexture.hpp>
#include <A4Engine/Sprite.hpp>
#include <A4Engine/Transform.hpp>

int main(int argc, char** argv)
{
	Transform transform;
	transform.SetPosition(Vector2f(42.f, -6.f));
	transform.SetRotation(-270.f);
	transform.SetScale(Vector2f(0.5f, 2.f));

	std::cout << transform.TransformPoint(Vector2f(0.f, 0.f)) << std::endl;
	std::cout << transform.TransformPoint(Vector2f(10.f, 0.f)) << std::endl;
	std::cout << transform.TransformPoint(Vector2f(0.f, 10.f)) << std::endl;
	std::cout << transform.TransformPoint(Vector2f(21.f, -3.f)) << std::endl;

	transform.SetScale(Vector2f(-0.5f, -2.f));
	std::cout << transform.TransformPoint(Vector2f(-42.f, -42.f)) << std::endl;

    SDLpp sdl;

    SDLppWindow window("A4Engine", 1280, 720);
    SDLppRenderer renderer(window);

    InputManager::Instance().BindKeyPressed(SDLK_h, "SayHello");
    InputManager::Instance().BindMouseButtonPressed(MouseButton::Right, "SayHello");

    InputManager::Instance().OnAction("SayHello", []()
    {
        std::cout << "Hello world" << std::endl;
    });

    Sprite sprite(ResourceManager::Instance().GetTexture(renderer, "assets/runner.png"));
    sprite.Resize(256, 256);

    sprite.SetRect(SDL_Rect{ 0, 0, 32, 32 });

    Uint64 lastUpdate = SDL_GetPerformanceCounter();

    int frameIndex = 0;
    int frameCount = 5;
    float timer = 0.0f;

    bool isOpen = true;
    while (isOpen)
    {
        Uint64 now = SDL_GetPerformanceCounter();
        float deltaTime = (float) (now - lastUpdate) / SDL_GetPerformanceFrequency();
        lastUpdate = now;

        timer += deltaTime;
        if (timer > 0.1f)
        {
            timer -= 0.1f;
            frameIndex++;
            if (frameIndex >= frameCount)
                frameIndex = 0;  

            sprite.SetRect({ frameIndex * 32, 0, 32, 32 });

            std::cout << frameIndex << std::endl;
        }

        SDL_Event event;
        while (SDLpp::PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                isOpen = false;

            InputManager::Instance().HandleEvent(event);
        }

        renderer.SetDrawColor(127, 0, 127, 255);
        renderer.Clear();

        sprite.Draw(renderer, 147, 257);
        renderer.Present();
    }

    return 0;
}
