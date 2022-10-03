#pragma once

#include <A4Engine/Export.hpp>
#include <memory> //< std::shared_ptr
#include <unordered_map> //< std::unordered_map est plus efficace que std::map pour une association clé/valeur

class SDLppRenderer;
class SDLppTexture;

class A4ENGINE_API ResourceManager
{
	public:
		ResourceManager() = default;
		ResourceManager(const ResourceManager&) = delete;
		ResourceManager(ResourceManager&&) = delete;
		~ResourceManager() = default;

		const std::shared_ptr<SDLppTexture>& GetTexture(SDLppRenderer& renderer, const std::string& texturePath);

		void Purge();

		static ResourceManager& Instance();

		ResourceManager& operator=(const ResourceManager&) = delete;
		ResourceManager& operator=(ResourceManager&&) = delete;

	private:
		std::shared_ptr<SDLppTexture> m_missingTexture;
		std::unordered_map<std::string /*texturePath*/, std::shared_ptr<SDLppTexture>> m_textures;
};