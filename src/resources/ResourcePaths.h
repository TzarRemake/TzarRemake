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
#include <cassert>
#include <vector>
#include <map>
#include <exception>
#include <json/json.hpp>

//--------------------------------------------------------------------------

class BasePathNode;

//--------------------------------------------------------------------------

using json = nlohmann::json;
using ResourcePathValue = std::string;
using ResourcePathDict = std::map<std::string, std::shared_ptr<BasePathNode>>;
using ResourcePathList = std::vector<ResourcePathValue>;

//--------------------------------------------------------------------------

enum class PathType
{
    INVALID = -1,
    VALUE = 0,
    DICT,
    LIST
};

//--------------------------------------------------------------------------

struct BasePathNode
{
    PathType type = PathType::INVALID;
};

//--------------------------------------------------------------------------

struct PathNodeValue : public BasePathNode
{
    PathNodeValue() { type = PathType::VALUE; }
    PathNodeValue(std::string path) : value(path) { type = PathType::VALUE; }
    ResourcePathValue value;
};

//--------------------------------------------------------------------------

struct PathNodeDict : public BasePathNode
{
    PathNodeDict() { type = PathType::DICT; }
    ResourcePathDict values;
};

//--------------------------------------------------------------------------

struct PathNodeList : public BasePathNode
{
    PathNodeList() { type = PathType::LIST; }
    ResourcePathList values;
};

//--------------------------------------------------------------------------

class ResourcePathNode
{
public:
    ResourcePathNode()
    {}

    ResourcePathNode(std::shared_ptr<BasePathNode> node) :
        pNode(node)
    {}

    const ResourcePathValue& value() const
    {
        if (pNode == nullptr || pNode->type != PathType::VALUE)
            throw std::invalid_argument("PathNodeValue invalid type!");

        auto data = std::static_pointer_cast<PathNodeValue>(pNode);
        return data->value;
    }

    const ResourcePathList& list() const
    {
        if (pNode == nullptr || pNode->type != PathType::LIST)
            throw std::invalid_argument("PathNodeList invalid type!");

        auto data = std::static_pointer_cast<PathNodeList>(pNode);
        return data->values;
    }

    const ResourcePathNode key(std::string key) const
    {
        if (pNode == nullptr || pNode->type != PathType::DICT)
            throw std::invalid_argument("PathNodeDict invalid type!");

        auto data = std::static_pointer_cast<PathNodeDict>(pNode);
        auto it = data->values.find(key);

        if (it == data->values.end())
            throw std::invalid_argument("PathNode invalid type!");

        return { it->second };
    }

private:
    std::shared_ptr<BasePathNode> pNode;
};

//--------------------------------------------------------------------------

class ResourcePaths
{
public:
    static constexpr auto fonts = "fonts";
    static constexpr auto loadingScreens = "loading_screen";

    bool load(std::string file)
    {
        return false;
    }

    template<typename T>
    bool insert(std::string key, std::shared_ptr<T> node)
    {
        static_assert(std::is_base_of<BasePathNode, T>::value, "T must derive from BasePathNode");

        auto pair = m_data.emplace(key, ResourcePathNode(node));
        return pair.second;
    }

    const ResourcePathNode& node(std::string key)
    {
        auto it = m_data.find(key);
        if (it == m_data.end())
            throw std::invalid_argument("ResourcePathNode invalid type!");

        return it->second;
    }

private:
    std::map<std::string, ResourcePathNode> m_data;
};
