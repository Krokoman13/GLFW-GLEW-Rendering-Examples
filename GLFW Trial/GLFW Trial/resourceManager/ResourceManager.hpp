#pragma once
#include <string>

class Shader;
class Texture;

template<typename, typename>
class ResourceCache;

class ResourceManager
{
public:
	inline static ResourceCache<Texture, std::string>* pTexureCache = nullptr;
	static Texture GetTexture(const unsigned int a_uniqueID);

	inline static ResourceCache<Shader, std::string>* pShaderCache = nullptr;
	static Shader GetShader(const unsigned int a_vertexhaderPathID, const unsigned int a_fragmentShaderPathID);
};

