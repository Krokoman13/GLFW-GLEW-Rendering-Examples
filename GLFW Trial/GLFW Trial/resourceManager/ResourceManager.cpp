#include "ResourceManager.hpp"
#include "PathManager.hpp"
#include "ResourceCache/ResourceCache.hpp"

#include "../graphics/texture/Texture.hpp"
#include "../graphics/shader/Shader.hpp"
#include "../graphics/loaders/ShaderUtil.hpp"

Texture ResourceManager::GetTexture(const unsigned int a_uniqueID)
{
    if (!pTexureCache) throw std::invalid_argument("No texureCache has been assigned");

    std::string path = PathManager::GetFilePath(a_uniqueID);
    if (pTexureCache->Exists(path)){
        std::cout << "ResourceManager: " << path << " already cached, not loaded again" << std::endl;
        return pTexureCache->Get(path);
    }

    Texture texture(path);
    pTexureCache->AddNewResource(path, texture);
    return texture;
}

Shader ResourceManager::GetShader(const unsigned int a_vertexhaderPathID, const unsigned int a_fragmentShaderPathID)
{
    if (!pShaderCache) throw std::invalid_argument("No shaderCache has been assigned");

    std::string path = ShaderUtil::createString(PathManager::GetFilePath(a_vertexhaderPathID), PathManager::GetFilePath(a_fragmentShaderPathID));
    if (pShaderCache->Exists(path))  {
        std::cout << "ResourceManager: " << path << " already cached, not loaded again" << std::endl;
        return pShaderCache->Get(path);
    }

    Shader shader(path);
    pShaderCache->AddNewResource(path, shader);
    return shader;
}
