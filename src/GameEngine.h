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
#include <utility>
#include <SFML/Graphics.hpp>

//--------------------------------------------------------------------------

#include "StateMachine.h"
#include "ResourceManager.h"

//--------------------------------------------------------------------------

class GameEngine final
{
public:
    inline std::unique_ptr<sf::RenderWindow>& window() { return m_pWindow; }

    void shutdown();
    int run();

    StateMachine machine;
    ResourceManager<RESOURCES> resources;

private:
    void init();
    void handleEvents(sf::Event& event);
    void update();

    std::unique_ptr<sf::RenderWindow> m_pWindow;

    sf::Clock m_clock;
    bool m_fullscreen = false;
};
