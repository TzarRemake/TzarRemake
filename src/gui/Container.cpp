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
		Widget{sf::Color(0,0,0,0)}, m_mhType{mhType}
	{
		std::cout << "Container constructor working" << std::endl;
		switch (mhType)
		{
			case MouseHandlingType::SEARCH_BOUNDARY:
			{
				break;
			}
			case MouseHandlingType::SEARCH_MATRIX:
			{
				static_assert(tab_i_default == -1, "Default value for tab container should be -1");
				m_inputMatrix = std::make_unique<mat::Matrix<char>>(WIN_WIDTH, WIN_HEIGHT, tab_i_default);
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

	Container::Container(Container && obj) :
		Widget{obj.m_normColor}
	{
		m_background = obj.m_background;
		m_boundary = obj.m_boundary;
		m_Children = std::move(obj.m_Children);
		m_boundaries = std::move(obj.m_boundaries);
		m_inputMatrix = std::move(obj.m_inputMatrix);
		leftMouseClicked = std::move(obj.leftMouseClicked);
		//textEntered = std::move(obj.textEntered);
		//command = std::move(obj.command);
		m_mhType = obj.m_mhType;
	}

	//--------------------------------------------------------------------------

	void Container::init()
	{
		m_hoveredWidget = m_Children.end();
		m_clickedWidget = m_Children.end();
		m_choosenWidget = m_Children.end();
	}

	//--------------------------------------------------------------------------

	void Container::handleCommand(CommandHandler * const sender, const CommandArgs  & args)
	{

	}

	//--------------------------------------------------------------------------

	void Container::handleEvents(sf::Event & event)
	{
		try
		{
			switch (event.type)
			{
				//------------------------------------------- Mouse events --------------------------------------------------------//
				case sf::Event::MouseMoved:
				{
					auto it = getWidget(sf::Vector2i(event.mouseMove.x, event.mouseMove.y)); // get widget under mouse position
					if (it == m_hoveredWidget)
					{
						break;
					}
					else
					{
						if (m_Children.end() != m_hoveredWidget)
						{
							commander.args.type = CommandArgs::CommandType::stopHover;
							commander(this, m_hoveredWidget->get());
							m_hoveredWidget = m_Children.end();
						}
						if (m_Children.end() != it)
						{
							commander.args.type = CommandArgs::CommandType::startHover;
							commander(this, it->get());
							m_hoveredWidget = it;
						}
					}
					break;
				}
				case sf::Event::MouseButtonPressed:
				{
					auto it = getWidget(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)); // get widget under mouse click position
					if (it != m_Children.end())
					{
						commander.args.type = CommandArgs::CommandType::startClick;
						commander(this, m_hoveredWidget->get());
						m_clickedWidget = it;
					}
					break;
				}
				case sf::Event::MouseButtonReleased:
				{
					auto it = getWidget(sf::Vector2i(event.mouseButton.x, event.mouseButton.y)); // get widget under mouse release mouse position

					EventArgs args;
					args.type = EventArgs::EventType::leftMouseDown;


					if (m_clickedWidget != m_Children.end())
					{
						commander.args.type = CommandArgs::CommandType::stopClick;
						commander(this, m_clickedWidget->get());
						if (it == m_clickedWidget)
						{
							commander.args.type = CommandArgs::CommandType::click;
							commander(this, m_clickedWidget->get());
						}
						m_choosenWidget = it;
						m_clickedWidget = m_Children.end();
						args.widgetPointer = it->get();
					}
					else
					{
						args.widgetPointer = nullptr;
						m_choosenWidget = m_Children.end();
						m_clickedWidget = m_Children.end();
					}

					onLeftMouseClicked(args);
					break;
				}
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////


				//----------------------------------------- Keyboard events --------------------------------------------------------//
				case sf::Event::TextEntered:
				{
					if (event.text.unicode < 128)
					{	
						if (m_choosenWidget != m_Children.end())
						{
							commander.args.type = CommandArgs::CommandType::textEntered;
							commander.args.unicodeCharacter = event.text.unicode;
							commander(this, m_choosenWidget->get());
						}


						char c = static_cast<char>(event.text.unicode);
						std::cout << "ASCII character typed: " << static_cast<char>(event.text.unicode) << std::endl;
					}
				}
				////////////////////////////////////////////////////////////////////////////////////////////////////////////////////
			}
		}
		catch (const std::out_of_range & e)
		{
			std::cout << "Catched exception std::out_of_range in Container::handleEvents(). " << e.what() << std::endl;
		}
	}

	//--------------------------------------------------------------------------

	void Container::update(sf::Time& delta)
	{
		for (auto & w : m_Children)
		{
			w->update(delta);
		}
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
				if (m_boundary.contains(position))
				{
					unsigned int positionKey = position.x + position.y*WIN_WIDTH;
					for (auto it = m_boundaries.begin() ; it != m_boundaries.end() ; )
					{
						unsigned int index = it->tab;
						if (it->rect.contains(position))
						{
							return (m_Children.begin() + it->tab);
						}
						else
						{
							unsigned int currentKey = RectBinTree::getKey(it->rect);
							unsigned int righChildID = RectBinTree::getChildRight(index);
							unsigned int leftChildID = RectBinTree::getChildLeft(index);

							// if positionKey is higher than current it, then go to rightChild
							if (positionKey > currentKey)
							{
								if (it->rightChildExist)
								{
									it = m_boundaries.begin() + righChildID;
								}
								else
									break;
							}
							else
							{
								if (it->leftChildExist)
								{
									it = m_boundaries.begin() + leftChildID;
								}
								else
									break;
							}
						}
					}
				}
				break;
			}
			case MouseHandlingType::SEARCH_MATRIX:
			{
				if (m_boundary.contains(position))
				{
					try
					{
						int widgetIdx = m_inputMatrix->getValue(position.x, position.y);
						if (widgetIdx != tab_i_default)
						{
							return m_Children.begin() + widgetIdx;
						}
					}
					catch (std::out_of_range e)
					{
						std::cout << "Container::getWidget(sf::Vector2i position): " << e.what() << std::endl;
					}
					
				}
				break;
			}
		}
		//std::cout << "Container::getWIdget()\n";
		return m_Children.end();
	}
}
