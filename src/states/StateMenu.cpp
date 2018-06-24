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

#include "StateMenu.h"
#include "../GameEngine.h"

#include <thread>

//--------------------------------------------------------------------------

namespace state
{
	void Menu::init()
	{
		// create GUI
		m_guiObject = std::make_unique<gui::ProgramGUI>(this, &engine, gui::GuiType::MAIN_MENU, gui::MouseHandlingType::SEARCH_BOUNDARY);
		auto font = engine.resources.holder<sf::Font>().get("main");
		tester::Timer<tester::TimerID::StateMenu>::init(engine.window().get(), *font);
		tester::Timer2<tester::TimerID::StateMenu>::init(engine.window().get(), *font);
	}

	//--------------------------------------------------------------------------

	void Menu::handleEvents(sf::Event& event)
	{
		//m_eventHandler.processEvent(event);
		m_guiObject->handleEvent(event);
	}

	//--------------------------------------------------------------------------

	void Menu::shutdown()
	{
	}

	//--------------------------------------------------------------------------

	void Menu::update(sf::Time& delta)
	{
		m_guiObject->update(delta);
		m_guiObject->draw(*engine.window());

		//-- Timers for fps/frame time
		tester::Timer<tester::TimerID::StateMenu> timer = tester::Timer<tester::TimerID::StateMenu>();
		//tester::Timer2<tester::TimerID::StateMenu> timer2 = tester::Timer2<tester::TimerID::StateMenu>();
		//--

		m_guiObject->updateContainer(); // Update actually used GUI submenu container
	}
}