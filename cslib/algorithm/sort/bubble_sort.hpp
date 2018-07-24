#ifndef CSLIB_ALGORITHM_SORT_BUBBLE_SORT_HPP
#define CSLIB_ALGORITHM_SORT_BUBBLE_SORT_HPP

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
