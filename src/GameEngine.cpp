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

#include <ctime>
#include <SFML/OpenGL.hpp>

//--------------------------------------------------------------------------

#include "GameEngine.h"
#include "states/StateGameLoading.h"

//--------------------------------------------------------------------------

int GameEngine::run()
{
    init();

    while (m_pWindow->isOpen())
    {
        sf::Event event;
        while (m_pWindow->pollEvent(event))
            handleEvents(event);

        m_pWindow->clear();
        update();
        m_pWindow->display();
    }

    return 0;
}

//--------------------------------------------------------------------------
#include <iostream>
void GameEngine::init()
{
    // Restart seed
    std::srand(std::time(nullptr));

    m_pWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "TzarRemake");

    // Testing resources data
    auto fonts = std::make_shared<PathNodeDict>();
    fonts->values.emplace("main", std::make_shared<PathNodeValue>("resources/fonts/Tahoma.ttf"));

    auto screens = std::make_shared<PathNodeList>();
    screens->values.push_back("resources/IMAGES/IMAGES/SCREENS/WAITSCR/SCREEN.BMP");
    screens->values.push_back("resources/IMAGES/IMAGES/SCREENS/WAITSCR/SCREEN1.BMP");
    screens->values.push_back("resources/IMAGES/IMAGES/SCREENS/WAITSCR/SCREEN2.BMP");
    screens->values.push_back("resources/IMAGES/IMAGES/SCREENS/WAITSCR/SCREEN3.BMP");
    screens->values.push_back("resources/IMAGES/IMAGES/SCREENS/WAITSCR/SCREEN4.BMP");
    screens->values.push_back("resources/IMAGES/IMAGES/SCREENS/WAITSCR/SCREEN5.BMP");
    screens->values.push_back("resources/IMAGES/IMAGES/SCREENS/WAITSCR/SCREEN6.BMP");

    paths.insert("fonts", fonts);
    paths.insert("loading_screen", screens);

    machine.changeState(std::make_shared<state::GameLoading>(*this));
}

//--------------------------------------------------------------------------

void GameEngine::shutdown()
{
    m_pWindow = nullptr;
}

//--------------------------------------------------------------------------

void GameEngine::handleEvents(sf::Event& event)
{
    machine.handleEvents(event);

    switch (event.type)
    {
    case sf::Event::KeyReleased:
        switch (event.key.code)
        {
        case sf::Keyboard::Escape:
            m_pWindow->close();
            break;
        }
        break;

    case sf::Event::Resized:
        {
            sf::FloatRect viewSize(0.f, 0.f, event.size.width, event.size.height);
            m_pWindow->setView(sf::View(viewSize));
        }
        break;

    case sf::Event::Closed:
        m_pWindow->close();
        break;
    }
}

//--------------------------------------------------------------------------

void GameEngine::update()
{
    auto elapsed = m_clock.restart();
    machine.update(elapsed);

    sf::View view({ 0.f, 0.f, 800.f, 600.f });
    m_pWindow->setView(view);
}
