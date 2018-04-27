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

#include "Widget.h"
#include "Matrix.h"
#include "Button.h"

//--------------------------------------------------------------------------

namespace gui
{
	/*!
	* \brief This structure keep information about rectangle objects inside binary tree allocator
	*/
	struct RectTree
	{
		sf::Rect<int> rect;				///< boundary rectangle
		int tab;						///< id of object
		bool leftChildExist = false;	///< indicates if left child in binary tree exist
		bool rightChildExist = false;   ///< indicates if right child in binary tree exist
	};

	//--------------------------------------------------------------------------

	/*!
	* \biref Binary tree of sf::Rect
	*/
	class RectBinTree
	{
	public:
		RectBinTree(unsigned int size = 0)
		{
			m_items.reserve(size);
		}
		RectBinTree(RectBinTree && obj)
		{
			m_items = std::move(obj.m_items);
		}
		RectBinTree & operator=(RectBinTree && obj)
		{
			m_items = std::move(obj.m_items);
			return *this;
		}
		~RectBinTree() {}

		/*!
		* \brief Insert element in bin tree
		*/
		void insert(sf::Rect<int> & item)
		{
			int key = getKey(item);
			int size = m_items.size();
			if (size > 0)
			{
				unsigned int parentID = 0;
				bool itemPlaced = false;
				while (!itemPlaced)
				{
					unsigned int rightChildID = getChildRight(parentID);
					unsigned int leftChildID = getChildLeft(parentID);
					if (key > getKey(m_items[parentID].rect))
					{
						// if right child dont exist then then place it
						if (!m_items[parentID].rightChildExist)
						{
							if (size == rightChildID)
							{
								RectTree tempRect;
								tempRect.rect = item;
								tempRect.tab = ++m_tab;
								m_items.push_back(tempRect);
								m_items[parentID].rightChildExist = true;
								itemPlaced = true;
							}
							else if (size < rightChildID)
							{
								m_items.resize(rightChildID + 1);
								RectTree tempRect;
								tempRect.rect = item;
								tempRect.tab = ++m_tab;
								m_items[rightChildID] = tempRect;
								m_items[parentID].rightChildExist = true;
								itemPlaced = true;
							}
							else
							{
								RectTree tempRect;
								tempRect.rect = item;
								m_items[rightChildID] = tempRect;
								tempRect.tab = ++m_tab;
								m_items[parentID].rightChildExist = true;
								itemPlaced = true;
							}
						}
						else
							parentID = rightChildID;
					}
					else if (key < getKey(m_items[parentID].rect))
					{
						// if left child dont exist then place it
						if (!m_items[parentID].leftChildExist)
						{
							if (size == leftChildID)
							{
								RectTree tempRect;
								tempRect.rect = item;
								tempRect.tab = ++m_tab;
								m_items.push_back(tempRect);
								m_items[parentID].leftChildExist = true;
								itemPlaced = true;
							}
							else if (size < leftChildID)
							{
								m_items.resize(leftChildID + 1);
								RectTree tempRect;
								tempRect.rect = item;
								tempRect.tab = ++m_tab;
								m_items[leftChildID] = tempRect;
								m_items[parentID].leftChildExist = true;
								itemPlaced = true;
							}
							else
							{
								RectTree tempRect;
								tempRect.rect = item;
								tempRect.tab = ++m_tab;
								m_items[leftChildID] = tempRect;
								m_items[parentID].leftChildExist = true;
								itemPlaced = true;
							}
						}
						else
							parentID = leftChildID;
					}
					else
					{
						Functions::throwInvalidArgument("Item with this key already exist in RectBinTree");
					}
				}
			}
			else
			{
				RectTree tempRect;
				tempRect.rect = item;
				tempRect.tab = m_tab;
				m_items.push_back(tempRect);
			}
		}

		/*!
		* \brief Get key value of item for sorting purpose
		*/
		static int getKey(sf::Rect<int> & item)
		{
			int centerY = item.top + item.height / 2;
			int centerX = item.left + item.width / 2;
			return centerX + centerY*WIN_WIDTH;
		}

		/*!
		* \brief Get index of the parent
		*/
		static unsigned int getParent(unsigned int index) noexcept
		{
			return (index - 1) / 2;
		}

		/*!
		* \brief Get index of left child
		*/
		static unsigned int getChildLeft(unsigned int index) noexcept
		{
			return index * 2 + 1;
		}

		/*!
		* \brief Get index of right child
		*/
		static unsigned int getChildRight(unsigned int index)
		{
			return index * 2 + 2;
		}

		std::vector<RectTree>::iterator end()
		{
			return m_items.end();
		}

		std::vector<RectTree>::iterator begin()
		{
			return m_items.begin();
		}

		std::vector<RectTree>::const_iterator cend() const
		{
			return m_items.cend();
		}

		std::vector<RectTree>::const_iterator cbegin() const
		{
			return m_items.cbegin();
		}

		unsigned int size() const { return m_items.size(); }

	private:
		std::vector<RectTree> m_items;
		int m_tab = 0;
	};

	//--------------------------------------------------------------------------

	/*!
	* \biref Binary tree which stores lowest object on top
	*/
	class ContainerBinTree
	{
	public:
		ContainerBinTree(unsigned int size = 0)
		{
			m_items.reserve(size);
		}
		ContainerBinTree(ContainerBinTree && obj)
		{
			m_items = std::move(obj.m_items);
		}
		ContainerBinTree & operator=(ContainerBinTree && obj)
		{
			m_items = std::move(obj.m_items);
			return *this;
		}
		//ContainerBinTree & operator=(ContainerBinTree & obj)
		//{
		//	m_items = std::move(obj.m_items);
		//	return *this;
		//}
		~ContainerBinTree() noexcept
		{

		}

		/*!
		* \brief Adds new element to the Tree
		*
		* \param item Reference to item
		*
		*/
		void add(std::unique_ptr<Widget> item)
		{
			m_items.push_back(std::move(item));

			// check if new item is not on top of the tree
			if (m_items.size() > 1)
			{
				unsigned int index = m_items.size() - 1;
				while (true)
				{
					unsigned int parentIndex = getParent(index);
					sf::Vector2f center = m_items[index]->getLocalCenter();
					sf::Vector2f parentCenter = m_items[parentIndex]->getLocalCenter();
					if ((center.x + center.y*WIN_WIDTH) < (parentCenter.x + parentCenter.y*WIN_WIDTH))
					{
						std::swap(m_items[index], m_items[parentIndex]);
					}
					else
						break;

					if (parentIndex == 0)
						break;
					else
						index = parentIndex;
				}
			}
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

		std::vector<std::unique_ptr<Widget>>::iterator end()
		{
			return m_items.end();
		}

		std::vector<std::unique_ptr<Widget>>::iterator begin()
		{
			return m_items.begin();
		}

		std::vector<std::unique_ptr<Widget>>::const_iterator cend() const
		{
			return m_items.cend();
		}

		std::vector<std::unique_ptr<Widget>>::const_iterator cbegin() const
		{
			return m_items.cbegin();
		}

		unsigned int size() const { return m_items.size(); }

	private:
		std::vector<std::unique_ptr<Widget>> m_items;	///< vector of all widgets
		//std::vector<unsigned int> m_id;					///< vector of id to widgets
	};
}