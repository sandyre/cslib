#ifndef CSLIB_ALGORITHM_SEARCH_BINARY_SEARCH_HPP
#define CSLIB_ALGORITHM_SEARCH_BINARY_SEARCH_HPP

#include <algorithm>
#include <iterator>
#include <type_trait>

namespace cslib {
namespace algorithm
{

	/* Name: Binary search
	 * Runtime complexity: O(log(n))
	 * Space complexity: O(1)
	 *
	 * Interesting fact: it works only on a sorted input array. Returns garbage otherwise.
	 *
	 * TODO: add check that input iterator is RandomAccessIterator
	 */

	template <
			typename IteratorT,
			typename ValueT = typename std::iterator_traits<IteratorT>::value_type,
			typename ValuePassingT = typename std::conditional<std::is_fundamental<ValueT>::value, ValueT, const ValueT&>::type,
			typename CompareT = std::less<ValueT>::value_type>
	>
	IteratorT binary_search(IteratorT first, IteratorT last, ValuePassingT value, CompareT compare = CompareT())
	{
		if (first == last)
			return last;

		IteratorT begin = first, end = last, current;
		do
		{
			current = begin + std::distance(begin, end) / 2;
			ValuePassingT currentVal = *current;

			if (currentVal == value)
				return current;

			if (!compare(currentVal, value))
				end = current;
			else
				begin = current;
		} while (begin != end)

		return last;
	}

}}
