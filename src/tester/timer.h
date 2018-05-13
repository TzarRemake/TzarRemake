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
#include <chrono>
#include <iostream>

//--------------------------------------------------------------------------

namespace tester
{
	enum class TimerID
	{
		StateMenu,
	};

	//--------------------------------------------------------------------------

	/*!
	* \biref Used to measure time.
	*
	* This class can be used to measure time and output this into SFML object sf::Text.
	* 
	*
	*/
	template<TimerID ID>
	class Timer
	{
	public:
		Timer() = default;
		~Timer();

		/*!
		* \brief Initialize of static elements of this class
		*
		* This function should be called at least once to specify static elements
		* which are used in this class.
		*
		*/
		static void init(sf::RenderWindow * window, sf::Font & font)
		{
			m_window = window;
			textClock.setFont(font);
			textClock.setPosition(5.f, 10.f);
			textClock.setCharacterSize(18);
			textClock.setFillColor(sf::Color(255, 255, 0));

			fps = 0;
			m_elapsed = 0.f;
			start = std::chrono::high_resolution_clock::now();
		}

	private:
		static std::chrono::time_point<std::chrono::high_resolution_clock> start, end;

		//std::chrono

		static sf::RenderWindow * m_window;
		static sf::Text textClock;
		static float m_elapsed;
		static int fps;
		static int oldFps;
	};

	template<TimerID ID>
	Timer<ID>::~Timer()
	{
		end = std::chrono::high_resolution_clock::now();
		auto duration = end - start;
		++fps;
		if (duration.count() >= 1'000'000'000)
		{
			oldFps = (static_cast<float>(oldFps) + static_cast<float>(fps)) / 2.f;
			textClock.setString("FPS: " + std::to_string(oldFps) + "\nFrame time: " + std::to_string(1 / static_cast<float>(oldFps)) + " s");
			fps = 0;
			start = std::chrono::high_resolution_clock::now() + duration - std::chrono::nanoseconds(1'000'000'000);
		}
		m_window->draw(textClock);
	}

	template<TimerID ID>
	std::chrono::time_point<std::chrono::high_resolution_clock> Timer<ID>::start = std::chrono::high_resolution_clock::now();

	template<TimerID ID>
	std::chrono::time_point<std::chrono::high_resolution_clock> Timer<ID>::end = std::chrono::high_resolution_clock::now();

	template<TimerID ID>
	float Timer<ID>::m_elapsed = 0.f;

	template<TimerID ID>
	int Timer<ID>::fps = 0;

	template<TimerID ID>
	int Timer<ID>::oldFps = 0;

	template<TimerID ID>
	sf::Text Timer<ID>::textClock = sf::Text();

	template<TimerID ID>
	sf::RenderWindow * Timer<ID>::m_window = nullptr;

	//--------------------------------------------------------------------------

	/*!
	* \biref Used to measure time.
	*
	* This class can be used to measure time and output this into SFML object sf::Text.
	*
	*
	*/
	template<TimerID ID>
	class Timer2
	{
	public:
		Timer2() = default;
		~Timer2();

		/*!
		* \brief Initialize of static elements of this class
		*
		* This function should be called at least once to specify static elements
		* which are used in this class.
		*
		*/
		static void init(sf::RenderWindow * window, sf::Font & font)
		{
			m_window = window;
			m_textClock.setFont(font);
			m_textClock.setPosition(5.f, 100.f);
			m_textClock.setCharacterSize(18);
			m_textClock.setFillColor(sf::Color(255, 255, 0));

			fps = 0;
			m_elapsed = 0.f;
			m_clock.restart();
		}

	private:
		static sf::RenderWindow * m_window;
		static sf::Text m_textClock;
		static sf::Clock m_clock;
		static float m_elapsed;
		static int fps;
		static int oldFps;
	};

	template<TimerID ID>
	Timer2<ID>::~Timer2()
	{
		++fps;
		if (m_clock.getElapsedTime().asMicroseconds() >= 1'000'000)
		{
			oldFps = (static_cast<float>(oldFps) + static_cast<float>(fps)) / 2.f;
			m_textClock.setString("FPS: " + std::to_string(oldFps) + "\nFrame time: " + std::to_string(1 / static_cast<float>(oldFps)) + " s");
			fps = 0;
			m_clock.restart(); // need to add something
		}
		m_window->draw(m_textClock);
	}

	template<TimerID ID>
	sf::Clock Timer2<ID>::m_clock = sf::Clock();

	template<TimerID ID>
	float Timer2<ID>::m_elapsed = 0.f;

	template<TimerID ID>
	int Timer2<ID>::fps = 0;

	template<TimerID ID>
	int Timer2<ID>::oldFps = 0;

	template<TimerID ID>
	sf::Text Timer2<ID>::m_textClock = sf::Text();

	template<TimerID ID>
	sf::RenderWindow * Timer2<ID>::m_window = nullptr;

	//--------------------------------------------------------------------------

	/*!
	* \brief Class which measure time of it's existance
	*
	* This class instance can be used at the start of some function or any other moment to
	* "catch" timesteamp of that moment. Destructor of this class will print out
	* amount of time which passed between construction end destruction.
	* 
	*/
	class FunctionTimer
	{
	public:
		FunctionTimer()
		{
			start = std::chrono::high_resolution_clock::now();
		}
		~FunctionTimer()
		{
			end = std::chrono::high_resolution_clock::now();
			auto duration = end - start;
			std::cout << "Function took " << duration.count() << " ns" << std::endl;
		}

	private:
		static std::chrono::time_point<std::chrono::high_resolution_clock> start, end;
	};
}