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

#include <vector>

//--------------------------------------------------------------------------

#include "../logic/Delegate.h"

//--------------------------------------------------------------------------

namespace gui
{
	/*!
	 * \brief Class which holds all information about raised event
	 */
	class EventArgs
	{
	public:
		/*!
		 *	\brief Structure holding 2 int values
		 */
		struct Vector2i
		{
			int x;
			int y;
		};

		/*!
		 *	\brief Structure holding 4 int values
		 */
		struct Vector4i
		{
			int x1;
			int y1;
			int x2;
			int y2;
		};

		/*!
		 * \brief Specify all possible event types for widgets
		 */
		enum class EventType
		{
			// Events send to widgets as messages
			startHover,	///< start hovering widget		
			stopHover,	///< stop hovering widget
			startClick,	///< start click widget
			stopClick,	///< stop click widget
			click,		///< click widget

			// Events subscribed and catched by all listeners 
			leftMouseDown,	///< left mouse down
			UnicodeEntered,	///< indicates that user entered unicode character on keyboard
		};

		EventType type;			///< specify event type of the object
		void * widgetPointer;	///< Pointer to choosen widget

		/*!
		 * \brief This union specify additional event information
		 */
		union
		{
			char character;				///< character
			unsigned int unicodeCharacter; ///< unicode character
			//Vector2i globalPosition2i; 	///< position on the window(grid)
			//Vector4i globalPosition4i; 	///< two positions on the window(grid)
		};
	};

	//--------------------------------------------------------------------------

	/*!
	* \brief Class for GUI Events
	*/
	class GuiEvent
	{
	public:
		GuiEvent() = default;
		~GuiEvent() noexcept { }
		GuiEvent(const GuiEvent & obj) = delete;		///< Deleted copy constructor
		GuiEvent(GuiEvent && obj) = delete;				///< Deleted move constructor
		GuiEvent & operator=(GuiEvent & obj) = delete;	///< Deleted assignement operator
		GuiEvent & operator=(GuiEvent && obj) = default;///< Move assignement operator

		/*!
		* \brief Raise event
		*
		* This is overloaded operator() which subscribe event and inform all listeners.
		*
		* \param sender Pointer to object which subscribes event
		* \param args Reference to additional arguments send by subscriber
		*
		*/
		void operator()(void * sender, const EventArgs & args)
		{
			for (auto & d : m_delegates)
			{
				d(sender, &args);
			}
		}

		/*!
		* \brief Add delegate function to vector of delegates
		*
		* \param delegate Delegate object added to vector of listeners 
		*
		*/
		void operator += (const logic::Delegate<void(void*, const EventArgs*)> & delegate)
		{
			m_delegates.emplace_back(delegate);
		}

	private:
		std::vector<logic::Delegate<void(void*, const EventArgs*)>> m_delegates; ///< Vector of all delegate functions to call when event is raised
	};
} // namespace gui

/*!
* \class gui::GuiEvent
*
* gui::GuiEvent is class which handle event driven programming technique.
* In order to use events there is couple mandatory things to do:
* - Declare gui::GuiEvent object inside class which will raise event (subscriber class) as a public member. Standard is to use name which indicate type of event
*   for example leftMouseClicked. Public access allow other objects to listen to this event.
* - Define method which takes const reference to gui::EventArgs as paremeter and return void inside class which will raise event as a protected member.
*	Inside this function there should be call to operator() over apropriate gui::GuiEvent object. Function definition can
*	look like this:
*	\code
* void onLeftMouseClicked(const gui::EventArgs & args)
* {
*	leftMouseClicked(this, args);
* }
*	\endcode
* - Define method which takes void pointer and const pointer to gui::EventArgs as paremeters and return void. This function should be defined inside class
*	which wants to listen to raised event.
*	Function definition can look like this:
*	\code
* void onLeftMouseClicked(void * sender, const gui::EventArgs * args)
* {
* ...
* }
*	\endcode
* - Create logic::Delegate from this method and add it to gui::EventHandler by operator+
* - In order to raise event create gui::EventArgs local object and call protected method inside subscriber class object.
*/