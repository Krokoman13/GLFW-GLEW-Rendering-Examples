#pragma once

class Shader;
class Texture;

template<typename>
class ResourceCache;

class ResourceManager
{
public:
	static ResourceCache<Texture> texureCache;
	static Texture GetTexture(const unsigned int a_uniqueID);

	static ResourceCache<Shader> shaderCache;
	static Shader GetShader(const unsigned int a_vertexhaderPathID, const unsigned int a_fragmentShaderPathID);
};

