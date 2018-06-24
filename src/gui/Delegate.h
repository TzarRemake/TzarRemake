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

#include <utility>

//--------------------------------------------------------------------------

namespace gui
{
	template<typename T> class Delegate;

	template<typename R, typename ...Args>
	class Delegate<R(Args...)>
	{
	private:
		using function_type = R(*)(void*, Args&&...);	///< This is basic type for method pointer 

		Delegate(void * const oPtr, function_type const fPtr) :
			m_objectPtr{ oPtr }, m_functionPtr{ fPtr }
		{

		}

	public:
		Delegate() = delete;							///< Deleted default constructor
		~Delegate() noexcept {}							///< Destructor don't throw exceptions
		Delegate(const Delegate & obj) = default;		///< Copy constructor
		Delegate(Delegate && obj) = default;			///< Move constructor
		Delegate & operator=(Delegate & obj) = default;	///< Assignement operator
		Delegate & operator=(Delegate && obj) = default;///< Move assignement operator

		template<typename C, R(C::* const methodPtr)(Args...) >
		static Delegate factory(C * const objectPtr) noexcept
		{
			return{ objectPtr, methodProc<C, methodPtr> };
		}

		R operator()(Args... args) const
		{
			return m_functionPtr(m_objectPtr, ::std::forward<Args>(args)...);
		}


	private:
		void * m_objectPtr;				///< Object pointer
		function_type m_functionPtr;	///< Pointer to function

		template <class C, R(C::* const methodPtr)(Args...)>
		static R methodProc(void* const subscriberPtr, Args&&... args)
		{
			return (static_cast<C* const>(subscriberPtr)->*methodPtr)(
				::std::forward<Args>(args)...);
		}
	};
}