#pragma once

class Shader;
class Texture;

template<typename>
class ResourceCache;

class ResourceManager
{
public:
	inline static ResourceCache<Texture>* pTexureCache = nullptr;
	static Texture GetTexture(const unsigned int a_uniqueID);

	inline static ResourceCache<Shader>* pShaderCache = nullptr;
	static Shader GetShader(const unsigned int a_vertexhaderPathID, const unsigned int a_fragmentShaderPathID);
};

