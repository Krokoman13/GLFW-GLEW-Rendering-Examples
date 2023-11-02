#pragma once
#include <unordered_map>
#include <string_view>
#include <iostream>

template<typename T>
class CachedResource;

template<typename T>
class ResourceCache
{
private:
	friend class CachedResource<T>;
	std::unordered_map <std::string_view, unsigned int> m_resourceMap;
	std::vector<T> m_resources;

	inline T& get(const unsigned int a_index) { return m_resources[a_index]; };

	unsigned int addNewResouce(std::string_view a_filePath)
	{
		const unsigned int index = m_resources.size();
		m_resources.push_back(T(a_filePath.data()));
		m_resourceMap[a_filePath] = index;
		return index;
	};

public:
	CachedResource<T> Get(std::string_view a_filePath);
};

template<typename T>
class CachedResource
{
private:
	friend class ResourceCache<T>;

	unsigned int m_index;
	ResourceCache<T>& m_cache;

private:
	CachedResource(const unsigned int a_index, ResourceCache<T>& a_cache) : m_index(a_index), m_cache(a_cache) {};

public:
	CachedResource(const CachedResource<T>& a_other) : m_index(a_other.m_index), m_cache(a_other.m_cache) {};
	~CachedResource() {};

	inline T& Get() { return m_cache.get(m_index); };
	T& operator->() { return Get(); };
};

template<typename T>
CachedResource<T> ResourceCache<T>::Get(std::string_view a_filePath)
{
	// Check if the resource is already cached
	auto it = m_resourceMap.find(a_filePath);
	if (it != m_resourceMap.end()) {
		std::cout << "Resource already mapped, returning cached resource!" << std::endl;
		return CachedResource<T>(it->second, *this);
	}

	std::cout << "Resource not yet mapped, resource will be mapped" << std::endl;

	const unsigned int index = addNewResouce(a_filePath);

	return CachedResource<T>(index, *this);
}

