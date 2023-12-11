#pragma once
#include <string>

class Shader;
class Texture;
class GLBuffer;

template<typename, typename>
class ResourceCache;

class ResourceManager
{
public:
	inline static ResourceCache<Texture, std::string>* pTexureCache = nullptr;
	static Texture GetTexture(const unsigned int a_uniqueID);

	inline static ResourceCache<Shader, std::string>* pShaderCache = nullptr;
	static Shader GetShader(const unsigned int a_vertexhaderPathID, const unsigned int a_fragmentShaderPathID);

	inline static ResourceCache<GLBuffer, unsigned int>* pGLBufferCache = nullptr;
	static GLBuffer GetGLBuffer(const unsigned int a_displayModeID);
};

