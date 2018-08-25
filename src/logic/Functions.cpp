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

#include "defines.h"

//--------------------------------------------------------------------------


void Functions::exitCin(unsigned int exitReturn)
{
	auto func = atexit([]() {
		std::cout << "Press enter to terminate program... " << std::endl;
		std::cin.get();
	});
	exit(exitReturn);
}

void Functions::throwInvalidArgument(std::string && str)
{
	throw std::invalid_argument(str);
}