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
#include <SFML/Graphics.hpp>
#include <memory>

//--------------------------------------------------------------------------

#include "Grid.h"
#include "allocators.h"

//--------------------------------------------------------------------------

/*!
* \brief Id of algorithms used in path finding
*/
enum class PF_ALGORITHM
{
	A_STAR_HEAP,
	A_STAR_HEAP_BIDIRECTIONAL,

};

//--------------------------------------------------------------------------

class PathingSystem
{
public:
	PathingSystem(Grid * originGrid);
	~PathingSystem();

	/*!
	* \brief Finds best path vector between two positions on the map
	*
	* This function calculate a path between two positions on the grid map. Used for this goal algorithm is specified by
	* PF_ALGORITHM enum class. Function does not perform bounding check for start and target position in Release mode. 
	* User must ensure that this positions are inside main grid map.
	*
	* \param startPos Starting position of path
	* \param targetPos Target position of path
	* \param algorithm ID of algorithm used in path finding
	*
	* \return Path vector including starting and target position
	*
	*/
	std::vector<sf::Vector2i> findPath(sf::Vector2i startPos, sf::Vector2i targetPos, PF_ALGORITHM algorithm);

	class CostTile
	{
	public:
		CostTile() = default;
		CostTile(unsigned int pos_x, unsigned int pos_y);
		CostTile(sf::Vector2i gridPos);
		CostTile(const CostTile & tile);
		CostTile & operator=(const CostTile & tile);

		bool operator>(const CostTile & t2) const
		{
			if (fCost() > t2.fCost())
				return true;
			else if ( (fCost() == t2.fCost()) && (getHCost() > t2.getHCost()) )
				return true;
			else
				return false;
		}

		bool operator<(const CostTile & t2) const
		{
			if (fCost() < t2.fCost())
				return true;
			else if ((fCost() == t2.fCost()) && (getHCost() < t2.getHCost()))
				return true;
			else
				return false;
		}

		int fCost() const { return m_gCost + m_hCost; }
		int getGCost() const { return m_gCost; }
		int getHCost() const { return m_hCost; }
		unsigned int getX() const { return m_x; }
		unsigned int getY() const { return m_y; }


	private:
		//unsigned int m_x, m_y;					///< x,y position on the grid
		//int m_gCost{ 0 };						///< distance to start tile
		//int m_hCost{ 0 };						///< distance to target tile
		//CostTile * m_parentTile{ nullptr };	///< pointer to parent tile

	public:
		static Grid * originGrid;			///< pointer to original grid
		unsigned int m_x, m_y;				///< x,y position on the grid
		int m_gCost{ 0 };					///< distance to start tile
		int m_hCost{ 0 };					///< distance to target tile
		CostTile * m_parentTile{ nullptr };	///< pointer to parent tile

	};

private:
	unsigned int getIndex(int gridPosition_x, int gridPosition_y) const
	{
		return (gridPosition_x / m_chunkSize.x + (gridPosition_y / m_chunkSize.y)*m_chunkGridSize.x)*m_chunkSizeN + (gridPosition_x % m_chunkSize.x) + 
			(gridPosition_y % m_chunkSize.y)*m_chunkSize.x;
	}

	unsigned int getIndex(sf::Vector2i gridPosition) const
	{
		return (gridPosition.x / m_chunkSize.x + (gridPosition.y / m_chunkSize.y)*m_chunkGridSize.x)*m_chunkSizeN + (gridPosition.x % m_chunkSize.x) +
			(gridPosition.y % m_chunkSize.y)*m_chunkSize.x;
	}

	int ManHDistance(CostTile * nodeA, CostTile * nodeB)
	{
		// if diagonal is slower than straight
		/*
		int dstX = std::abs(static_cast<int>(nodeA->m_x - nodeB->m_x));
		int dstY = std::abs(static_cast<int>(nodeA->m_y - nodeB->m_y));

		if (dstX > dstY)
			return 14 * dstY + 10 * (dstX - dstY);
		else
			return 14 * dstX + 10 * (dstY - dstX);
		*/
		int dstX = std::abs(static_cast<int>(nodeA->m_x - nodeB->m_x));
		int dstY = std::abs(static_cast<int>(nodeA->m_y - nodeB->m_y));
		return dstX > dstY ? dstX : dstY;
	}

	int ManHDistance(sf::Vector2i posA, sf::Vector2i posB)
	{
		// if diagonal is slower than straight
		/*
		int dstX = std::abs(static_cast<int>(posA.x - posB.x));
		int dstY = std::abs(static_cast<int>(posA.y - posB.y));

		if (dstX > dstY)
			return 14 * dstY + 10 * (dstX - dstY);
		else
			return 14 * dstX + 10 * (dstY - dstX);
		*/
		int dstX = std::abs(static_cast<int>(posA.x - posB.x));
		int dstY = std::abs(static_cast<int>(posA.y - posB.y));
		return dstX > dstY ? dstX : dstY;
	}

	/*!
	* \brief Set up neighbour vector
	*/
	void getNeighbours(CostTile *node);

private:
	const Grid * m_originGrid;											///< pointer to original grid

	sf::Vector2i m_gridSize;											///< size of the grid in grid coordinates (amount of tiles in x and y direction in all grid)
	sf::Vector2i m_chunkSize{ sf::Vector2i(CHUNK_SIZE,CHUNK_SIZE) };	///< size of the chunk in grid coordinates (amount of tiles in x and y direction in chunk)
	sf::Vector2i m_chunkGridSize;										///< amount of chunk in x and y direction
	int m_chunkSizeN;													///< amount of tiles in chunk

	std::vector<CostTile> m_costTileGrid;								///< grid of cost tiles
	std::vector<CostTile> m_costTileGrid2;								///< grid of cost tiles used for bidirectional algorithm
	std::unique_ptr<BinaryHeapTiles<CostTile*>> m_openSet;				///< open set for cost tiles stored on binary heap allocator
	std::unique_ptr<CloseSet<CostTile*>> m_closeSet;					///< close set for cost tiles
	std::unique_ptr<BinaryHeapTiles<CostTile*>> m_openSet2;				///< open set for cost tiles stored on binary heap allocator used for bidirectional algorithm
	std::unique_ptr<CloseSet<CostTile*>> m_closeSet2;					///< close set for cost tiles used for bidirectional algorithm

	std::unique_ptr<HeapArray<CostTile*>> m_neighbours;					///< vector of all neighbours 
};

