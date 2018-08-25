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
#include <bitset>
#include <algorithm>
#include <SFML/Graphics.hpp>

//--------------------------------------------------------------------------

namespace logic
{
	/*!
	* \brief This container is used to store tiles information in minimal binary heap (top of the heap has minimal value)
	*/
	template<class T>
	class BinaryHeapTiles
	{
	public:
		BinaryHeapTiles<T>(sf::Vector2i gridSize) :
			m_items(gridSize.x*gridSize.y), m_gridSize{ gridSize }
		{
			static_assert(std::is_pointer<T>::value, "BinaryHeapTiles expects a pointer T* ");
		}

		/*!
		* \brief Return first element of the heap
		*/
		T front()
		{
			return m_items[0];
		}

		/*!
		* \brief Return last element of the heap
		*/
		T back()
		{
			return m_items[m_index - 1];
		}

		/*!
		* \brief Adds new element to the heap
		*
		* \param item Pointer to added element
		*
		*/
		void add(T item)
		{
			unsigned int index = item->getY()*m_gridSize.x + item->getX();
			m_isSet[index] = true;
			m_items[m_index] = item;

			// check if new item is not on top of the heap
			if (m_index != 0)
			{
				while (true)
				{
					unsigned int parentIndex = getParent(m_index);
					// check if item's cost is lower than it's parent cost
					if (*m_items[m_index] < *m_items[parentIndex])
					{
						std::swap(m_items[m_index], m_items[parentIndex]);
					}
					else
						break;

					if (parentIndex == 0)
						break;
					else
						m_index = parentIndex;
				}
			}

			++m_index;
		}

		/*!
		* \brief Remove element from the heap
		*
		* \param index Index to element which should be removed
		*
		*/
		void remove(unsigned int index)
		{
			T item = m_items[index];
			unsigned int idx = item->getY()*m_gridSize.x + item->getX();
			m_isSet[idx] = false;
			m_items[index] = m_items[m_index - 1];

			while (true)
			{
				int leftChildIndex = getChildLeft(index);
				if (leftChildIndex >= m_index)
					break;
				int rightChildIndex = getChildRight(index);
				if (rightChildIndex >= m_index)
				{
					if ((*m_items[leftChildIndex] < *m_items[index]) == true)
					{
						std::swap(m_items[leftChildIndex], m_items[index]);
					}
					break;;
				}
				else
				{
					if ((*m_items[leftChildIndex] < *m_items[index]) == true)
					{
						if ((*m_items[leftChildIndex] < *m_items[rightChildIndex]) == true)
						{
							std::swap(m_items[leftChildIndex], m_items[index]);
							index = leftChildIndex;
						}
						else
						{
							std::swap(m_items[rightChildIndex], m_items[index]);
							index = rightChildIndex;
						}
					}
					else if ((*m_items[rightChildIndex] < *m_items[index]) == true)
					{
						std::swap(m_items[rightChildIndex], m_items[index]);
						index = rightChildIndex;
					}
					else
						break;
				}
			}

			--m_index;
		}

		/*!
		* \brief Get index of the parent
		*/
		unsigned int getParent(unsigned int index) const noexcept
		{
			return (index - 1) / 2;
		}

		/*!
		* \brief Get index of left child
		*/
		unsigned int getChildLeft(unsigned int index) const noexcept
		{
			return index * 2 + 1;
		}

		/*!
		* \brief Get index of right child
		*/
		unsigned int getChildRight(unsigned int index) const
		{
			return index * 2 + 2;
		}

		/*!
		* \brief Return bool value indicating if specified element is in heap allocator
		*/
		bool find(T item)
		{
			unsigned int index = item->m_y*m_gridSize.x + item->m_x;
			return m_isSet.test(index);
		}

		/*!
		* \brief Return current logic size of the vector container
		*/
		unsigned int size() const { return m_index; }

		/*!
		* \brief Clean and reset vector
		*/
		void cleanup()
		{
			m_index = 0;
			m_isSet.reset();
		}

	private:
		/*!
		* \brief Return specified element of the heap
		*/
		T get(unsigned int index)
		{
			return m_items[index];
		}

