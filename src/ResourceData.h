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

#include <memory>
#include <vector>
#include <map>

//--------------------------------------------------------------------------

enum class ResourceType
{
    DICT,
    LIST
};

//--------------------------------------------------------------------------

struct BaseResourceNode
{
    ResourceType type;
};

//--------------------------------------------------------------------------

struct ResourceNodeDict : public BaseResourceNode
{
    ResourceNodeDict() { type = ResourceType::DICT; }
    std::map<std::string, std::string> values;
};

//--------------------------------------------------------------------------

struct ResourceNodeList : public BaseResourceNode
{
    ResourceNodeList() { type = ResourceType::LIST; }
    std::vector<std::string> values;
};

//--------------------------------------------------------------------------

class ResourceData
{
public:
    bool load(std::string file)
    {
        return false;
    }

    bool insert(std::string key, std::shared_ptr<BaseResourceNode> node)
    {
        auto pair = m_data.emplace(key, std::move(node));
        return pair.second;
    }

    template<typename T>
    std::shared_ptr<T> get(std::string key)
    {
        static_assert(std::is_base_of<BaseResourceNode, T>::value, "T must derive from BaseResourceNode");

        auto it = m_data.find(key);
        if (it == m_data.end())
            return nullptr;

        return std::static_pointer_cast<T>(it->second);
    }

private:
    std::map<std::string, std::shared_ptr<BaseResourceNode>> m_data;
};
