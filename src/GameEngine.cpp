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
#include "resources/ResourceLoader.h"
#include "states/StateGameLoading.h"

//--------------------------------------------------------------------------

int GameEngine::run()
{
    init();

    while (m_pWindow->isOpen())
    {
        sf::Event event;
		//m_pWindow.get()->pollEvent(event);
		//m_pWindow->pollEvent(event);
        while (m_pWindow->pollEvent(event))
            handleEvents(event);

        m_pWindow->clear();
        update();
        m_pWindow->display();
    }

    shutdown();
    return 0;
}

//--------------------------------------------------------------------------

void GameEngine::init()
{
    // Restart seed
    std::srand(std::time(nullptr));

    m_pWindow = std::make_unique<sf::RenderWindow>(sf::VideoMode(800, 600), "TzarRemake");

    // Testing resources data
    auto fontsPaths = std::make_shared<PathNodeDict>();
    fontsPaths->values.emplace("main", std::make_shared<PathNodeValue>("resources/fonts/Tahoma.ttf"));

    auto screens = std::make_shared<PathNodeList>();
    screens->values.push_back("resources/IMAGES/IMAGES/SCREENS/WAITSCR/SCREEN.BMP");
    screens->values.push_back("resources/IMAGES/IMAGES/SCREENS/WAITSCR/SCREEN1.BMP");
    screens->values.push_back("resources/IMAGES/IMAGES/SCREENS/WAITSCR/SCREEN2.BMP");
    screens->values.push_back("resources/IMAGES/IMAGES/SCREENS/WAITSCR/SCREEN3.BMP");
    screens->values.push_back("resources/IMAGES/IMAGES/SCREENS/WAITSCR/SCREEN4.BMP");
    screens->values.push_back("resources/IMAGES/IMAGES/SCREENS/WAITSCR/SCREEN5.BMP");
    screens->values.push_back("resources/IMAGES/IMAGES/SCREENS/WAITSCR/SCREEN6.BMP");

    paths.insert("fonts", fontsPaths);
    paths.insert("loading_screen", screens);

    auto& textures = resources.holder<sf::Texture>();
    textures.load("screen", Resource::loadFromFile<sf::Texture>(screens->values.at(0)));
    textures.load("screen", Resource::loadFromFile<sf::Texture>(screens->values.at(1)));
    textures.load("screen", Resource::loadFromFile<sf::Texture>(screens->values.at(2)));
    textures.load("screen", Resource::loadFromFile<sf::Texture>(screens->values.at(3)));
    textures.load("screen", Resource::loadFromFile<sf::Texture>(screens->values.at(4)));
    textures.load("screen", Resource::loadFromFile<sf::Texture>(screens->values.at(5)));

    auto& fonts = resources.holder<sf::Font>();
    fonts.load("main", Resource::loadFromFile<sf::Font>(paths.node("fonts").key("main").value()));

    machine.changeState(std::make_shared<state::GameLoading>(*this));
}

//--------------------------------------------------------------------------

void GameEngine::shutdown()
{
    machine.clear();

    resources.holder<sf::Texture>().clear();
    resources.holder<sf::Font>().clear();

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
            sf::FloatRect viewRect(0.f, 0.f, event.size.width, event.size.height);
            m_view.reset(viewRect);
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

    m_pWindow->setView(m_view);
}
