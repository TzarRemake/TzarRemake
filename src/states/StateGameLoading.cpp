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

//--------------------------------------------------------------------------

#include <random>

//--------------------------------------------------------------------------

#include "../GameEngine.h"
#include "StateGameLoading.h"
#include "StateGameplay.h"

//--------------------------------------------------------------------------

using namespace state;

//--------------------------------------------------------------------------

void GameLoading::init()
{
    auto font = engine.resources.holder<sf::Font>().get("main");
    auto textures = engine.resources.holder<sf::Texture>().list("screen");

    // Get random texture
    auto texId = rand() % textures.size();
    auto size = engine.window()->getSize();

    m_loadingScreen.setFont(*font);
    m_loadingScreen.setTexture(*textures.at(texId));
    m_loadingScreen.updateView(size.x, size.y);
    m_loadingScreen.setStatus("Generating terrain...");
}

//--------------------------------------------------------------------------

void GameLoading::handleEvents(sf::Event& event)
{
    m_loadingScreen.handleEvents(event);
}

//--------------------------------------------------------------------------

void GameLoading::shutdown()
{
}

//--------------------------------------------------------------------------

void GameLoading::update(sf::Time& delta)
{
    engine.window()->draw(m_loadingScreen);
    //engine.machine.changeState(std::make_shared<state::Gameplay>(engine));
}
