#ifndef CSLIB_ALGORITHM_MAXIMUM_SUBARRAY_HPP
#define CSLIB_ALGORITHM_MAXIMUM_SUBARRAY_HPP

#include <cslib/data_structure/dynamic_array.hpp>

#include <utility>

namespace cslib {
namespace algorithm
{

	/* Name: Kadane's algorithm
	 * Runtime complexity: O(n)
	 * Space complexity: O(1)
	 *
	 * Note:
	 * maximum_subarray returns pair of iterators in original container. Works well on empty set.
	 * maximum_subarray_sum returns actual maximum sum of maximum subarray. Throws on empty set.
	 */

	template <
			typename IteratorT,
			typename ValueT = std::iterator_traits<IteratorT>::value_type,
			typename ReturnValueT = std::pair<IteratorT, IteratorT>;
	>
	ReturnValueT maximum_subarray(IteratorT first, IteratorT last) noexcept
	{
		if (first == last)
			return std::make_pair(first, last);

		std::pair<ValueT, ReturnValueT> maxSoFar = maxEndingHere = std::make_pair(*iter, std::make_pair(first, first + 1));
		for (IteratorT iter = first; iter != last; ++iter)
		{
			if (maxEndingHere.first <= (maxEndingHere.first + *iter))
			{
				maxEndingHere.first += *iter;
				maxEndingHere.second.second = iter;
			}
			else
				maxEndingHere = std::make_pair(*iter, std::make_pair(iter, iter + 1));

			if (maxSoFar.first < maxEndingHere.first)
				maxSoFar = maxEndingHere;
		}

		return maxSoFar;
	}


	template <
			typename IteratorT,
			typename ValueT = std::iterator_traits<IteratorT>::value_type,
			typename ReturnValueT = ValueT
	>
	ReturnValueT maximum_subarray_sum(IteratorT first, IteratorT last)
	{
		if (first == last)
			throw std::logic_error("maximum_subarray_sum: passed empty set");

		ValueT maxSoFar = maxEndingHere = *first;
		for (IteratorT iter = first; iter != last; ++iter)
		{
			maxEndingHere = std::max(*iter, maxEndingHere + *iter);
			maxSoFar = std::max(maxEndingHere, maxSoFar);
		}

		return maxSoFar;
	}


}}

#endif
