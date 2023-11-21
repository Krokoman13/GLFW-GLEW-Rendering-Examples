#include "ResourceManager.hpp"
#include "PathManager.hpp"
#include "ResourceCache.hpp"

#include "../graphics/texture/Texture.hpp"
#include "../graphics/shader/Shader.hpp"
#include "../graphics/loaders/ShaderUtil.hpp"

ResourceCache<Texture> ResourceManager::texureCache = ResourceCache<Texture>();

Texture ResourceManager::GetTexture(const unsigned int a_uniqueID)
{
    return texureCache.Get(PathManager::GetFilePath(a_uniqueID));
}

ResourceCache<Shader> ResourceManager::shaderCache = ResourceCache<Shader>();

Shader ResourceManager::GetShader(const unsigned int a_vertexhaderPathID, const unsigned int a_fragmentShaderPathID)
{
    std::string path = ShaderUtil::createString(PathManager::GetFilePath(a_vertexhaderPathID), PathManager::GetFilePath(a_fragmentShaderPathID));
    return shaderCache.Get(path);
}
