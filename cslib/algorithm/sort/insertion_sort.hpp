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
		const std::ptrdiff_t size = std::distance(first, last);
		if (size <= 1)
			return;

		size_t i, j;
		IteratorT key;
		for (size_t i = 1; i < size; ++i)
		{
			key = first + i;
			j = i - 1;

			while (j >= 0 && compare(*(first + j), *key))
			{
				std::iter_swap(first + j + 1, first + j);
				j = j - 1;
			}

			*(first + j + 1) = *key;
		}
	}

}}

#endif
