#pragma once
#include <unordered_map>
#include <iostream>
#include <type_traits>
#include "../../core/counted/Counted.hpp"

template<typename TResource, typename TKey>

class ResourceCache
{
    static_assert(std::is_base_of<Counted, TResource>::value, "T must inherit from Counted");

protected:
    // A hash map to store the mapping from resource paths to indices in the resources vector
    std::unordered_map <TKey, unsigned int> m_resourceMap;
    // A vector to store the resources
    std::vector<TResource> m_resources;

public:
    virtual ~ResourceCache() { Clear(); }

    inline TResource& Get(const TKey& a_key) { return m_resources[m_resourceMap[a_key]]; };
    
    // A public method to check if a resource arleady exits
    bool Exists(const TKey& a_key) const
    {
        auto it = m_resourceMap.find(a_key);
        if (it != m_resourceMap.end()) {
            return true;
        }

        return false;
    };

    // Clears the cache of all current resources
    void Clear()
    {
        while (!m_resources.empty()) {
            if (!m_resources.back().IsLast())
                std::cerr << "Warning: resource in cache is NOT the last resource, this means it cannot be cleaned up propperly" << std::endl;

            m_resources.pop_back();
        }

        m_resourceMap.clear();
    }

    virtual void AddNewResource(const TKey& a_key, const TResource a_resource)
    {
        if (Exists(a_key)) throw std::invalid_argument("Key already existst, cannot add new resource, make sure to check using `Exists(TKey)`");

        m_resources.push_back(a_resource);
        m_resourceMap[a_key] = m_resources.size() - 1;
    };
};