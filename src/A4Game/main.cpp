#include <iostream>
#include <fstream>
#include <SDL.h>
#include <A4Engine/InputManager.hpp>
#include <A4Engine/ResourceManager.hpp>
#include <A4Engine/SDLpp.hpp>
#include <A4Engine/SDLppWindow.hpp>
#include <A4Engine/SDLppRenderer.hpp>
#include <A4Engine/SDLppTexture.hpp>
#include <A4Engine/Sprite.hpp>
#include <A4Engine/Transform.hpp>
#include <imgui.h>
#include <imgui_impl_sdl.h>
#include <imgui_impl_sdlrenderer.h>
#include <A4Engine/Model.hpp>
#include <entt/entt.hpp>
#include <A4Engine/Systems.hpp>
#include <A4Engine/Components.hpp>

int main(int argc, char** argv)
{
    SDLpp sdl;

    SDLppWindow window("A4Engine", 1280, 720);
    SDLppRenderer renderer(window);

    ResourceManager resourceManager(renderer);
    InputManager inputManager;

    Model model("assets/Models/house.model");

    // Setup imgui
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();

    ImGui::StyleColorsDark();

    ImGui_ImplSDL2_InitForSDLRenderer(window.GetHandle(), renderer.GetHandle());
    ImGui_ImplSDLRenderer_Init(renderer.GetHandle());


    Transform transformParent;
    Transform transform;
    transform.SetParent(&transformParent);

    transformParent.SetPosition(Vector2f(300.f, 100.f));
    transform.SetPosition(Vector2f(150.f, 150.f));

    // ZQSD
    InputManager::Instance().BindKeyPressed(SDLK_q, "MoveLeft");
    InputManager::Instance().BindKeyPressed(SDLK_d, "MoveRight");
    InputManager::Instance().BindKeyPressed(SDLK_z, "MoveUp");
    InputManager::Instance().BindKeyPressed(SDLK_s, "MoveDown");

    // Touches directionnelles
    InputManager::Instance().BindKeyPressed(SDLK_LEFT, "MoveLeft");
    InputManager::Instance().BindKeyPressed(SDLK_RIGHT, "MoveRight");
    InputManager::Instance().BindKeyPressed(SDLK_UP, "MoveUp");
    InputManager::Instance().BindKeyPressed(SDLK_DOWN, "MoveDown");

    std::shared_ptr<SDLppTexture> texture = ResourceManager::Instance().GetTexture("assets/runner.png");

    entt::registry registry;

    entt::entity camera = registry.create();
    auto& cameraTranform = registry.emplace<Transform>(camera);
    cameraTranform.SetPosition(Vector2f(-512.f, -232.f));
    cameraTranform.SetScale(Vector2f(1.f, 1.f));
    cameraTranform.SetRotation(5);

    registry.emplace<CameraComponent>(camera);
    

    entt::entity player = registry.create();
    {
        auto& entityPos = registry.emplace<Transform>(player);
        entityPos.SetPosition(Vector2f(0.f, 0.f));

        auto& entityDrawable = registry.emplace<Sprite>(player, texture);
        entityDrawable.SetRect(SDL_Rect{ 0, 0, 32, 32 });
        entityDrawable.Resize(256, 256);

        auto& entityVelocity = registry.emplace<VelocityComponent>(player);
        entityVelocity.x = 0.f;
        entityVelocity.y = 0.f;

        /*registry.emplace<nogravity>(player);

        registry.emplace<input>(player);*/
    }

    Sprite sprite(texture);
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

            ImGui_ImplSDL2_ProcessEvent(&event);

            InputManager::Instance().HandleEvent(event);
        }

        if (InputManager::Instance().IsActive("MoveDown"))
            transformParent.Translate(Vector2f(0.f, 500.f * deltaTime));

        if (InputManager::Instance().IsActive("MoveLeft"))
            transformParent.Translate(Vector2f(-500.f * deltaTime, 0.f));

        if (InputManager::Instance().IsActive("MoveRight"))
            transformParent.Translate(Vector2f(500.f * deltaTime, 0.f));

        if (InputManager::Instance().IsActive("MoveUp"))
            transformParent.Translate(Vector2f(0.f, -500.f * deltaTime));

        // ImGUI
        ImGui_ImplSDLRenderer_NewFrame();
        ImGui_ImplSDL2_NewFrame();
        ImGui::NewFrame();

        renderer.SetDrawColor(127, 0, 127, 255);
        renderer.Clear();

        ImGui::Begin("Camera Parameter");

        auto& position = cameraTranform.GetPosition();
        float posPtr[2] = { position.x, position.y };
        if (ImGui::SliderFloat2("Position", posPtr, -1000.f, 1000.f))
            cameraTranform.SetPosition(Vector2(posPtr[0], posPtr[1]));

        float rotation = cameraTranform.GetRotation();
        if (ImGui::SliderFloat("Rotation", &rotation, -180.f, 180.f))
            cameraTranform.SetRotation(rotation);

        auto& scale = cameraTranform.GetScale();
        float scalePtr[2] = { scale.x, scale.y };
        if (ImGui::SliderFloat2("Scale", scalePtr, -10.f, 10.f))
            cameraTranform.SetScale(Vector2(scalePtr[0], scalePtr[1]));

        ImGui::End();

        //sprite.Draw(renderer, transformParent);
        //sprite.Draw(renderer, transform);

		ImGui::Render();
		ImGui_ImplSDLRenderer_RenderDrawData(ImGui::GetDrawData());

        Systems::RenderSystem(registry, renderer);
        Systems::VelocitySystem(registry, deltaTime);
        renderer.Present();
	}
	// Cleanup
	ImGui_ImplSDLRenderer_Shutdown();
	ImGui_ImplSDL2_Shutdown();
	ImGui::DestroyContext();

    return 0;
}
