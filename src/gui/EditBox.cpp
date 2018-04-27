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

	EditBox::EditBox(InputValidation inpValidation, sf::Vector2f size, sf::Color normColor) :
		Widget{ normColor }, m_inpValidation{ inpValidation }
	{
		// initialize vertices
		m_vertices.setPrimitiveType(sf::Quads);
		m_vertices.append(sf::Vertex(sf::Vector2f(0.f, 0.f), normColor));
		m_vertices.append(sf::Vertex(sf::Vector2f(size.x, 0.f), normColor));
		m_vertices.append(sf::Vertex(size, normColor));
		m_vertices.append(sf::Vertex(sf::Vector2f(0.f, size.y), normColor));

		// initialize local bounding rect
		m_floatRect = sf::Rect<float>(0, 0, size.x, size.y);
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
		return sf::Vector2f(m_vertices[0].position.x + m_vertices[2].position.x / 2.f, m_vertices[0].position.y + m_vertices[2].position.y / 2.f);
	}

	//--------------------------------------------------------------------------

	void EditBox::setColor(const sf::Color & color)
	{
		assert(m_vertices.getVertexCount() == 4);
		m_vertices[0].color = color;
		m_vertices[1].color = color;
		m_vertices[2].color = color;
		m_vertices[3].color = color;
	}

	//--------------------------------------------------------------------------

	const sf::Color & EditBox::getColor() const
	{
		assert(m_vertices.getVertexCount() >= 1);
		return m_vertices[0].color;
	}

	//--------------------------------------------------------------------------

	void EditBox::setResources(sf::Texture * texture, const sf::Rect<int> & rect)
	{
		m_normTexture = texture;
		m_texture = texture;
		m_normTextureRect = rect;
		setTextureRect(rect);
	}

	//--------------------------------------------------------------------------

	void EditBox::initText(const std::string & str, const sf::Font & font, 
		unsigned charSize, sf::Text::Style style, sf::Color color)
	{
		m_text.setString(str);
		m_text.setCharacterSize(charSize);
		m_text.setStyle(style);
		m_text.setFillColor(color);
		m_text.setFont(font);
	}

	//--------------------------------------------------------------------------

	void EditBox::draw(sf::RenderTarget& target, sf::RenderStates states) const
	{
		states.transform *= getTransform();

		// apply the texture
		states.texture = m_texture;

		// draw the vertex array
		target.draw(m_vertices, states);
		target.draw(m_text, states);
	}
}
