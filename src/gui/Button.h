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
#include "Text.h"

//--------------------------------------------------------------------------

namespace gui
{
	/*!
	 * \brief Button GUI class
	 */
	class Button : public Widget
	{
	public:
		/*!
		 * \brief Create button gui object
		 *
		 * \param size Size of rectangle button
		 * \param normColor Standard color of button
		 *
		 */
		Button(sf::Vector2f size, const sf::Color & normColor = sf::Color(0,0,0));
		~Button();
		Button(const Button & obj);
		Button(Button && obj);
		Button & operator=(Button & obj);
		Button & operator=(Button && obj);

		/*!
		* \brief Get center of widget in local coordinate system
		*/
		virtual sf::Vector2f getLocalCenter() const override;

		/*!
		* \brief Get local bounds of this button
		*
		* \return Local bounding of this button as sf::Rect<float>
		*/
		sf::Rect<float> getLocalBounds() const
		{
			return m_floatRect;
		}

		/*!
		* \brief Get global bounds of this button
		*
		* This function return global float rectangle object, so all coordinates
		* take into account all translation and transfrmation beside of window camera
		* movement translation/rotation.
		*
		* \return Global bounding of this button as sf::Rect<float>
		*
		*/
		sf::Rect<float> getGlobalBounds() const
		{
			assert(m_vertices.getVertexCount() == 4);
			return getTransform().transformRect(m_floatRect);
		}

		/*!
		* \brief Set callback function which occur upon pressing button
		*
		* \param fun Function callback
		*
		*/
		void setCallBack(std::function<void()> fun)
		{
			m_callback = std::move(fun);
		}


		virtual void handleEvents(Event::EventType event) override;
		virtual void update() override;

		/*!
		* \brief Set color of button
		*
		* \param color Reference to color which will be set to button
		*
		*/
		void setColor(const sf::Color & color);

		/*!
		* \brief Get color of button
		*
		* \return Color of button
		*
		*/
		const sf::Color & getColor() const;

		/*!
		* \brief Sets resources for widget
		*
		* \brief font Pointer to font resource in memory
		* \brief texture Pointer to texture resource in memory
		*
		*/
		void setResources(sf::Font * font, sf::Texture * texture = nullptr, const sf::Rect<int> & rect = sf::Rect<int>());

		/*!
		* \brief Initialize text
		*
		* \param str Text on the button
		* \param textAlining Style of text aligning to button widget
		* \param charSize Size of text characters
		* \param style Style of text characters
		* \param color Color of text characters
		*
		*/
		void initText(const std::string & str, TextAligning textAlining,
			unsigned charSize = 30, sf::Text::Style style = sf::Text::Bold, sf::Color color = sf::Color(255,255,255));


		void setTextColorHoverable(bool isHoverable, sf::Color color)
		{
			m_isTextColorHoverable = isHoverable;
			m_textHoverColor = color;
		}

	private:
	    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const override;

		//bool m_isTextHoverable{ false };		///< indicates if button text change when hoverable
		bool m_isTextColorHoverable{ false };	///< indicates if color of text change when hovered
		sf::Color m_textNormColor;				///< standard color of text
		sf::Color m_textHoverColor;				///< color of text after being hovered

	    sf::Texture * m_texture;			///< Pointer to texture object
	    std::unique_ptr<Text> m_text;		///< Text object which is drawed on top of button
		sf::Rect<float> m_floatRect;		///< Local bounding rectangle of button
		std::function<void()> m_callback;	///< Object which holds function callback which occur when button is pressed
	};
}
