#ifndef CSLIB_ALGORITHM_SORT_INSERTION_SORT_HPP
#define CSLIB_ALGORITHM_SORT_INSERTION_SORT_HPP

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
