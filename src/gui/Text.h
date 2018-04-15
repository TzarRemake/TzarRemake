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

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//--------------------------------------------------------------------------

#include "Widget.h"

//--------------------------------------------------------------------------

namespace gui
{
	/*!
	* \brief Type of text aligning
	*/
	enum class TextAligning
	{
		CENTER,	///< position text in center of widget
	};

	//--------------------------------------------------------------------------

	/*!
	* \brief This is wrapper class around text to use with widgets
	*/
	class Text : public sf::Text
	{
	public:
		Text(Widget * const widget, TextAligning textAligning);
		~Text() = default;
		
		/*!
		* \brief align text with widget boundary
		*/
		void align();

	private:
		Widget * m_widget;				///< Pointer to widget
		TextAligning m_textAligning;	///< Type of text aligning
		sf::Vector2f m_offset;			///< Offset position of text
	};
}
