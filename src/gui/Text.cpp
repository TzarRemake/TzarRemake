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

#include "Text.h"

//--------------------------------------------------------------------------

namespace gui
{
	Text::Text(Widget * const widget, TextAligning textAligning) :
		m_widget{ widget }, m_textAligning{ textAligning }
	{
	}
	
	//--------------------------------------------------------------------------

	void Text::align()
	{
		switch (m_textAligning)
		{
			case TextAligning::CENTER:
			{
				sf::Rect<float> bounds = getLocalBounds();
				sf::Vector2f position = m_widget->getLocalCenter();
				position.x = position.x - bounds.width / 2.f;
				position.y = position.y - bounds.height / 2.f;
				setPosition(position + m_offset);
				break;
			}
		}
	}
}
