#pragma once
#include <unordered_map>
#include <string_view>
#include <iostream>
#include <sstream>
#include "Counted.hpp"

#include "../resourceManager/ResourceManager.hpp"


template<typename T, typename = std::enable_if_t<std::is_base_of<Counted, T>::value>>

class ResourceCache
{
private:
	std::unordered_map <unsigned int, unsigned int> m_resourceMap;
	std::vector<T> m_resources;

	inline T& get(const unsigned int a_index) { return m_resources[a_index]; };

	unsigned int addNewResouce(const unsigned int a_resourceID)
	{
		const unsigned int index = findLonely();
		const std::string_view path = ResourceManager::GetFilePath(a_resourceID);
		
		if (index == m_resources.size())
		{
			m_resources.push_back(T(path));
		}
		else
		{
			std::cout << "Found a lonely Resouce, will be overwritten by a new one!" << std::endl;
			m_resources[index] = T(path);
		}

		m_resourceMap[a_resourceID] = index;
		return index;
	};

	unsigned int findLonely()
	{
		const unsigned int size = m_resources.size();

		for (unsigned int i = 0; i < size; i++)
		{
			if (m_resources[i].Count() == 1) return i;
		}

		return size;
	};

public:
	T Get(const unsigned int a_resourceID)
	{
		// Check if the resource is already cached
		auto it = m_resourceMap.find(a_resourceID);
		if (it != m_resourceMap.end()) {
			std::cout << "Resource already mapped, returning cached resource!" << std::endl;
			return m_resources[it->second];
		}

		std::cout << "Resource not yet mapped, resource will be mapped" << std::endl;

		const unsigned int index = addNewResouce(a_resourceID);

		return m_resources[index];
	};
};

