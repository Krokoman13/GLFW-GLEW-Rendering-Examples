#pragma once
#include <unordered_map>
#include <string_view>
#include <iostream>
#include <sstream>
#include "Counted.hpp"

template<typename T, typename = std::enable_if_t<std::is_base_of<Counted, T>::value>>

class ResourceCache
{
private:
	std::unordered_map <std::string_view, unsigned int> m_resourceMap;
	std::vector<T> m_resources;

	inline T& get(const unsigned int a_index) { return m_resources[a_index]; };

	template<typename... Args>
	std::string argsToString(Args... args)
	{
		std::stringstream ss;
		(ss << ... << args);
		return ss.str();
	}

	template<typename... Args>
	unsigned int addNewResouce(std::string_view a_stringView, Args... args)
	{
		const unsigned int index = findLonely();
		if (index == m_resources.size())
		{
			m_resources.push_back(T(args...));
		}
		else
		{
			std::cout << "Found a lonely Resouce, will be overwritten by a new one!" << std::endl;
			m_resources[index] = T(args...);
		}

		m_resourceMap[a_stringView] = index;
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
	template<typename... Args>
	T Get(Args... args)
	{
		const std::string string = argsToString(args...);

		// Check if the resource is already cached
		auto it = m_resourceMap.find(stringView);
		if (it != m_resourceMap.end()) {
			std::cout << "Resource already mapped, returning cached resource!" << std::endl;
			return m_resources[it->second];
		}

		std::cout << "Resource not yet mapped, resource will be mapped" << std::endl;

		const unsigned int index = addNewResouce(stringView, args...);

		return m_resources[index];
	};
};

