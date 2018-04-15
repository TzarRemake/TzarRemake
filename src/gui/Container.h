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
#include "Matrix.h"
#include "Button.h"

//--------------------------------------------------------------------------

namespace gui
{
	/*!
	 * \brief Container GUI class
	 *
	 * Object of this class hold information about all other GUI objects which derive from gui::Widget class.
	 *
	 */
	class Container : public Widget
	{
	public:
		/*!
		* \brief Container constructor
		*
		* \param mhType Algorithm used to search for appropriate widget with mouse events
		*
		*/
		Container(MouseHandlingType mhType);
		~Container();
		Container(Container && obj);

		/*!
		* \brief Initialize container
		*
		* This function validate iterators and should be called whenever vector of widgets reallocation takes place.
		*
		*/
		void init();

		void handleEvents(sf::Event& event);

		virtual void handleEvents(Event::EventType event) override;

		virtual void update() override;

		/*!
		* \brief Get center of widget in local coordinate system
		*/
		virtual sf::Vector2f getLocalCenter() const override;

		/*!
		* \brief Get iterator to widget
		*
		* This function return iterator
		*
		* \param position Position on the window
		* \return Iterator to widget
		*
		*/
		std::vector<std::unique_ptr<gui::Widget>>::iterator getWidget(sf::Vector2i position);

		/*!
		 * \brief This function can add gui::Widget object to container
		 */
		template<class T>
		void attachObject(std::unique_ptr<T> widget)
		{
			assert((std::is_base_of<Widget, T>::value) == true );
			sf::Rect<float> bounds = widget->getGlobalBounds();

			// check if new widget boundaries exceed global menu boundaries
			if (bounds.left < m_boundary.left)
				m_boundary.left = bounds.left;
			if (bounds.top < m_boundary.top)
				m_boundary.top = bounds.top;

			m_boundaries.push_back(static_cast<sf::Rect<int>>(bounds));

			// check if new widget boundaries exceed global menu boundaries
			if ((bounds.left + bounds.width) > (m_boundary.left + m_boundary.width))
				m_boundary.width = bounds.width + bounds.left - m_boundary.left;
			if ((bounds.top + bounds.height) > (m_boundary.top + m_boundary.height))
				m_boundary.height = bounds.width + bounds.top - m_boundary.top;

			m_Children.push_back(std::move(widget));
		}

		/*!
		* \brief Set brackground sprite
		*/
		void setBackground(const sf::Texture & texture)
		{
			m_background.setTexture(texture);
		}

	private:
	    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	    {
			target.draw(m_background);
	    	for(auto & m: m_Children)
	    	{
	    		target.draw(*m);
	    	}
	    }

		MouseHandlingType m_mhType;
		sf::Sprite m_background;											///< Background sprite
	    std::vector<std::unique_ptr<gui::Widget>> m_Children;				///< Storage for all widgets

		std::vector<sf::Rect<int>> m_boundaries;							///< Rectangle boundaries for all widgets
		sf::Rect<int> m_boundary{sf::Rect<int>(WIN_WIDTH,WIN_HEIGHT,0,0)};	///< Rectangle boundary for menu

		std::vector<std::unique_ptr<gui::Widget>>::iterator m_hoveredWidget; ///< iterator to actually hovered Widget
		std::vector<std::unique_ptr<gui::Widget>>::iterator m_clickedWidget; ///< iterator to actually clicked Widget
	};
}
