#ifndef CSLIB_ALGORITHM_SEARCH_LINEAR_SEARCH_HPP
#define CSLIB_ALGORITHM_SEARCH_LINEAR_SEARCH_HPP

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

#include <iterator>
#include <type_traits>

namespace cslib {
namespace algorithm
{

	/* Name: Linear search
	 * Runtime complexity: O(n)
	 * Space complexity: O(1)
	 */

	template <
			typename IteratorT,
			typename ValueT = typename std::iterator_traits<IteratorT>::value_type,
			typename PassingValueT = typename std::conditional<std::is_fundamental<ValueT>::value, ValueT, const ValueT&>::type,
			typename = typename std::enable_if<
				std::is_convertible<
						typename std::iterator_traits<IteratorT>::iterator_category,
						typename std::input_iterator_tag
				>::value
			>::type
	>
	IteratorT linear_search(IteratorT first, IteratorT last, PassingValueT value)
	{
		for (IteratorT iter = first; iter != last; ++iter)
			if (*iter == value)
				return iter;
		return last;
	}

}}

#endif
