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
	* \brief 
	*/
	enum class InputValidation
	{
		ALL_TEXT = 255,
	};

	/*!
	 * \brief EditBox GUI class
	 */
	class EditBox : public Widget
	{
	public:
		EditBox(InputValidation m_inpValidation, sf::Vector2f size, sf::Color normColor = sf::Color(0, 0, 0));
		~EditBox();
		EditBox(const EditBox & obj);
		EditBox(EditBox && obj);
		EditBox & operator=(EditBox & obj);
		EditBox & operator=(EditBox && obj);

		//--------------------------------------------------------------------------

		virtual void handleEvents(Event::EventType event) override;
		virtual void update() override;
		/*!
		* \brief Get center of widget in local coordinate system
		*/
		virtual sf::Vector2f getLocalCenter() const override;

		//--------------------------------------------------------------------------

		/*!
		* \brief Get local bounds of this widget
		*
		* \return Local bounding of this widget as sf::Rect<float>
		*/
		sf::Rect<float> getLocalBounds() const
		{
			return m_floatRect;
		}

		/*!
		* \brief Get global bounds of this widget
		*
		* This function return global float rectangle object, so all coordinates
		* take into account all translation and transfrmation beside of window camera
		* movement translation/rotation.
		*
		* \return Global bounding of this edtibox as sf::Rect<float>
		*
		*/
		sf::Rect<float> getGlobalBounds() const
		{
			assert(m_vertices.getVertexCount() == 4);
			return getTransform().transformRect(m_floatRect);
		}

		/*!
		* \brief Set callback function which occur upon pressing widget
		*
		* \param fun Function callback
		*
		*/
		void setCallBack(std::function<void()> fun)
		{
			setIsClickable(true);
			m_callback = std::move(fun);
		}

		/*!
		* \brief Set color of widget
		*
		* \param color Reference to color which will be set to widget
		*
		*/
		void setColor(const sf::Color & color);

		/*!
		* \brief Get color of widget
		*
		* \return Color of widget
		*
		*/
		const sf::Color & getColor() const;

		/*!
		* \brief Sets resources for widget
		*
		* \brief texture Pointer to texture resource in memory
		*
		*/
		void setResources(sf::Texture * texture = nullptr, const sf::Rect<int> & rect = sf::Rect<int>());

		/*!
		* \brief Initialize text
		*
		* \param str Text on the widget
		* \param font Font used for text
		* \param charSize Size of text characters
		* \param style Style of text characters
		* \param color Color of text characters
		*
		*/
		void initText(const std::string & str, const sf::Font & font, 
			unsigned charSize = 30, sf::Text::Style style = sf::Text::Bold, sf::Color color = sf::Color(255, 255, 255));

	private:
		virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		sf::Text m_text;					///< text object which user can change
		sf::Rect<float> m_floatRect;		///< Local bounding rectangle of editBox
		std::function<void()> m_callback;	///< Object which holds function callback which occur when widget is pressed
		sf::Texture * m_texture;			///< Pointer to texture objects
		InputValidation m_inpValidation;	///< indicates what type of input is valid
	};
}


