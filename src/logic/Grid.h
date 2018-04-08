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

#include <vector>
#include <SFML\Graphics.hpp>

//--------------------------------------------------------------------------

#include "defines.h"
#include <cassert>

//--------------------------------------------------------------------------

enum class TerrainType
{
	
};

//--------------------------------------------------------------------------

enum class ObjectType
{
	NONE,
	UNIT,
	TREE,
	BUILDING,
};

//--------------------------------------------------------------------------

class Grid
{
public:
	Grid(sf::Vector2i & gridSize);
	~Grid();

	inline sf::Vector2i getGridSize() const { return m_gridSize; }
	inline sf::Vector2i getChunkSize() const { return m_chunkSize; }
	inline sf::Vector2i getChunkGridSize() const { return m_chunkGridSize; }
	inline int getChunkSizeN() const { return m_chunkSizeN; }
	inline ObjectType getObjectType(unsigned int index) const { return m_objType[index]; }

private:
	std::vector<ObjectType> m_objType;		///< object type

	sf::Vector2i m_gridSize;											///< size of the grid in grid coordinates (amount of tiles in x and y direction in all grid)
	sf::Vector2i m_chunkSize{ sf::Vector2i(CHUNK_SIZE,CHUNK_SIZE) };	///< size of the chunk in grid coordinates (amount of tiles in x and y direction in chunk)
	sf::Vector2i m_chunkGridSize;										///< amount of chunk in x and y direction
	int m_chunkSizeN;													///< amount of tiles in chunk
};

