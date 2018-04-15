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

#include "Widget.h"

//--------------------------------------------------------------------------

namespace gui
{
	/*!
	 * \brief EditBox GUI class
	 */
	class EditBox : public Widget
	{
	public:
		EditBox();
		~EditBox();
		EditBox(const EditBox & obj);
		EditBox(EditBox && obj);
		EditBox & operator=(EditBox & obj);
		EditBox & operator=(EditBox && obj);


		virtual void handleEvents(Event::EventType event) override;
		virtual void update() override;
		/*!
		* \brief Get center of widget in local coordinate system
		*/
		virtual sf::Vector2f getLocalCenter() const override;

	private:
	    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	    {

	    }

	};
}
