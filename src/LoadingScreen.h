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

#include <SFML/Graphics.hpp>

//--------------------------------------------------------------------------

#include "resources/ResourcePaths.h"

//--------------------------------------------------------------------------

class LoadingScreen : public sf::Drawable
{
public:
    LoadingScreen();

    void handleEvents(sf::Event& event);

    void setFont(sf::Font& font);
    void setTexture(sf::Texture& texture);
    void setStatus(std::string status);

    const float margins = 10.0f;

private:
    virtual void draw(sf::RenderTarget& target, sf::RenderStates states) const;

    sf::Sprite m_background;
    sf::Text m_status;
    sf::View m_textureView;
};
