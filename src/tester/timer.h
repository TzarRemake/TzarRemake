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

#include <SFML/Graphics.hpp>
#include <SFML/Window.hpp>
#include <SFML/System/Clock.hpp>

//--------------------------------------------------------------------------

namespace tst
{
	enum class TimerID
	{
		StateMenu,
	};

	//--------------------------------------------------------------------------

	template<TimerID ID>
	class Timer
	{
	public:
		Timer(sf::RenderWindow *window);
		~Timer();

		static void init(sf::Font & font)
		{
			textClock.setFont(font);
			textClock.setPosition(5.f,10.f);
			textClock.setCharacterSize(18);
			textClock.setFillColor(sf::Color(255,255,0));

			clock.restart();
			time = sf::seconds(0.f);
			fps = 0;
			m_elapsed = 0.f;
		}

	private:
		sf::RenderWindow * m_window;
		static sf::Text textClock;
		static sf::Clock clock;
		static sf::Time time;
		static float m_elapsed;
		static int fps;
		static int oldFps;
	};

	//--------------------------------------------------------------------------

	template<TimerID ID>
	Timer<ID>::Timer(sf::RenderWindow * window):
		m_window{window}
	{
	}

	//--------------------------------------------------------------------------

	template<TimerID ID>
	Timer<ID>::~Timer()
	{
		sf::Time newTime = clock.restart();
		m_elapsed += newTime.asSeconds();
		++fps;

		if (m_elapsed >= 1.f)
		{
			oldFps = static_cast<float>(oldFps + fps) / 2.f;
			textClock.setString("FPS: " + std::to_string(oldFps));
			m_elapsed -= 1.f;
			fps = 0;
		}

		m_window->draw(textClock);
	}

	//--------------------------------------------------------------------------

	template<TimerID ID>
	float Timer<ID>::m_elapsed = 0.f;

	template<TimerID ID>
	int Timer<ID>::fps = 0;

	template<TimerID ID>
	int Timer<ID>::oldFps = 0;

	template<TimerID ID>
	sf::Text Timer<ID>::textClock = sf::Text();

	template<TimerID ID>
	sf::Clock Timer<ID>::clock = sf::Clock();

	template<TimerID ID>
	sf::Time Timer<ID>::time = sf::Time();

}