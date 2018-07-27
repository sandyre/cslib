#ifndef CSLIB_ALGORITHM_SORT_COUNTING_SORT_HPP
#define CSLIB_ALGORITHM_SORT_COUNTING_SORT_HPP

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

#include <algorithm>

namespace cslib {
namespace algorithm
{

	/* Name: Counting Sort
	 * Runtime complexity: O(n)
	 * Space complexity: O(n)
	 *
	 * Interesting fact: this sort's actual space complexity relies on the input distribution.
	 *
	 * TODO:
	 * 1. pass Compare func to set order, I guess.
	 * 2. simple implementation is not stable. Add stable variant.
	 * 3. add check that input is RandomAccessIterator
	 */

	template < typename IteratorT >
	void counting_sort(IteratorT first, IteratorT last)
	{
		using ValueT = std::iterator_traits<IteratorT>::value_type;
		using CountContainerT = std::vector<ValueT>;

		const IteratorT minElement = std::min_element(first, last);
		const IteratorT maxElement = std::max_element(first, last);
		if (minElement == maxElement)
			return;

		CountContainerT counts(std::distance(minElement, maxElement), 0);
		for (IteratorT iter = first; iter != last; iter++)
			++counts[*iter - *minElement];

		IteratorT resultIter = first;
		for (size_t idx = 0; idx < counts.size(); ++idx)
		{
			if (counts[idx] != 0)
			{
				for (size_t jdx = 0; jdx < counts[idx]; ++jdx, ++resultIter)
					*resultIter = idx + *minElement;
			}
		}
	}

}}

#endif
