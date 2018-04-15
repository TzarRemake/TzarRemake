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

//--------------------------------------------------------------------------

#include "states/GameState.h"

//--------------------------------------------------------------------------

class StateMachine
{
public:
    template<class State, typename... Ts>
    void changeState(std::shared_ptr<State>&& state, Ts&&... args)
    {
        popState();
        pushState(std::forward<std::shared_ptr<State>>(state), std::forward<Ts>(args)...);
    }

    template<class State, typename... Ts>
    void pushState(std::shared_ptr<State>&& state, Ts&&... args)
    {
        if (!m_states.empty())
            m_states.back()->pause();

        state->init(std::forward<Ts>(args)...);
        m_waiting.push_back(std::forward<std::shared_ptr<State>>(state));
    }

    void popState()
    {
        if (!m_states.empty())
            m_waiting.push_back(nullptr);
    }

    void handleEvents(sf::Event& event)
    {
        for (auto &state : m_states)
            state->handleEvents(event);
    }

    void update(sf::Time& delta)
    {
        for (auto &state : m_states)
            state->update(delta);

        purge();
    }

    void clear()
    {
        int size = m_states.size();
        for (auto &state : m_states)
            state->shutdown();

        m_states.clear();
        m_waiting.clear();
    }

private:
    void purge()
    {
        for (auto &state : m_waiting)
        {
            if (state == nullptr)
            {
                m_states.back()->shutdown();
                m_states.pop_back();
            }
            else
                m_states.push_back(state);
        }

        m_waiting.clear();
    }

    std::vector<std::shared_ptr<GameState>> m_states;
    std::vector<std::shared_ptr<GameState>> m_waiting;
};
