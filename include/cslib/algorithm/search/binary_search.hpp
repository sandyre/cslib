#ifndef CSLIB_ALGORITHM_SEARCH_BINARY_SEARCH_HPP
#define CSLIB_ALGORITHM_SEARCH_BINARY_SEARCH_HPP

#include <functional>
#include <iterator>
#include <type_traits>

namespace cslib {
namespace algorithm
{

	/* Name: Binary search
	 * Runtime complexity: O(log(n))
	 * Space complexity: O(1)
	 *
	 * Interesting fact: it works only on a sorted input array. Returns garbage otherwise.
	 */

	template <
			typename IteratorT,
			typename ValueT = typename std::iterator_traits<IteratorT>::value_type,
			typename PassingValueT = typename std::conditional<std::is_fundamental<ValueT>::value, ValueT, const ValueT&>::type,
			typename = typename std::enable_if<
				std::is_convertible<
						typename std::iterator_traits<IteratorT>::iterator_category,
						typename std::random_access_iterator_tag
				>::value
			>::type
	>
	IteratorT binary_search(IteratorT first, IteratorT last, PassingValueT value)
	{
		if (first == last)
			return last;

		IteratorT begin = first, end = last, middle;
		while (begin != end)
		{
			middle = begin + std::distance(begin, end) / 2;
			PassingValueT currentValue = *middle;

			if (value < currentValue)
				end = middle;
			else if (value > currentValue)
				begin = middle + 1;
			else
				return middle;
		}

		return last;
	}

}}

#endif
