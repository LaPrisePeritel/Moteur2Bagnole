#pragma once

#include <SDL.h>
#include <string>
#include <vector>

class Model
{
public:
	Model() = default;
	Model(const char* filepath);
	Model(const Model&) = default;
	Model(Model&&) noexcept;
	~Model() = default;

private:
	std::string _texture;
	std::vector<int> _indices;
	std::vector<SDL_Vertex> _vertices;
};
