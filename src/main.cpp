#include <iostream>
#include <SDL.h>
#include <SDL_image.h>
#include "SDLpp.hpp"
#include "SDLppWindow.hpp"
#include "SDLppRenderer.hpp"
#include "SDLppTexture.hpp"
#include "Sprite.hpp"

int main(int argc, char** argv)
{
    SDLpp sdl;

    SDLppWindow window("A4Engine", 1280, 720);
    SDLppRenderer renderer(window);

    SDLppTexture runner = SDLppTexture::LoadFromFile(renderer, "assets/runner.png");
    Sprite sprite(runner);
    sprite.Resize(256, 256);

    sprite.SetRect(SDL_Rect{ 0, 0, 32, 32 });

    Uint64 lastUpdate = SDL_GetPerformanceCounter();

    bool isOpen = true;
    while (isOpen)
    {
        Uint64 now = SDL_GetPerformanceCounter();
        float deltaTime = (float) (now - lastUpdate) / SDL_GetPerformanceFrequency();

        SDL_Event event;
        while (SDLpp::PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                isOpen = false;
        }

        renderer.SetDrawColor(127, 0, 127, 255);
        renderer.Clear();

        sprite.Draw(renderer, 147, 257);
        renderer.Present();
    }

    return 0;
}
