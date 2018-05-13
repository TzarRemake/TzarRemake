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
#include "GuiAllocators.h"
#include "../tester/timer.h"

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

		//--------------------------------------------------------------------------

		virtual void handleCommand(CommandHandler * const sender, const CommandArgs  & args) override;

		virtual void update(sf::Time& delta) override;

		/*!
		* \brief Get center of widget in local coordinate system
		*/
		virtual sf::Vector2f getLocalCenter() const override;

		//--------------------------------------------------------------------------

		/*!
		* \brief Initialize container
		*
		* This function validate iterators and should be called whenever vector of widgets reallocation takes place.
		*
		*/
		void init();

		void handleEvents(sf::Event& event);

		/*!
		* \brief Restart container to it's initial state
		*/
		void restart()
		{
			m_hoveredWidget = m_Children.end();
			m_choosenWidget = m_Children.end();
			m_clickedWidget = m_Children.end();
		}

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
			sf::Rect<int> bounds = static_cast<sf::Rect<int>>(widget->getGlobalBounds());

			// check if new widget boundaries exceed global menu boundaries
			if (bounds.left < m_boundary.left)
				m_boundary.left = bounds.left;
			if (bounds.top < m_boundary.top)
				m_boundary.top = bounds.top;
			
			switch (m_mhType)
			{
				case MouseHandlingType::SEARCH_BOUNDARY:
				{
					m_boundaries.insert(bounds);
					break;
				}
				case MouseHandlingType::SEARCH_MATRIX:
				{
					m_inputMatrix->setValue(bounds.left, bounds.top, bounds.width, bounds.height, m_Children.size());
					break;
				}
			}

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
		void setBackground(const sf::Texture & texture, sf::Color color)
		{
			m_background.setTexture(texture);
			m_background.setColor(color);
		}


		GuiEvent leftMouseClicked;	///< Event raised upon left mouse click
		//GuiEvent textEntered;		///< Event raised upon entering some text(from keyboard)

	protected:
		void onLeftMouseClicked(const gui::EventArgs & args)
		{
			leftMouseClicked(this, args);
		}
		//void onTextEntered(const gui::EventArgs & args)
		//{
		//	textEntered(this, args);
		//}


	private:
	    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override
	    {
			//if(m_background.getTexture() !=nullptr)
			target.draw(m_background);

	    	for(auto it = m_Children.cbegin();  it != m_Children.cend() ; ++it)
	    	{
	    		target.draw(*it->get());
	    	}
	    }

		MouseHandlingType m_mhType;											///< Algorithm used when handling mouse events
		sf::Sprite m_background;											///< Background sprite
	    std::vector<std::unique_ptr<gui::Widget>> m_Children;				///< Storage for all widgets
		sf::Rect<int> m_boundary{ sf::Rect<int>(WIN_WIDTH,WIN_HEIGHT,0,0) };///< Global rectangle boundary where all widgets are positioned

		//MouseHandlingType::SEARCH_BOUNDARY
		RectBinTree m_boundaries;											///< Rectangle boundaries for all widgets

		// MouseHandlingType::SEARCH_MATRIX
		std::unique_ptr<mat::Matrix<char>> m_inputMatrix;					///< matrix which holds information about indexes of widgets in all window pixels
		static constexpr int tab_i_default = -1;							///< default value for m_inputMatrix for places without any widget

		std::vector<std::unique_ptr<gui::Widget>>::iterator m_hoveredWidget; ///< Iterator to actually hovered Widget
		std::vector<std::unique_ptr<gui::Widget>>::iterator m_clickedWidget; ///< Iterator to actually clicked Widget(choosen with left mouse down)
		std::vector<std::unique_ptr<gui::Widget>>::iterator m_choosenWidget; ///< iterator to choosen(active) widget
	};
}