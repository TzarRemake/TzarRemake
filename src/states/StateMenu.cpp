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

//--------------------------------------------------------------------------

namespace state
{
	void Menu::init()
	{
		// create GUI
		m_guiObject = std::make_unique<gui::ProgramGUI>(this, &engine, gui::GuiType::MAIN_MENU, gui::MouseHandlingType::SEARCH_BOUNDARY);
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
		//eh::Event event;
		//while (m_eventHandler.pullEvent(event))
		//{
		//	m_guiObject->handleEvent(event);
		//}

		m_guiObject->draw(*engine.window());
	}

	//--------------------------------------------------------------------------

	bool Menu::loadTexture(tls::TextureID texID, const std::string & strTex, bool isAlphaMaska, sf::Color alphaMask)
	{
		try
		{
			std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();

			// load texture into textureHolder
			if (isAlphaMaska == false)
			{
				m_textureHolder.load(texID, strTex);
			}
			// load texture into textureHolder with mask
			else
			{
				sf::Image image;
				if (!image.loadFromFile(strTex))
					throw std::runtime_error("Menu::loadTexture() - Failed to load "
						+ strTex);
				image.createMaskFromColor(alphaMask);
				if (!texture->loadFromImage(image))
					throw std::runtime_error("Menu::loadTexture() - Failed to load "
						+ strTex);
				m_textureHolder.add(texID, std::move(texture));
			}
		}
		catch (...)
		{
			return false;
		}
		return true;
	}
}