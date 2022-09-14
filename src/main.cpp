#include <iostream>
#include <SDL.h>
#include "SDLpp.hpp"
#include "SDLppWindow.hpp"
#include "SDLppRenderer.hpp"

int main(int argc, char** argv)
{
    SDLpp sdl;

	SDLppWindow window("A4Engine", SDL_WINDOWPOS_CENTERED, SDL_WINDOWPOS_CENTERED, 1280, 720, 0);
	SDLppRenderer renderer(window);

    bool isOpen = true;
    while (isOpen)
    {
        SDL_Event event;
        while (SDLpp::PollEvent(&event))
        {
            if (event.type == SDL_QUIT)
                isOpen = false;
        }

        renderer.SetDrawColor(127, 0, 127, 255);
        renderer.Clear();
        renderer.Present();
    }

    return 0;
}
