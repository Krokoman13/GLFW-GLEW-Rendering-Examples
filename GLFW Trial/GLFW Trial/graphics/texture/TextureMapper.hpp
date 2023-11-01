#pragma once
#include <unordered_map>
#include <memory>
#include <string_view>
#include "MappedTexture.hpp"

class TextureMapper
{
private:
	static std::unordered_map <std::string_view, std::shared_ptr<Texture>> m_textureMap;

public:
	static MappedTexture Get(std::string_view a_filePath);
	static void Release(const std::shared_ptr<Texture>& a_pTexture);
};
