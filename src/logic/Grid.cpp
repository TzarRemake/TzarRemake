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

#include "Grid.h"

//--------------------------------------------------------------------------

Grid::Grid(sf::Vector2i & gridSize) :
	m_gridSize{gridSize}
{
	// check if gridSize and chunkSize fit
	assert( ((gridSize.x % m_chunkSize.x) == 0) && ((gridSize.y % m_chunkSize.y) == 0) );
	m_chunkGridSize.x = gridSize.x / m_chunkSize.x;
	m_chunkGridSize.y = gridSize.y / m_chunkSize.y;
	m_chunkSizeN = m_chunkSize.x*m_chunkSize.y;

	m_objType.resize(gridSize.x*gridSize.y);
}

//--------------------------------------------------------------------------

Grid::~Grid()
{
}
