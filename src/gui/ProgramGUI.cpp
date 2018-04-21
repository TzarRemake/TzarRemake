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

#include "ProgramGUI.h"
#include "../GameEngine.h"
#include "../resources/ResourceLoader.h"

//--------------------------------------------------------------------------

namespace gui
{
	ProgramGUI::ProgramGUI(GameState * state, GameEngine * engine,
		GuiType gType, MouseHandlingType mhType) :
		m_engine{ engine }, m_state{ state }
	{
		std::cout << "ProgramGUI constructor running!" << std::endl;

		switch (gType)
		{
			case GuiType::MAIN_MENU:
			{
				// load Textures
				auto& textures = resources.holder<sf::Texture>();
				std::string texture0_str{ "./resources/IMAGES/IMAGES/SCREENS/S_MAIN/BACK.bmp" };
				std::string texture1_str{ "./resources/IMAGES/IMAGES/SCREENS/S_MAIN/BTN.bmp" };
				textures.load("MAIN_MENU_BACK", Resource::loadFromFile<sf::Texture>(texture0_str));
				textures.load("MAIN_MENU_BTN", Resource::loadFromFile<sf::Texture>(texture1_str));
				textures.load("S_SINGLEPLAYER_BACK", Resource::loadFromFile<sf::Texture>("./resources/IMAGES/IMAGES/SCREENS/S_SINGLEPLAYER/BACK.bmp"));
				textures.load("S_SINGLEPLAYER_BTN", Resource::loadFromFile<sf::Texture>("./resources/IMAGES/IMAGES/SCREENS/S_SINGLEPLAYER/BTN.bmp"));

				// load fonts
				auto& fonts = resources.holder<sf::Font>();
				fonts.load("FONT_TAHOME", Resource::loadFromFile<sf::Font>("./resources/fonts/Tahoma.ttf"));



				//--------------------------------------- Container 1 - MAIN MENU --------------------------------------------------------//

				m_containers.push_back(gui::Container(mhType));

				// set background initial sprite
				m_containers.back().setBackground(*resources.holder<sf::Texture>().get("MAIN_MENU_BACK"));

				// button_SinglePlayer
				auto button_1 = std::make_unique<gui::Button>(sf::Vector2f(235.f, 25.f), sf::Color(255, 255, 255));
				button_1->setPosition(sf::Vector2f(270.f, 277.f));
				button_1->initText("Single Player", *resources.holder<sf::Font>().get("FONT_TAHOME"), TextAligning::CENTER, sf::Vector2f(0.f, -2.f), 13, sf::Text::Bold, sf::Color(188, 188, 0));
				button_1->setResources(resources.holder<sf::Texture>().get("MAIN_MENU_BTN").get(), sf::Rect<int>(0, 0, 235, 25));
				button_1->setIsTextureClickable(true, resources.holder<sf::Texture>().get("MAIN_MENU_BTN").get(), sf::Rect<int>(236,0,235,25));
				button_1->setTextColorHoverable(true, sf::Color(255,255,55));
				button_1->setCallBack([this]() {
					std::cout << "Button callback function change to Single Player: " << std::endl;
					m_containerID = SINGLE_PLAYER;
				});
				m_containers.back().attachObject(std::move(button_1));

				// button_2
				auto button_2 = std::make_unique<gui::Button>(sf::Vector2f(235.f, 25.f), sf::Color(255, 255, 255));
				button_2->setPosition(sf::Vector2f(270.f, 277.f+60.f)); // declaring position of button in local gui coordinates bounded to window coordinate system
				button_2->initText("Multiplayer", *resources.holder<sf::Font>().get("FONT_TAHOME"), TextAligning::CENTER, sf::Vector2f(0.f, -2.f), 13, sf::Text::Bold, sf::Color(188, 188, 0));
				button_2->setResources(resources.holder<sf::Texture>().get("MAIN_MENU_BTN").get(), sf::Rect<int>(0, 0, 235, 25));
				button_2->setIsTextureClickable(true, resources.holder<sf::Texture>().get("MAIN_MENU_BTN").get(), sf::Rect<int>(236, 0, 235, 25));
				button_2->setTextColorHoverable(true, sf::Color(255, 255, 55));
				button_2->setCallBack([this]() {
					std::cout << "Button callback function change to Multiplayer: " << std::endl;
				});
				m_containers.back().attachObject(std::move(button_2));

				// button_3
				auto button_3 = std::make_unique<gui::Button>(sf::Vector2f(235.f, 25.f), sf::Color(255, 255, 255));
				button_3->setPosition(sf::Vector2f(270.f, 277.f+120.f)); // declaring position of button in local gui coordinates bounded to window coordinate system
				button_3->initText("Options", *resources.holder<sf::Font>().get("FONT_TAHOME"), TextAligning::CENTER, sf::Vector2f(0.f, -2.f), 13, sf::Text::Bold, sf::Color(188, 188, 0));
				button_3->setResources(resources.holder<sf::Texture>().get("MAIN_MENU_BTN").get(), sf::Rect<int>(0, 0, 235, 25));
				button_3->setIsTextureClickable(true, resources.holder<sf::Texture>().get("MAIN_MENU_BTN").get(), sf::Rect<int>(236, 0, 235, 25));
				button_3->setTextColorHoverable(true, sf::Color(255, 255, 55));
				button_3->setCallBack([this]() {
					std::cout << "Button callback function change to Options: " << std::endl;
				});
				m_containers.back().attachObject(std::move(button_3));

				// button_4
				auto button_4 = std::make_unique<gui::Button>(sf::Vector2f(235.f, 25.f), sf::Color(255, 255, 255));
				button_4->setPosition(sf::Vector2f(270.f, 277.f+240.f)); // declaring position of button in local gui coordinates bounded to window coordinate system
				button_4->initText("Exit", *resources.holder<sf::Font>().get("FONT_TAHOME"), TextAligning::CENTER, sf::Vector2f(0.f, -2.f), 13, sf::Text::Bold, sf::Color(188, 188, 0));
				button_4->setResources(resources.holder<sf::Texture>().get("MAIN_MENU_BTN").get(), sf::Rect<int>(0, 0, 235, 25));
				button_4->setIsTextureClickable(true, resources.holder<sf::Texture>().get("MAIN_MENU_BTN").get(), sf::Rect<int>(236, 0, 235, 25));
				button_4->setTextColorHoverable(true, sf::Color(255, 255, 55));
				button_4->setCallBack([this]() {
					exit(EXIT_SUCCESS);
				});
				m_containers.back().attachObject(std::move(button_4));

				/////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////



				//--------------------------------------- Container 2 - Single Player -----------------------------------------------------//

				m_containers.push_back(gui::Container(mhType));

				// set background initial sprite
				m_containers.back().setBackground(*resources.holder<sf::Texture>().get("S_SINGLEPLAYER_BACK"));

				// button_return
				auto button_S1 = std::make_unique<gui::Button>(sf::Vector2f(235.f, 25.f), sf::Color(255, 255, 255));
				button_S1->setPosition(sf::Vector2f(299.f, 141.f + 381.f));	// 1- 299/93
				button_S1->initText("Return", *resources.holder<sf::Font>().get("FONT_TAHOME"), TextAligning::CENTER, sf::Vector2f(0.f, -2.f), 13, sf::Text::Bold, sf::Color(188, 188, 0));
				button_S1->setResources(resources.holder<sf::Texture>().get("S_SINGLEPLAYER_BTN").get(), sf::Rect<int>(0, 0, 235, 25));
				button_S1->setIsTextureClickable(true, resources.holder<sf::Texture>().get("S_SINGLEPLAYER_BTN").get(), sf::Rect<int>(236, 0, 235, 25));
				button_S1->setTextColorHoverable(true, sf::Color(255, 255, 55));
				button_S1->setCallBack([this]() {
					std::cout << "Button callback Return to Main Menu: " << std::endl;
					m_containerID = MAIN_MENU;
				});
				m_containers.back().attachObject(std::move(button_S1));

				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////////

				// initialize actually used container
				m_container = m_containers.begin();
				break;
			}
		}

		for (auto & c : m_containers)
		{
			c.init();
		}
	}

