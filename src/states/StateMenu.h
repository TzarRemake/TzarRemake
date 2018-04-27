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

#include "GameState.h"
#include "../gui/ProgramGUI.h"

//--------------------------------------------------------------------------

namespace state
{
	/*!
	* \brief Submenu id
	*/
	enum MenuContainerID
	{
		MAIN_MENU = 0,
		SINGLE_PLAYER,
		MULTI_PLAYER,
		OPTIONS,
		EXIT,
	};

	//--------------------------------------------------------------------------

	class Menu : public GameState
	{
	public:
		Menu(GameEngine& engine) : GameState(engine) {}

		void init();
		virtual void pause() override {}
		virtual void handleEvents(sf::Event& event) override;
		virtual void shutdown() override;
		virtual void update(sf::Time& delta) override;

	private:
		std::unique_ptr<gui::ProgramGUI> m_guiObject;	///< gui for menu
	};
}