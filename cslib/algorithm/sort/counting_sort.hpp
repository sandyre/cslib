#ifndef CSLIB_ALGORITHM_SORT_COUNTING_SORT_HPP
#define CSLIB_ALGORITHM_SORT_COUNTING_SORT_HPP

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
