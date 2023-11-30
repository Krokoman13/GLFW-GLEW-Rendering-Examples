#pragma once
#include <unordered_map>
#include <iostream>
#include <sstream>
#include <type_traits>
#include "../core/counted/Counted.hpp"

template<typename T>

class ResourceCache
{
    static_assert(std::is_base_of<Counted, T>::value, "T must inherit from Counted");

private:
    // A hash map to store the mapping from resource paths to indices in the resources vector
    std::unordered_map <std::string, unsigned int> m_resourceMap;
    // A vector to store the resources
    std::vector<T> m_resources;

public:
    ~ResourceCache() { Clear(); }

    // Either finds and returns an existing resource or create and adds a new one
    T Get(const std::string& a_path)
    {
        // Check if the resource is already cached
        auto it = m_resourceMap.find(a_path);
        if (it != m_resourceMap.end()) {
            std::cout << "Resource " << a_path << " already mapped, returning cached resource!" << std::endl;
            return get(it->second);
        }

        std::cout << "Resource not yet mapped, resource will be mapped" << std::endl;

        // If the resource is not cached, add it to the cache and return it
        const unsigned int index = addNewResouce(a_path);

        return get(index);
    };

    // Clears the cache of all current resources
    void Clear()
    {
        while (!m_resources.empty()) {
            if (!m_resources.back().LastCopy())
                std::cerr << "Warning: resource in cache is NOT the last resource, this means it cannot be cleaned up propperly" << std::endl;

            m_resources.pop_back();
        }

        m_resourceMap.clear();
    }

private:
    // A private method to get a resource by its index
    inline T& get(const unsigned int a_index) { return m_resources[a_index]; };

    unsigned int addNewResouce(const std::string& a_path)
    {
        // Try to find a lonely resource to overwrite
        const unsigned int index = findLonely();

        // If there are not lonely resources add the resource to the cache
        if (index == m_resources.size())
        {
            m_resources.push_back(T(a_path));
        }
        // Otherwise, overwrite the lonely resource
        else
        {
            std::cout << "Found a lonely Resouce, will be overwritten by a new one!" << std::endl;
            const std::string& previous = findByValue(index);
            m_resources[index] = T(a_path);
            m_resourceMap.erase(previous);
        }

        // Add the path and index to the resource map
        m_resourceMap[a_path] = index;
        return index;
    };

    // A private method to find a lonely resource
    unsigned int findLonely()
    {
        // Get the size of the resources vector
        const unsigned int size = m_resources.size();

        // Iterate over the resources vector
        for (unsigned int i = 0; i < size; i++)
        {
            // If a resource is lonely (its count is 1), return its index
            if (m_resources[i].LastCopy()) return i;
        }

        // If no lonely resource is found, return the size of the resources vector
        return size;
    };

    std::string findByValue(const unsigned int a_value)
    {
        for (auto it : m_resourceMap)
        {
            if (it.second == a_value) return it.first;
        }

        throw std::invalid_argument("Value was not found in resourceMap");
    }
};