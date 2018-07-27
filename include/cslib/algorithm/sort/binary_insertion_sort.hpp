#ifndef CSLIB_ALGORITHM_SORT_INSERTION_SORT_HPP
#define CSLIB_ALGORITHM_SORT_INSERTION_SORT_HPP

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

#include <cslib/algorithm/search/binary_search.hpp>

namespace cslib {
namespace algorithm
{

	/* Name: Binary insertion sort
	 * Runtime complexity: O(n^2)
	 * Space complexity: O(1)
	 *
	 * Interesting fact:
	 * If CompareT::operator() does strong check (i.e. < OR >), this algorithm is stable. Overwise it's not.
	 *
	 * TODO: iterator must be RandomAccessIterator, add this check
	 */

	template <
			typename IteratorT,
			typename ValueT = typename std::iterator_traits<IteratorT>::value_type,
			typename CompareT = std::less<ValueT>::value_type>
	>
	void binary_insertion_sort(IteratorT first, IteratorT last, CompareT compare = CompareT())
	{
		if (first == last)
			return;

		IteratorT i, j, location;
		for (i = first + 1; i != last; ++i)
		{
			j = i - 1;
			location = binary_search(first, i, *i, compare);

			while (j >= location)
			{
				*(j + 1) = *j;
				--j;
			}

			*(j + 1) = *i;
		}
	}

}}

#endif
