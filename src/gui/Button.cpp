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

#include "Button.h"

//--------------------------------------------------------------------------

namespace gui
{
	Button::Button(sf::Vector2f size, const sf::Color & normColor)
	{
		m_normColor = normColor;
		// initialize vertices
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.append(sf::Vertex(sf::Vector2f(0.f,0.f), m_normColor));
		m_vertices.append(sf::Vertex(sf::Vector2f(size.x,0.f), m_normColor));
		m_vertices.append(sf::Vertex(size, m_normColor));
		m_vertices.append(sf::Vertex(sf::Vector2f(0.f,size.y), m_normColor));
		// initialize local bounding rect
		m_floatRect = sf::Rect<float>(0, 0, size.x, size.y);

		m_text = std::make_unique<Text>(this, TextAligning::CENTER);
		std::cout << "Button constructor working" << std::endl;
	}

	//--------------------------------------------------------------------------

	Button::~Button()
	{
		std::cout << "Button destructor working" << std::endl;
	}

	//--------------------------------------------------------------------------

	sf::Vector2f Button::getLocalCenter() const
	{
		return sf::Vector2f(m_vertices[0].position.x + m_vertices[2].position.x/2.f, m_vertices[0].position.y + m_vertices[2].position.y/2.f);
	}

	//--------------------------------------------------------------------------

	void Button::handleEvents(Event::EventType event)
	{
		switch (event)
		{
			case Event::EventType::startHover:
			{
				if ((getIsHoverable()))
				{
					if (getIsColorHoverable())
					{
						setColor(m_hoverColor);
					}
					if (getIsTextureHoverable())
					{
						m_texture = m_hoverTexture;
						setTextureRect(m_hoverTextureRect);
					}
					if (m_isTextColorHoverable)
					{
						m_text->setFillColor(m_textHoverColor);
					}
					setIsHovered(true);
				}
				break;
			}
			case Event::EventType::stopHover:
			{
				if (getIsColorHoverable())
				{
					setColor(m_normColor);
				}
				if (getIsTextureHoverable())
				{
					m_texture = m_hoverTexture;
					setTextureRect(m_hoverTextureRect);
				}
				if (m_isTextColorHoverable)
				{
					m_text->setFillColor(m_textNormColor);
				}
				setIsHovered(false);
				break;
			}
			case Event::EventType::startClick:
			{
				if (getIsClickable())
				{
					if (getIsColorClickable())
					{
						setColor(m_clickedColor);
					}
					if (getIsTextureClickable())
					{
						m_texture = m_clickedTexture;
						setTextureRect(m_clickedTextureRect);
					}
					setIsClicked(true);
				}
				break;
			}
			case Event::EventType::stopClick:
			{
				if (getIsColorClickable())
				{
					if (getIsColorHoverable() & getIsHovered())
						setColor(m_hoverColor);
					else
						setColor(m_normColor);
				}
				if (getIsTextureClickable())
				{
					if (getIsTextureHoverable() & getIsHovered())
					{
						m_texture = m_hoverTexture;
						setTextureRect(m_hoverTextureRect);
					}
					else
					{
						m_texture = m_normTexture;
						setTextureRect(m_normTextureRect);
					}
				}
				setIsClicked(false);
				break;
			}
			case Event::EventType::click:
			{
				if (getIsClickable())
				{
					if (m_callback)
						m_callback();
				}
				break;
			}
		}
	}

	//--------------------------------------------------------------------------

	void Button::update()
	{

	}

	//--------------------------------------------------------------------------

	void Button::setColor(const sf::Color & color)
	{
		assert(m_vertices.getVertexCount() == 4);
		m_vertices[0].color = color;
		m_vertices[1].color = color;
		m_vertices[2].color = color;
		m_vertices[3].color = color;
	}

	//--------------------------------------------------------------------------

	const sf::Color & Button::getColor() const
	{
		assert(m_vertices.getVertexCount() >= 1);
		return m_vertices[0].color;
	}

	//--------------------------------------------------------------------------

	void Button::setResources(sf::Font * font , sf::Texture * texture, const sf::Rect<int> & rect)
	{
		m_text->setFont(*font);
		m_normTexture = texture;
		m_texture = texture;
		m_normTextureRect = rect;
		setTextureRect(rect);
	}

	//--------------------------------------------------------------------------

	void Button::initText(const std::string & str, TextAligning textAlining,
		unsigned charSize, sf::Text::Style style, sf::Color color)
	{
		m_textNormColor = color;
		m_text->setString(str);
		m_text->setCharacterSize(charSize);
		m_text->setStyle(style);
		m_text->setFillColor(color);
		m_text->align();
	}

	//--------------------------------------------------------------------------

    void Button::draw(sf::RenderTarget& target, sf::RenderStates states) const
    {
        states.transform *= getTransform();

        // apply the texture
        states.texture = m_texture;

        // draw the vertex array
        target.draw(m_vertices, states);
        target.draw(*(static_cast<sf::Text*>(m_text.get())), states);
    }
}
