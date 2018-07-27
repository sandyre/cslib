#ifndef CSLIB_ALGORITHM_SORT_BUBBLE_SORT_HPP
#define CSLIB_ALGORITHM_SORT_BUBBLE_SORT_HPP

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
#include <iterator>
#include <type_traits>

namespace cslib {
namespace algorithm
{

	/* Name: Bubble Sort
	 * Runtime complexity: O(n^2)
	 * Space complexity: O(1)
	 *
	 * Interesting fact:
	 * If CompareT::operator() does strong check (i.e. < OR >), this algorithm is stable. Overwise it's not.
	 *
	 * TODO: iterator must be RandomAccessIterator, add this check
	 */

	template < typename IteratorT, typename CompareT = std::less<typename std::iterator_traits<IteratorT>::value_type> >
	void bubble_sort(IteratorT first, IteratorT last, CompareT compare = CompareT())
	{
		for (IteratorT iIter = first; iIter != last; ++iIter)
		{
			for (IteratorT jIter = first; jIter != last; ++jIter)
				if (!compare(*iIter, *jIter))
					std::iter_swap(iIter, jIter);
		}
	}

}}

#endif
