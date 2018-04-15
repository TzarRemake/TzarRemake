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

namespace gui
{

	/*!
	 * \brief Class which holds all information about event
	 */
	class Event
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
			startHover,	///< start hovering widget		
			stopHover,	///< stop hovering widget
			startClick,	///< start click widget
			stopClick,	///< stop click widget
			click,		///< click widget
		};

		EventType type;			///< specify event type of the object

		/*!
		 * \brief This union specify additional event information
		 */
		union
		{
			Vector2i globalPosition2i; 	///< position on the window(grid)
			Vector4i globalPosition4i; 	///< two positions on the window(grid)
		};
	};

	//--------------------------------------------------------------------------

	class EventHandler
	{
	public:
		EventHandler() = default;
		~EventHandler() = default;
	};
}
