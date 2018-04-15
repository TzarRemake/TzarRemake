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

#include "PathingSystem.h"

//--------------------------------------------------------------------------

#include <iostream>

//--------------------------------------------------------------------------

Grid * PathingSystem::CostTile::originGrid = nullptr;

//--------------------------------------------------------------------------

PathingSystem::PathingSystem(Grid * originGrid) :
	m_originGrid{originGrid}
{
	testVector.reserve(100000000);

	m_gridSize = originGrid->getGridSize();
	m_chunkGridSize = originGrid->getChunkGridSize();
	m_chunkSizeN = originGrid->getChunkSizeN();
	CostTile::originGrid = originGrid;

	// create all CostTiles   
	m_costTileGrid.reserve(originGrid->getGridSize().x*originGrid->getGridSize().y);
	if (m_costTileGrid.capacity() != originGrid->getGridSize().x*originGrid->getGridSize().y)
		throw std::runtime_error("PathingSystem constructor - Failed to resize grid");
	for (unsigned int j = 0u; j < m_chunkGridSize.y; ++j)
	{
		for (unsigned int i = 0u; i < m_chunkGridSize.x; ++i)
		{
			for (unsigned int y = 0u; y < m_chunkSize.y; ++y)
			{
				for (unsigned int x = 0u; x < m_chunkSize.x; ++x)
				{
					int gridX = m_chunkSize.x*i + x;
					int gridY = m_chunkSize.y*j + y;
					m_costTileGrid.emplace_back(gridX, gridY);
				}
			}
		}
	}
	m_openSet = std::make_unique<BinaryHeapTiles<CostTile*>>(m_gridSize);
	m_closeSet = std::make_unique<CloseSet<CostTile*>>(m_gridSize);

	// neighbours used in bidirectional and non bidrectional search
	m_neighbours = std::make_unique<HeapArray<CostTile*>>(8);

	// initialize variables for bidirectional search  
	m_costTileGrid2.reserve(originGrid->getGridSize().x*originGrid->getGridSize().y);
	if (m_costTileGrid2.capacity() != originGrid->getGridSize().x*originGrid->getGridSize().y)
		throw std::runtime_error("PathingSystem constructor - Failed to resize grid");
	for (unsigned int j = 0u; j < m_chunkGridSize.y; ++j)
	{
		for (unsigned int i = 0u; i < m_chunkGridSize.x; ++i)
		{
			for (unsigned int y = 0u; y < m_chunkSize.y; ++y)
			{
				for (unsigned int x = 0u; x < m_chunkSize.x; ++x)
				{
					int gridX = m_chunkSize.x*i + x;
					int gridY = m_chunkSize.y*j + y;
					m_costTileGrid2.emplace_back(gridX, gridY);
				}
			}
		}
	}
	m_openSet2 = std::make_unique<BinaryHeapTiles<CostTile*>>(m_gridSize);
	m_closeSet2 = std::make_unique<CloseSet<CostTile*>>(m_gridSize);
}

//--------------------------------------------------------------------------

PathingSystem::~PathingSystem()
{
}

//--------------------------------------------------------------------------

