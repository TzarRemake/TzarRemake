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

//--------------------------------------------------------------------------

namespace mat
{

	/*!
	 *	\brief Matrix class which can hold objects of any type
	 */
	template<class T>
	class Matrix
	{
	public:
		/*!
		 * \brief Constructor
		 *
		 * \param width Width of the matrix
		 * \param height Height of the matrix
		 * \param initializer Value used to initialize all matrix nodes
		 *
		 */
		Matrix(int width, int height, T initializer = T()):
			m_width(width), m_height(height)
		{
			assert(width > 0 && height > 0); // width and height of matrix should be positive values
			int size = width*height;
			assert(size > 0); // no overflow
			m_inputs.resize(size);
			for(int i = 0 ; i < size ; ++i)
			{
				m_inputs[i] = initializer;
			}

		}
		~Matrix() = default;

		/*!
		 * \brief Set value to specified matrix node
		 *
		 * Set value without any bound checking.
		 *
		 * \param width x coordinate of the node
		 * \param height y coordinate of the node
		 * \param value Reference to value which will be saved to specified node of the matrix
		 *
		 */
		void setValue(int width, int height, const T & value)
		{
			m_inputs[height*m_width+width] = value;
		}

		/*!
		* \brief Set value to node of matrix specified by rectangle
		*
		* This function perform bounding check. If some part of rectangle is outside of 
		* matrix bound, then this nodes are ommited but function don't throw exception.
		*
		* \param left top of the rectangle
		* \param top top of the rectangle
		* \param width width of the rectangle
		* \param height height of the rectangle
		* \param value Reference to value which will be saved to specified nodes of the matrix
		*
		*/
		void setValue(int left, int top, int width, int height, const T & value)
		{
			// check if rectangle is inside matrix bound
			int newWidth = width + left;
			int newHeight = height + top;
			if (left >= m_width || top >= m_height || left < 0 || top < 0)
				return;
			if( newWidth > m_width )
			{
				newWidth = m_width;
			}
			if (newHeight > m_height)
			{
				newHeight = m_height;
			}

			for (unsigned i = left; i < newWidth; ++i)
			{
				for (unsigned j = top; j < newHeight; ++j)
				{
					setValue(i, j, value);
				}
			}
		}

		/*!
		 * \brief Return reference to value of specified node
		 *
		 * This function performs bound checking, and throws out_of_range
		 * exception if specified node is outside of this bounds.
		 *
		 * \param width Width of the node
		 * \param height Height of the node
		 *
		 * \return Reference to value inside specified node of the matrix
		 *
		 */
		T & getValue(int width, int height)
		{
			if (width < 0 || height < 0 || width > m_width || height > m_height)
				throw std::out_of_range("");
			return m_inputs[height*m_width + width];
		}

	private:
		std::vector<T> m_inputs;		///< vector of all nodes inside matrix
		//const T default;				///< default value which is assigned to matrix at constructino time
		const int m_width, m_height;	///< size of the matrix
	};
}
