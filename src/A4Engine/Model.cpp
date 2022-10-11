#include <A4Engine/Model.h>

#include <nlohmann/json.hpp>

#include <iostream>
#include <fstream>

using json = nlohmann::json;

Model::Model(const char* filepath)
{
	std::ifstream _file(filepath);
	auto jsonFile = json::parse(_file);

	_texture = jsonFile.at("texture");

	for (const auto& indice : jsonFile.at("indices"))
		_indices.push_back(indice);

	for (const auto& vertex : jsonFile.at("vertices"))
	{
		auto& pos = vertex.at("position");
		auto& tc = vertex.at("uv");
		auto& col = vertex.at("color");

		SDL_FPoint position{ pos[0], pos[1] };
		SDL_FPoint tex_coord{ tc[0], tc[1] };
		SDL_Color color{ col[0], col[1], col[2], col[3] };

		SDL_Vertex vertex{ position, color, tex_coord };

		_vertices.push_back(vertex);
	}

	//remplir avec les valeurs du JSON
}

Model::Model(Model&&) noexcept
{
}
