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

#include <iostream>

//--------------------------------------------------------------------------

constexpr unsigned int WIN_WIDTH = 800;
constexpr unsigned int WIN_HEIGHT = 600;
constexpr unsigned int CHUNK_SIZE = 8;
constexpr unsigned int GRID_SIZE = 256;

constexpr unsigned int WIN_WIDTH_MENU = 800;
constexpr unsigned int WIN_HEIGHT_MENU = 600;

//--------------------------------------------------------------------------

/*!
* \brief Function which exit program after user press enter in console
*/
class Functions
{
public:
	/*!
	* Exit program after pressing enter
	*
	* \param exitReturn Return value of program exit.
	*/
	static void exitCin(unsigned int exitReturn);

	/*!
	* Throw std::invalid_argument with std::string
	*
	* \param str Rvalue reference to std::string which will throw exception
	*
	*/
	static void throwInvalidArgument(std::string && str);
};