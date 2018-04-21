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

//--------------------------------------------------------------------------

#include <SFML/System.hpp>


//--------------------------------------------------------------------------

class GameEngine;

namespace sf
{
    class Event;
}

//--------------------------------------------------------------------------

class GameState
{
public:
    GameState(GameEngine& _engine) : engine(_engine) {}

    template<typename... Ts>
    void init(Ts&&... args) {}
    virtual void pause() = 0;
    virtual void shutdown() = 0;
    virtual void handleEvents(sf::Event& event) = 0;
    virtual void update(sf::Time& delta) = 0;

protected:
    GameEngine& engine;
};
