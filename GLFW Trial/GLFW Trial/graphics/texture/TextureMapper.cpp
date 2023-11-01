#include "TextureMapper.hpp"
#include <iostream>
#include <memory>

std::unordered_map <std::string_view, std::shared_ptr<Texture>> TextureMapper::m_textureMap = {};

MappedTexture TextureMapper::Get(std::string_view a_filePath)
{
    // Check if the texture is already loaded
    auto it = m_textureMap.find(a_filePath);
    if (it != m_textureMap.end()) {
        std::cout << "Texture already mapped, returning mapped texture!" << std::endl;
        return it->second;
    }

    std::cout << "Texture not yet mapped, texture will be mapped" << std::endl;
    return m_textureMap[a_filePath] = std::make_shared<Texture>(a_filePath.data());
}

void TextureMapper::Release(const std::shared_ptr<Texture>& a_pTexture)
{
    // Check if the texture is already loaded
    auto it = m_textureMap.find(a_pTexture->GetFilePath());
    if (it != m_textureMap.end()) {
        m_textureMap.erase(it);
        std::cout << "Mapped texture no longer needed, will be destroyed." << std::endl;
        return;
    }

    std::cerr << "Error: could not find supposedly mapped texure: " << a_pTexture << " something went wrong!";
}