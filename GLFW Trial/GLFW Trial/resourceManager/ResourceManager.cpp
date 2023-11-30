#include "ResourceManager.hpp"
#include "PathManager.hpp"
#include "ResourceCache.hpp"

#include "../graphics/texture/Texture.hpp"
#include "../graphics/shader/Shader.hpp"
#include "../graphics/loaders/ShaderUtil.hpp"

Texture ResourceManager::GetTexture(const unsigned int a_uniqueID)
{
    if (!pTexureCache) throw std::invalid_argument("No texureCache has been assigned");
    return pTexureCache->Get(PathManager::GetFilePath(a_uniqueID));
}

Shader ResourceManager::GetShader(const unsigned int a_vertexhaderPathID, const unsigned int a_fragmentShaderPathID)
{
    if (!pShaderCache) throw std::invalid_argument("No shaderCache has been assigned");
    std::string path = ShaderUtil::createString(PathManager::GetFilePath(a_vertexhaderPathID), PathManager::GetFilePath(a_fragmentShaderPathID));
    return pShaderCache->Get(path);
}
