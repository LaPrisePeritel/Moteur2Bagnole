#include <iostream>
#include <SDL.h>
#include "SDLpp.hpp"
#include "SDLppWindow.hpp"
#include "SDLppRenderer.hpp"
#include "SDLppTexture.hpp"

int main(int argc, char** argv)
{
    SDLpp sdl;

    SDLppWindow window("A4Engine", 1280, 720);
    SDLppRenderer renderer(window);

    SDLppTexture monbeauchat = SDLppTexture::LoadFromFile(renderer, "assets/karmeliet.jpg");

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

        SDL_Rect rect;
        rect.x = 147;
        rect.y = 257;
        rect.w = 1422 / 4;
        rect.h = 1347 / 4;

        renderer.RenderCopy(monbeauchat, rect);
        renderer.Present();
    }

    return 0;
}
