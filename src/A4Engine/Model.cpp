#include <A4Engine/Model.hpp>
#include <A4Engine/ResourceManager.hpp>
#include <A4Engine/SDLppRenderer.hpp>
#include <A4Engine/SDLppTexture.hpp>
#include <nlohmann/json.hpp>

#include <iostream>
#include <string>
#include <fstream>

Model::Model(const char* filepath)
{
	std::ifstream _file(filepath);
	auto jsonFile = nlohmann::json::parse(_file);

	std::string textureFilepath = jsonFile.at("texture");
	_texture = ResourceManager::Instance().GetTexture(textureFilepath);

	for (const auto& indice : jsonFile.at("indices"))
		_indices.push_back(indice);

	for (const auto& v : jsonFile.at("vertices"))
	{
		auto& pos = v.at("position");
		auto& tc = v.at("uv");
		auto& col = v.at("color");

		SDL_FPoint position{ pos[0], pos[1] };
		SDL_FPoint tex_coord{ tc[0], tc[1] };
		SDL_Color color{ col[0], col[1], col[2], col[3] };

		SDL_Vertex vertex{ position, color, tex_coord };

		_vertices.push_back(vertex);
	}
}

void Model::Draw(SDLppRenderer& renderer)
{
	SDL_RenderGeometry(renderer.GetHandle(),
		_texture.get()->GetHandle(),
		_vertices.data(),
		(int)_vertices.size(),
		_indices.data(),
		(int)_indices.size());
}

void Model::ToJson(std::string name)
{
	if (name.length() <= 0)
		return;

	nlohmann::json JsonFile;
	std::string path = "assets/Models/" + name;
	JsonFile["indices"] = _indices;
	JsonFile["path"] = path;
	JsonFile["vertices"];

	std::ofstream file(path);
	file << std::setw(4) << JsonFile << std::endl;
}
