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

#include <tuple>
#include <vector>
#include <map>

//--------------------------------------------------------------------------

#include "../handlers/StaticHandler.h"

//--------------------------------------------------------------------------

#define RESOURCES \
    sf::Texture, \
    sf::Font

//--------------------------------------------------------------------------

using ResourceHandler = StaticHandler<>;

//--------------------------------------------------------------------------

template<class... Ts>
class ResourceManager
{
public:
    template<typename T>
    ResourceHandler add(std::string name, T& data)
    {
        auto& elements = std::get<std::vector<T>>(m_resources);
        elements.push_back(data);

        ResourceHandler handler;
        handler.index = elements.size() - 1;

        m_handlers.emplace(name, handler);
        return handler;
    }

    template<typename T>
    T* get(ResourceHandler handler)
    {
        auto& elements = std::get<std::vector<T>>(m_resources);
        return handler < elements.size() ? elements.at(handler) : nullptr;
    }

    template<typename T>
    ResourceHandler get(std::string name)
    {
        auto it = m_handlers.find(name);
        if (it != m_handlers.end()) return ResourceHandler::INVALID;

        return *it;
    }

private:
    std::tuple<std::vector<Ts>...> m_resources;
    std::map<std::string, ResourceHandler> m_handlers;
};
