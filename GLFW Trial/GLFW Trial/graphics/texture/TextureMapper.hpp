#pragma once
#include <unordered_map>
#include <memory>
#include <string>
#include "MappedTexture.hpp"

class TextureMapper
{
private:
	static std::unordered_map <const char*, std::shared_ptr<Texture>> m_textureMap;

public:
	static MappedTexture Get(const char* a_filePath);
	static void Release(const std::shared_ptr<Texture>& a_pTexture);
};