	private:
		std::vector<T> m_items;						///< main vector container
		unsigned int m_index{ 0u };					///< current logic size of the vector container
		std::bitset<GRID_SIZE*GRID_SIZE> m_isSet;	///< bitset of all tiles - true means that tile is already inside container
		sf::Vector2i m_gridSize;					///< size of the grid
	};

	//--------------------------------------------------------------------------

	/*!
	* \brief This container is used to store tiles information for close set in A* algorithm
	*
	* For performance reasons CloseSet holds only information if node is or is not in CloseSet inside std::bitset
	*
	*/
	template<class T>
	class CloseSet
	{
	public:
		CloseSet<T>(sf::Vector2i gridSize) :
			m_gridSize{ gridSize }
		{
			static_assert(std::is_pointer<T>::value, "CloseSet expects a pointer T* ");
		}

		void insert(sf::Vector2i nodePos)
		{
			unsigned int index = nodePos.y*m_gridSize.x + nodePos.x;
			m_closeSet[index] = true;
		}

		void insert(unsigned int index)
		{
			m_closeSet[index] = true;
		}

		void insert(T node)
		{
			unsigned int index = node->m_y*m_gridSize.x + node->m_x;
			m_closeSet[index] = true;
		}

		bool find(sf::Vector2i nodePos)
		{
			unsigned int index = nodePos.y*m_gridSize.x + nodePos.x;
			return m_closeSet[index];
		}

		bool find(unsigned int index) const
		{
			return m_closeSet[index];
		}

		bool find(T node) const
		{
			unsigned int index = node->m_y*m_gridSize.x + node->m_x;
			return m_closeSet[index];
		}

		void cleanup()
		{
			m_closeSet.reset();
		}

		unsigned int size() const { return m_closeSet.size(); }

	private:
		sf::Vector2i m_gridSize;						///< size of the grid of costNodes
		std::bitset<GRID_SIZE*GRID_SIZE> m_closeSet;	///< grid of all nodes values
	};

	//--------------------------------------------------------------------------

	/*!
	* \brief Array of pointers allocated on std::vector with static maximum size
	*
	* This template class allows to allocate pointers of any type on vector. Once defined, object
	* of this class will have static maximum size which can't be exceeded. Allocating new items
	* is performed by copy (copy of address), however removing all elements is only logic and no deallocation/deletion happens.
	*
	*/
	template<typename T>
	class LogicArrayPtr
	{
	public:
		/*!
		* \brief Default constructor
		*
		* \param size Size of array which will be static throughout all "live" of object.
		*/
		LogicArrayPtr(unsigned int size)
		{
			static_assert(std::is_pointer<T>::value, "LogicArrayPtr expects a pointer T* ");
			m_items.resize(size);
			m_items.shrink_to_fit();
		}

		/*!
		* \brief Add new item by making copy of it (copy of pointer)
		*
		* This function don't throw exception if adding new item would exceed it's preallocated size.
		*
		* \param item Pointer to new added element
		*
		*/
		void push_back(T item)
		{
			m_items[m_index] = item;
			++m_index;
		}

		/*!
		* \brief Get pointer to element from array on given position
		*
		* This function don't throw exception if index parameter exceet size of vector
		*
		* \param index Position of item in array
		*
		*/
		T get(unsigned int index) const
		{
			return m_items[index];
		}

		/*!
		* \brief Resets logic size of array to 0
		*
		* This function don't perform any physical deallocation or allocation.
		*
		*/
		void reset() noexcept
		{
			m_index = 0u;
		}

		/*!
		* \brief Return logical size of array
		*
		* \return Logical size of array
		*
		*/
		unsigned int size() const noexcept { return m_index; }

		/*!
		* \brief Return physical preallocated size of array
		*
		* \return Physical size of array
		*
		*/
		unsigned int physicalSize() const noexcept { return m_items.size(); }

	private:
		std::vector<T> m_items;		///< main vector of items
		unsigned int m_index{ 0u }; ///< current virtual size of the vector
	};

} // namespace logic