std::vector<sf::Vector2i> PathingSystem::findPath(sf::Vector2i startPos, sf::Vector2i targetPos, PF_ALGORITHM algorithm)
{
	//return std::move(testVector);
	return std::move(testVector);
	// check if target tile is not stationary occupied
	sf::Vector2i startPosition = startPos;
	sf::Vector2i targetPosition = targetPos;

	CostTile * ctStart = &m_costTileGrid[getIndex(startPosition)];
	CostTile * ctTarget = &m_costTileGrid[getIndex(targetPosition)];

	ctStart->m_gCost = 0;
	ctStart->m_hCost = 0;
	ctTarget->m_gCost = 0;
	ctTarget->m_hCost = 0;

	switch (algorithm)
	{
		case PF_ALGORITHM::A_STAR_HEAP:
		{
			m_openSet->add(ctStart); 	// add starting tile to openSet
			while (m_openSet->size() > 0)
			{
				// remove the tile, which has lowest cost, from openSet and put it into closeSet
				CostTile * currentTile = m_openSet->front();
				m_closeSet->insert(currentTile);
				m_openSet->remove(0);

				// check if current node is target node
				if (currentTile == ctTarget)
				{
					std::vector<sf::Vector2i> vec;
					while (!(currentTile == ctStart))
					{
						vec.emplace_back(currentTile->m_x, currentTile->m_y);
						currentTile = currentTile->m_parentTile;
					}
					vec.emplace_back(currentTile->m_x, currentTile->m_y);

					// cleanup open and close sets
					m_openSet->cleanup();
					m_closeSet->cleanup();
					return std::move(vec);
				}

				// get all neighbours of current node
				getNeighbours(currentTile);
				for (unsigned int i = 0; i < m_neighbours->size(); ++i)
				{
					CostTile * n = m_neighbours->get(i);
					// check if node is occupied or if it is on the closeSet already
					if (m_originGrid->getObjectType(getIndex(n->m_x, n->m_y)) != ObjectType::NONE || m_closeSet->find(n) == true)
						continue;

					// calculate new movement cost (distance from start) for node
					int newMovCostToNeigh = ManHDistance(currentTile, n) + currentTile->m_gCost;

					// check if new movement cost is lower than before or if node is not in openSet
					// if true, then put node inside openSet with new gCost and hCost and add it's parrent as currentNode
					if (newMovCostToNeigh < n->m_gCost || !m_openSet->find(n))
					{
						n->m_gCost = newMovCostToNeigh;
						n->m_hCost = ManHDistance(n, ctTarget);
						n->m_parentTile = currentTile;
						m_openSet->add(n);
					}
				}
			}

			// cleanup open and close sets if no path was found
			m_openSet->cleanup();
			m_closeSet->cleanup();
			break;
		}
		case PF_ALGORITHM::A_STAR_HEAP_BIDIRECTIONAL:
		{
			//CostTile * ctStart2 = &m_costTileGrid2[getIndex(targetPosition)];
			//CostTile * ctTarget2 = &m_costTileGrid2[getIndex(startPosition)];

			//ctStart2->m_gCost = 0;
			//ctStart2->m_hCost = 0;
			//ctTarget2->m_gCost = 0;
			//ctTarget2->m_hCost = 0;

			//m_openSet->add(ctStart); 	// add starting tile to openSet
			//m_openSet2->add(ctStart2); 	// add starting tile to openSet

			//while (m_openSet->size() > 0 && m_openSet2->size() > 0)
			//{
			//	//--------------- direction 1
			//	CostTile * currentTile = m_openSet->front();

			//	// remove the tile, which has lowest cost, from openSet and put it into closeSet
			//	m_closeSet->insert(m_openSet->front());
			//	m_openSet->remove(0);
			//	m_closeSet2->insert(m_openSet2->front());
			//	m_openSet2->remove(0);

			//	// check if current node is target node
			//	if (m_closeSet2->find(currentTile))
			//	{
			//		std::vector<sf::Vector2i> vec;
			//		CostTile * currentTile2 = &m_costTileGrid2[getIndex(currentTile->m_x, currentTile->m_y)]; // get same tile in 2nd direction

			//		while ( !(currentTile2 == ctStart) )
			//		{
			//			vec.emplace_back(currentTile->m_x, currentTile->m_y);
			//			currentTile = currentTile->m_parentTile;
			//		}

			//		while (!(currentTile == ctStart))
			//		{
			//			vec.emplace_back(currentTile->m_x, currentTile->m_y);
			//			currentTile = currentTile->m_parentTile;
			//		}
			//		vec.emplace_back(currentTile->m_x, currentTile->m_y);
			//		return std::move(vec);
			//	}


			//	// get all neighbours of current node
			//	getNeighbours(currentTile);
			//	for (unsigned int i = 0; i < m_neighbours->size(); ++i)
			//	{
			//		CostTile * n = m_neighbours->get(i);
			//		// check if node is occupied or if it is on the closeSet already
			//		if (m_originGrid->getObjectType(getIndex(n->m_x, n->m_y)) != ObjectType::NONE || m_closeSet->find(n) == true)
			//			continue;

			//		// calculate new movement cost (distance from start) for node
			//		int newMovCostToNeigh = ManHDistance(currentTile, n) + currentTile->m_gCost;

			//		// check if new movement cost is lower than before or if node is not in openSet
			//		// if true, then put node inside openSet with new gCost and hCost and add it's parrent as currentNode
			//		if (newMovCostToNeigh < n->m_gCost || !m_openSet->find(n))
			//		{
			//			n->m_gCost = newMovCostToNeigh;
			//			n->m_hCost = ManHDistance(n, ctTarget);
			//			n->m_parentTile = currentTile;
			//			m_openSet->add(n);
			//		}
			//	}

			//	//--------------- direction 2
			//}
			break;
		}
	}
	
	// return empty vector if no path was found
	return std::vector<sf::Vector2i>();
}

//--------------------------------------------------------------------------

void PathingSystem::getNeighbours(CostTile *node)
{
	m_neighbours->reset();
	for (int y = -1; y <= 1; ++y)
	{
		for (int x = -1; x <= 1; ++x)
		{
			if (x == 0 && y == 0)
				continue;
			int checkX = node->m_x + x;
			int checkY = node->m_y + y;
			if (checkX >= 0 && checkX < m_gridSize.x && checkY >= 0 && checkY < m_gridSize.y)
			{
				m_neighbours->push_back(&m_costTileGrid[getIndex(checkX, checkY)]);
			}
		}
	}
}

//--------------------------------------------------------------------------

PathingSystem::CostTile::CostTile(unsigned int pos_x, unsigned int pos_y)
{
	m_x = pos_x;
	m_y = pos_y;
}

//--------------------------------------------------------------------------

PathingSystem::CostTile::CostTile(sf::Vector2i gridPos)
{
	m_x = gridPos.x;
	m_y = gridPos.y;
}

//--------------------------------------------------------------------------

PathingSystem::CostTile::CostTile(const CostTile & tile)
{
	m_x = tile.m_x;
	m_y = tile.m_y;
	m_gCost = tile.m_gCost;
	m_hCost = tile.m_hCost;
	m_parentTile = tile.m_parentTile;
}

//--------------------------------------------------------------------------

PathingSystem::CostTile & PathingSystem::CostTile::operator=(const CostTile & tile)
{
	m_x = tile.m_x;
	m_y = tile.m_y;
	m_gCost = tile.m_gCost;
	m_hCost = tile.m_hCost;
	m_parentTile = tile.m_parentTile;
	return *this;
}
