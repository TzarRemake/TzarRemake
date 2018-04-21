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
#include "../tester/timer.h"

//--------------------------------------------------------------------------

namespace state
{

	class Menu : public GameState
	{
	public:
		Menu(GameEngine& engine) : GameState(engine) {}

		void init();
		virtual void pause() override {}
		virtual void handleEvents(sf::Event& event) override;
		virtual void shutdown() override;
		virtual void update(sf::Time& delta) override;

		/*!
		* \brief Load texture into texture holder
		*
		* \param textId Id of texture
		* \param strTex Reference to const string which holds relative path to texture resource file
		* \param isAlphaMaska Indicates if alphaMask variable is used
		* \param alphaMask This is color which is extruded from texture
		*
		* \return Return true if texture was succesfully loadedk, otherwise return false
		*
		*/
		//bool loadTexture(tls::TextureID texID, const std::string & strTex, bool isAlphaMaska = false, sf::Color alphaMask = sf::Color(0, 0, 0));

	private:
		std::unique_ptr<gui::ProgramGUI> m_guiObject;	///< gui for menu
		//TextureHolder m_textureHolder;					///< texture holder
	};
}