	//--------------------------------------------------------------------------

	ProgramGUI::~ProgramGUI()
	{
		std::cout << "ProgramGUI constructor running!" << std::endl;
	}

	//--------------------------------------------------------------------------

	void ProgramGUI::draw(sf::RenderWindow & window)
	{
		window.setActive(true);
		//window.setView(window.getDefaultView());
		window.draw(*m_container);
	}

	//--------------------------------------------------------------------------

	void ProgramGUI::handleEvent(sf::Event & event)
	{
		m_container->handleEvents(event);
	}

	//--------------------------------------------------------------------------

	void ProgramGUI::updateContainer()
	{
		if(m_containerID >= 0)
			m_container = m_containers.begin() + m_containerID;
	}

	//bool ProgramGUI::loadTexture(tls::TextureID texID, const std::string & strTex, bool isAlphaMaska, sf::Color alphaMask)
	//{
	//	try
	//	{
	//		std::unique_ptr<sf::Texture> texture = std::make_unique<sf::Texture>();

	//		// load texture into textureHolder
	//		if (isAlphaMaska == false)
	//		{
	//			m_textureHolder.load(texID, strTex);
	//		}
	//		// load texture into textureHolder with mask
	//		else
	//		{
	//			sf::Image image;
	//			if (!image.loadFromFile(strTex))
	//				throw std::runtime_error("sf::Image::loadFromFile() - Failed to load "
	//					+ strTex);
	//			image.createMaskFromColor(alphaMask);
	//			if (!texture->loadFromImage(image))
	//				throw std::runtime_error("sf::Image::loadFromImage() - Failed to load "
	//					+ strTex);
	//			m_textureHolder.add(texID, std::move(texture));
	//		}
	//	}
	//	catch (std::exception & e)
	//	{
	//		std::cout << "ProgramGUI::loadTexture() failed: " << e.what() << std::endl;
	//		auto func = atexit([]() { 
	//			std::cout << "Press enter to terminate program... " << std::endl;
	//			std::cin.get(); 
	//		});
	//		exit(EXIT_FAILURE);
	//	}
	//	return true;
	//}
}
