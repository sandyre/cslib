#ifndef CSLIB_ALGORITHM_SEARCH_LINEAR_SEARCH_HPP
#define CSLIB_ALGORITHM_SEARCH_LINEAR_SEARCH_HPP

#include <iterator>
#include <type_traits>

namespace cslib {
namespace algorithm
{

	/* Name: Linear search
	 * Runtime complexity: O(n)
	 * Space complexity: O(1)
	 */

	template <
			typename IteratorT,
			typename ValueT = typename std::iterator_traits<IteratorT>::value_type,
			typename PassingValueT = typename std::conditional<std::is_fundamental<ValueT>::value, ValueT, const ValueT&>::type,
			typename = typename std::enable_if<
				std::is_convertible<
						typename std::iterator_traits<IteratorT>::iterator_category,
						typename std::input_iterator_tag
				>::value
			>::type
	>
	IteratorT linear_search(IteratorT first, IteratorT last, PassingValueT value)
	{
		for (IteratorT iter = first; iter != last; ++iter)
			if (*iter == value)
				return iter;
		return last;
	}

}}

#endif
