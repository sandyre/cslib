#ifndef CSLIB_DATA_STRUCTURE_STACK_HPP
#define CSLIB_DATA_STRUCTURE_STACK_HPP

// MIT License
//
// Copyright (c) 2018 Alexandr Borzykh
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <cslib/data_structure/dynamic_array.hpp>

namespace cslib {
namespace data_structure
{

	/* Name: Stack
	 * Runtime operations complexity:
	 * - Access: O(n)
	 * - Search: O(n)
	 * - Insertion: O(1), assuming underlying container to be Dynamic array, which has insertion of first element complexity as amortized constant O(1)
	 * - Deletion: O(1), assuming underlying container to be Dynamic array, which has deletion of last element complexity as amortized constant O(1)
	 *
	 * Space complexity: O(n)
	 */

	template < typename ValueT >
	class stack
	{
	public:
		using value_type			= ValueT;
		using reference				= ValueT&;
		using const_reference		= const ValueT&;
		using size_type				= size_t;

	private:
		using PassingValueT = typename std::conditional<std::is_fundamental<value_type>::value, value_type, const_reference>::type;

	private:
		dynamic_array<ValueT>	_container;
		size_t					_endIndex;

	public:
		stack()
			:	_endIndex()
		{ }

		reference top()
		{ return _container[_endIndex - 1]; }

		void push(PassingValueT value)
		{
			_container.push_back(value);
			++_endIndex;
		}

		void pop()
		{
			_container.pop_back();
			--_endIndex;
		}

		bool operator==(const stack& other) const
		{ return _container == other._container; }

		bool operator!=(const stack& other) const
		{ return !operator==(other); }

		size_type size() const
		{ return _endIndex; }

		bool empty() const
		{ return !size(); }
	};

}}

#endif
