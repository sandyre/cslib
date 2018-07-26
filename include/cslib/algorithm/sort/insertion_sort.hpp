#ifndef CSLIB_ALGORITHM_SORT_INSERTION_SORT_HPP
#define CSLIB_ALGORITHM_SORT_INSERTION_SORT_HPP

#include <algorithm>
#include <iterator>
#include <type_traits>

namespace cslib {
namespace algorithm
{

	/* Name: Insertion sort
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
	void insertion_sort(IteratorT first, IteratorT last, CompareT compare = CompareT())
	{
		if (first == last)
			return;

		IteratorT i, j;
		for (i = first + 1; i != last; ++i)
		{
			j = i - 1;

			while (j >= first && *j > *i)
			{
				*(j + 1) = *j;
				--j;
			}

			*(j + 1) = *i;
		}
	}

}}

#endif
