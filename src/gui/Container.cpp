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

#include "Container.h"

//--------------------------------------------------------------------------

namespace gui
{
	Container::Container(MouseHandlingType mhType) : 
		m_mhType{mhType}
	{
		std::cout << "Container constructor working" << std::endl;
		switch (mhType)
		{
			case MouseHandlingType::SEARCH_BOUNDARY:
			{
				break;
			}
			default:
			{
				Functions::exitCin(EXIT_FAILURE);
				break;
			}
		}
	}

	//--------------------------------------------------------------------------

	Container::~Container()
	{
		std::cout << "Container destructor working" << std::endl;
	}

	//--------------------------------------------------------------------------

	Container::Container(Container && obj)
	{
		m_background = obj.m_background;
		m_boundary = obj.m_boundary;
		m_Children = std::move(obj.m_Children);
		m_boundaries = std::move(obj.m_boundaries);
		m_mhType = obj.m_mhType;
	}

	//--------------------------------------------------------------------------

	void Container::init()
	{
		m_hoveredWidget = m_Children.end();
		m_clickedWidget = m_Children.end();
	}

	//--------------------------------------------------------------------------

	void Container::handleEvents(Event::EventType event)
	{

	}

	//--------------------------------------------------------------------------

	void Container::handleEvents(sf::Event & event)
	{
		try
		{
			switch (event.type)
			{
				case sf::Event::MouseMoved:
				{
					auto it = getWidget(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)); // get widget under mouse position
					if (m_hoveredWidget != m_Children.end())
					{
						if (it != m_hoveredWidget)
						{
							m_hoveredWidget->get()->handleEvents(Event::EventType::stopHover);
							m_hoveredWidget = m_Children.end();
						}
					}

					if (it != m_Children.end())
					{
						it->get()->handleEvents(Event::EventType::startHover);
						m_hoveredWidget = it;
					}
					break;
				}
				case sf::Event::MouseButtonPressed:
				{
					auto it = getWidget(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					if (it != m_Children.end())
					{
						it->get()->handleEvents(Event::EventType::startClick);
						m_clickedWidget = it;
					}
					break;
				}
				case sf::Event::MouseButtonReleased:
				{
					auto it = getWidget(sf::Vector2i(event.mouseButton.x, event.mouseButton.y));
					if (m_clickedWidget != m_Children.end())
					{
						if (it == m_clickedWidget)
						{
							it->get()->handleEvents(Event::EventType::click);
						}
						m_clickedWidget->get()->handleEvents(Event::EventType::stopClick);
						m_clickedWidget = m_Children.end();
					}
					break;
				}
			}
		}
		catch (const std::out_of_range & e)
		{
			std::cout << "Catched exception std::out_of_range in Container::handleEvents(). " << e.what() << std::endl;
		}
	}

	//--------------------------------------------------------------------------

	void Container::update()
	{

	}

	//--------------------------------------------------------------------------

	sf::Vector2f Container::getLocalCenter() const
	{
		return sf::Vector2f(static_cast<float>(m_boundary.left) + static_cast<float>(m_boundary.width)/2.f, static_cast<float>(m_boundary.top) + static_cast<float>(m_boundary.height)/2.f);
	}

	//--------------------------------------------------------------------------

	std::vector<std::unique_ptr<gui::Widget>>::iterator Container::getWidget(sf::Vector2i position)
	{
		switch (m_mhType)
		{
			case MouseHandlingType::SEARCH_BOUNDARY:
			{
				unsigned int index = 0;
				if (m_boundary.contains(position))
				{
					for (auto it = m_boundaries.begin() ; it != m_boundaries.end() ; ++it)
					{
						if (it->contains(position))
						{
							return (m_Children.begin() + index);
						}
						++index;
					}
				}
				break;
			}
		}
		return m_Children.end();
	}
}
