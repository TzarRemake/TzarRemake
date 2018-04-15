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

#include "EditBox.h"

//--------------------------------------------------------------------------

namespace gui
{

	EditBox::EditBox()
	{
		std::cout << "EditBox constructor working" << std::endl;
	}

	//--------------------------------------------------------------------------

	EditBox::~EditBox()
	{
		std::cout << "EditBox destructor working" << std::endl;
	}

	//--------------------------------------------------------------------------

	void EditBox::handleEvents(Event::EventType event)
	{

	}

	//--------------------------------------------------------------------------

	void EditBox::update()
	{

	}

	//--------------------------------------------------------------------------

	sf::Vector2f EditBox::getLocalCenter() const
	{
		return sf::Vector2f(0,0);
	}
}
