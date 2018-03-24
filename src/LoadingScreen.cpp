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

#include "LoadingScreen.h"

//--------------------------------------------------------------------------

LoadingScreen::LoadingScreen()
{
    m_status.setFillColor(sf::Color::White);
    m_status.setCharacterSize(15);
    m_status.setStyle(sf::Text::Bold);

    m_status.setPosition(10.f, 200.f);
}

//--------------------------------------------------------------------------

void LoadingScreen::handleEvents(sf::Event& event)
{
    if (event.type == sf::Event::Resized)
        updateView(event.size.width, event.size.height);
}

//--------------------------------------------------------------------------

void LoadingScreen::updateView(float x, float y)
{
    // For now that's it
    m_status.setPosition(margins, y - m_status.getCharacterSize() - margins);
}

//--------------------------------------------------------------------------

void LoadingScreen::draw(sf::RenderTarget& target, sf::RenderStates states) const
{
    const auto original = target.getView();

    target.setView(m_textureView);
    target.draw(m_background, states);

    target.setView(original);
    target.draw(m_status, states);
}

//--------------------------------------------------------------------------

void LoadingScreen::setFont(const sf::Font& font)
{
    m_status.setFont(font);
}

//--------------------------------------------------------------------------

void LoadingScreen::setTexture(const sf::Texture &texture)
{
    auto size = texture.getSize();

    m_background.setTexture(texture);
    m_textureView.reset({0.f, 0.0f, static_cast<float>(size.x), static_cast<float>(size.y)});
}

//--------------------------------------------------------------------------

void LoadingScreen::setStatus(const std::string& status)
{
    m_status.setString(status);
}
