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

    SDLppTexture monbeauchat = SDLppTexture::LoadFromFile(renderer, "assets/karmeliet.jpg");
    Sprite sprite(monbeauchat);
    sprite.Resize(sprite.GetWidth() / 4, sprite.GetHeight() / 4);

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

        sprite.Draw(renderer, 147, 257);
        renderer.Present();
    }

    return 0;
}
