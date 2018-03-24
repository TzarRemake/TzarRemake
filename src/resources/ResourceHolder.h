/*
 * TzarRemake
 * Copyright (C) 2018
 *
 * This program is free software: you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation, either version 3 of the License, or
 * (at your option) any later version.
 *
 * This program is distributed in the hope that it will be useful,
 * but WITHOUT ANY WARRANTY; without even the implied warranty of
 * MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
 * GNU General Public License for more details.
 *
 * You should have received a copy of the GNU General Public License
 * along with this program.  If not, see <https://www.gnu.org/licenses/>.
 */

#pragma once

#include <vector>
#include <map>
#include <memory>

//--------------------------------------------------------------------------

template<typename T, typename K = std::string>
class ResourceHolder
{
public:
    using Resource = std::shared_ptr<T>;

    void load(const K& key, std::unique_ptr<T> &&resource)
    {
        m_resources.emplace(key, std::move(resource));
    }

    void release(const K& key)
    {
        m_resources.erase(key);
    }

    void clear()
    {
        m_resources.clear();
    }

    Resource get(const K& key)
    {
        auto it = m_resources.find(key);
        if (it == m_resources.end())
            return nullptr;

        return it->second;
    }

    std::vector<Resource> list(const K& key)
    {
        std::vector<Resource> resources;
        auto range = m_resources.equal_range(key);

        for (auto i = range.first; i != range.second; ++i)
            resources.push_back(i->second);

        return std::move(resources);
    }

private:
    std::multimap<K, Resource> m_resources;
};
