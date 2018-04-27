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

#include <Memory>
#include <iostream>
#include <cassert>
#include <type_traits>
#include <stdexcept>
#include <functional>
#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>

//--------------------------------------------------------------------------

#include "EventHandler.h"
#include "../logic/defines.h"

//--------------------------------------------------------------------------

namespace gui
{
	/*!
	* \brief Specify way of handling mouse events
	*/
	enum class MouseHandlingType
	{
		SEARCH_BOUNDARY,	///< indicates that gui will search for objects looking at their boundaries
		SEARCH_MATRIX,		///< indicates that gui will search for objects looking at static matrix
	};

	//--------------------------------------------------------------------------

	class Widget : 	public sf::Drawable,
					public sf::Transformable,
					public sf::NonCopyable
	{
	public:
		Widget(sf::Color normColor):
			m_normTexture{nullptr}, m_hoverTexture{nullptr}, m_clickedTexture{nullptr},
			m_normColor{ normColor }, m_hoverColor{0,0,0}, m_clickedColor{0,0,0}
		{
			std::cout << "Widget constructor working" << std::endl;
		}
		virtual	~Widget()
		{
			std::cout << "Widget destructor working" << std::endl;
		}
		Widget(const Widget & obj) = delete;
		Widget(Widget && obj) = delete;
		Widget & operator=(Widget & obj) = delete;
		Widget & operator=(Widget && obj) = delete;

		//--------------------------------------------------------------------------

		/*!
		* \brief Handle event function which occur whenever some event happen over specified widget
		*/
		virtual void handleEvents(Event::EventType event) = 0;

		virtual void update() {} ///< ??? not sure if this will be used in any way

		/*!
		* \brief Get center of widget in local coordinate system
		*/
		virtual sf::Vector2f getLocalCenter() const = 0;

		//--------------------------------------------------------------------------

		/*!
		 * \brief Setters and getters
		 */
		bool getIsColorHoverable() const { return m_isColorHoverable; }
		bool getIsColorClickable() const { return m_isColorClickable; }
		bool getIsVisible() const { return m_isVisible; }
		bool getIsClickable() const { return m_isClickable; }
		bool getIsHoverable() const { return m_isHoverable; }
		bool getIsTextureClickable() const { return m_isTextureClickable; }
		bool getIsTextureHoverable() const { return m_isTextureHoverable; }

		bool getIsClicked() const { return m_isClicked; }
		bool getIsHovered() const { return m_isHovered; }

		/*!
		* \brief This function state if texture of widget should change upon mouse hovering
		*
		* \param isTextureHoverable Indicates if texture change upon hover -> true or if color dont change -> false
		* \param hoverTexture Additional parameter informing about texture of the widget upon hovering
		*
		*/
		void setIsTextureHoverable(bool isTextureHoverable, sf::Texture * hoverTexture = nullptr, const sf::Rect<int> & textureRect = sf::Rect<int>())
		{
			m_isTextureHoverable = isTextureHoverable;
			if (isTextureHoverable == true)
			{
				m_hoverTexture = hoverTexture;
				m_hoverTextureRect = textureRect;
				setIsHoverable(true);
			}
		}

		/*!
		* \brief This function state if color of widget should change upon mouse hovering
		*
		* \param isColorHoverable Indicates if color change upon hover -> true or if color dont change -> false
		* \param hoverColor Additional parameter informing about color of widget upon hover
		*
		*/
		void setIsTextureClickable(bool isTextureClickable, sf::Texture * clickedTexture = nullptr, const sf::Rect<int> & textureRect = sf::Rect<int>())
		{
			m_isTextureClickable = isTextureClickable;
			if (isTextureClickable == true)
			{
				m_clickedTexture = clickedTexture;
				m_clickedTextureRect = textureRect;
				setIsClickable(true);
			}
		}

		/*!
		* \brief This function state if color of widget should change upon mouse hovering
		*
		* \param isColorHoverable Indicates if color change upon hover -> true or if color dont change -> false
		* \param hoverColor Additional parameter informing about color of widget upon hover
		*
		*/
		void setIsColorHoverable(bool isColorHoverable, sf::Color hoverColor = sf::Color(0,0,0)) 
		{ 
			m_isColorHoverable = isColorHoverable;
			if (isColorHoverable == true)
			{
				m_hoverColor = hoverColor;
				setIsHoverable(true);
			}
		}

		/*!
		* \brief This function state if color of widget should change upon mouse click
		*
		* Mouse click happens whenever user click left mouse button, but dont actually release button.
		*
		* \param isColorHoverable Indicates if color change upon click -> true or if color dont change -> false
		* \param clickedColor Additional parameter informing about color of widget upon click
		*
		*/
		void setIsColorClickable(bool isColorClickable, sf::Color clickedColor = sf::Color(0,0,0)) 
		{ 
			m_isColorClickable = isColorClickable;
			if (isColorClickable == true)
			{
				m_clickedColor = clickedColor;
				setIsClickable(true);
			}
		}

		/*!
		* \brief This function set hover and click colors for this widget
		*
		* \param hoverColor Color of widget upon mouse hover
		* \param clickedColor Color of widget upon mouse click
		*
		*/
		[[deprecated("Use setIsColorHoverable() and setIsColorClickable() instead")]]
		void setEventColors(const sf::Color & hoverColor, const sf::Color & clickedColor)
		{
			m_hoverColor = hoverColor;
			m_clickedColor = clickedColor;
		}

		/*!
		* \brief This function set hover and click colors for this widget
		*
		* \param hoverTexture Texture of widget upon mouse hover
		* \param clickedTexture Texture of widget upon mouse click
		*
		*/
		[[deprecated("Use setIsTextureHoverable() and setIsTextureClickable() instead")]]
		void setEventTextures(sf::Texture * const hoverTexture, sf::Texture * const clickedTexture)
		{
			m_hoverTexture = hoverTexture;
			m_clickedTexture = clickedTexture;
		}

	private:

		/*!
		* \brief State if widget change something when hovered
		*/
		void setIsHoverable(bool isHoverable) { m_isHoverable = isHoverable; }

		/*!
		* \brief State if widget is visible at all
		*/
		void setIsVisible(bool isVisible) { m_isVisible = isVisible; }

	protected:
		/*!
		* \brief State if widget change something when clicked left mouse button, but without release
		*/
		void setIsClickable(bool isClickable) { m_isClickable = isClickable; }

		void setIsHovered(bool isHovered) { m_isHovered = isHovered; }
		void setIsClicked(bool isClicked) { m_isClicked = isClicked; }
		/*!
		* \brief Set texture rect
		*
		* This function sets texture coordinates based on provided rectangle.
		*
		* \param rect Reference to rectangle which will be used in texture coordinates
		*
		*/
		void setTextureRect(const sf::Rect<int> & rect)
		{
			for (unsigned int i = 0; i < m_vertices.getVertexCount(); ++i)
			{
				sf::Rect<float> m_insideBounds = m_vertices.getBounds();
				float xratio = m_insideBounds.width > 0 ? (m_vertices[i].position.x - m_insideBounds.left) / m_insideBounds.width : 0;
				float yratio = m_insideBounds.height > 0 ? (m_vertices[i].position.y - m_insideBounds.top) / m_insideBounds.height : 0;
				m_vertices[i].texCoords.x = rect.left + rect.width * xratio;
				m_vertices[i].texCoords.y = rect.top + rect.height * yratio;
			}
		}

	private:
		bool m_isVisible{true};				///< indicates if widget is visible
		bool m_isClickable{true};			///< indicates if widget is able to be clicked
		bool m_isHoverable{true};			///< indicates if widget change something when hovered
		bool m_isTextureHoverable{false};	///< indicates if texture of widget change after being hovered
		bool m_isTextureClickable{false};	///< indicates if texture of widget change after being clicked
		bool m_isColorHoverable{false};		///< indicates if color of widget change after being hovered
		bool m_isColorClickable{false};		///< indicates if color of widget change after being clicked

		bool m_isHovered{ false };			///< indicates if mouse hover over widget if widget isHoverable is true
		bool m_isClicked{ false };			///< indicates if mouse clicked widget

	protected:
		sf::Texture * m_normTexture;		///< texture of widget normal
		sf::Texture * m_hoverTexture;		///< texture of widget after being hovered
		sf::Texture * m_clickedTexture;		///< texture of widget after being clicked
		sf::Rect<int> m_normTextureRect;	///< rectangle for normal texture
		sf::Rect<int> m_hoverTextureRect;	///< rectangle for hover texture
		sf::Rect<int> m_clickedTextureRect;	///< rectangle for clicked texture
		sf::Color m_normColor;				///< color of widget normal
		sf::Color m_hoverColor;				///< color of widget after being hovered
		sf::Color m_clickedColor;			///< color of widget after being clicked
		sf::VertexArray m_vertices;			///< Array of vertices for button
	};
}
