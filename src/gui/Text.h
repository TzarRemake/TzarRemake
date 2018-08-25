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
	* \brief This is wrapper class around sfml text class
	*/
	class Text : public sf::Text
	{
	public:
		/*!
		* \brief Default constructor
		*
		* \param widget Parent widget where text is positioned
		* \param textAligning Type of aligning with widget
		* \param offset Relative offset position of text applied after aligning
		*/
		Text(Widget * const widget, const sf::Font & font, TextAligning textAligning, const sf::Vector2f & offset = sf::Vector2f(0.f,0.f));
		~Text() = default;
		
		/*!
		* \brief Align text with widget boundary
		*
		* This function should be called after text string is set/changed or parent widget position/size is changed.
		*
		*/
		void align();

	private:
		Widget * m_widget;				///< Pointer to parent widget
		TextAligning m_textAligning;	///< Type of text aligning
		sf::Vector2f m_offset;			///< Offset position of text
	};
} // namespace gui

/*!
* \class gui::Text
*
* gui::Text can be used to put some text in relation with gui::widget objects or it's derived classes.  
* Text will be aligned in the way specified by parameter gui::TextAligning. Typical use for gui::Text is for stationary text
* and gui::widget objects. It's important to call align() method whenever something change position/size of text or parent widget.
*
*/