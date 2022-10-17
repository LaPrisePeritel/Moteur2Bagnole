#pragma once

#include <SDL.h>
#include <vector>
#include <memory>
#include <string>
#include <A4Engine/Export.hpp>

class SDLppRenderer;
class SDLppTexture;

class A4ENGINE_API Model
{
public:
	Model() = default;
	Model(const char* filepath);
	Model(const Model&) = default;
	Model(Model&&) = default;
	Model& operator=(const Model&) = default;
	Model& operator=(Model&&) = default;
	~Model() = default;

	void Draw(SDLppRenderer& renderer);
	//void ToJson(std::string name);

private:
	std::shared_ptr<SDLppTexture> _texture;
	std::vector<int> _indices;
	std::vector<SDL_Vertex> _vertices;
};
