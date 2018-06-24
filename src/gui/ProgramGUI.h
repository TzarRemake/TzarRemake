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

#include <iostream>
#include <vector>

//--------------------------------------------------------------------------

#include "Button.h"
#include "Container.h"
#include "EditBox.h"
#include "../resources/ResourceManager.h"

//--------------------------------------------------------------------------

class GameState;
class GameEngine;

//--------------------------------------------------------------------------

namespace gui
{
	/*!
	* \brief Specify type of gui
	*/
	enum class GuiType
	{
		MAIN_MENU, ///< gui inside main menu
	};

	//--------------------------------------------------------------------------

	/*!
	 * \brief Class holding GUI
	 */
	class ProgramGUI
	{
	public:
		/*!
		 * \brief Create all gui elements inside gui::Container
		 *
		 * This is main constructor of gui. sf::Rect parameter specify range in which gui objects
		 * will be drawed on main window. For best memory usage,  area of this rectangle 
		 * should be as low as possible.
		 *
		 * \param state Pointer to state which created and hold this gui instance
		 * \param engine Pointer to main game engine
		 * \param gType Type of created gui
		 * \param mhType Algorithm used to search for appropriate widget with mouse events
		 *
		 * \see gui::Container
		 *
		 */
		ProgramGUI(GameState * state, GameEngine * engine,
			GuiType gType = GuiType::MAIN_MENU, MouseHandlingType mhType = MouseHandlingType::SEARCH_BOUNDARY);

		~ProgramGUI();

		ProgramGUI(const ProgramGUI & obj) = delete;		///< Deleted copy constructor
		ProgramGUI(ProgramGUI && obj) = delete;				///< Deleted move constructor
		ProgramGUI & operator=(ProgramGUI & obj) = delete;	///< Deleted assignement operator
		ProgramGUI & operator=(ProgramGUI && obj) = delete;	///< Deleted move assignement operator

		/*!
		* \brief Handle event for gui
		*
		* \param event Reference to sfml event
		*
		*/
		void handleEvent(sf::Event & event);

		/*!
		* \brief Update all GUI objects according to passed time
		*
		* This function should be called in every update iteration of program in order
		* to refresh logic inside all gui objects.
		*
		* \param delta Reference to time object which indicates time which passed since last update call
		*
		*/
		void update(sf::Time& delta);

		/*!
		 * \brief Draw all GUI objects
		 *
		 * This function should be called in every draw iteration of program in order to refresh
		 * all GUI objects which appear on main program window.
		 *
		 * \param window Reference to window object where drawing happens
		 *
		 */
		void draw(sf::RenderWindow & window);

		/*!
		* \brief Change actually managed and drawed container to new one choosen in handleEvent phase
		*
		* This function should be used in every program iteration in update phase. This ensures that changes to actually used
		* container submenu are submitted.
		*
		*/
		void updateContainer();

		


		/*!
		* \brief Change actually active container
		*
		* This function should be used to change m_container iterator.
		*
		* \param newContainer Id of new active container
		*
		*/
		//void changeContainer(state::MenuContainerID containerID);

	private:
		GameEngine * m_engine;				///< Pointer to program engine which initialized this GUI object
		GameState * m_state;				///< Pointer to program state which initialized this GUI object

		std::vector<gui::Container> m_containers;			///< Main gui vector of containers objects which hold all other widgets
		std::vector<gui::Container>::iterator m_container;	///< Iterator to actuallly used gui container
		volatile int m_newContainerID{0};					///< Index of container which will be used in next program iteration

		ResourceManager<MAIN_RESOURCES> resources;	///< Recources manager (fonts, textures, etc..)
	};
}

/*!
 * \class gui::ProgramGUI
 *
 * gui::ProgramGUI Gather all GUI objects which are used to communicate with user.
 *
 */
