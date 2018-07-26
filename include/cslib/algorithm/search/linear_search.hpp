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
	 *
	 * TODO: add check that input iterator is ForwardIterator
	 */

	template < typename IteratorT, typename ValueT = typename std::iterator_traits<IteratorT>::value_type >
	IteratorT linear_search(IteratorT first, IteratorT last, typename std::conditional<std::is_fundamental<ValueT>::value, ValueT, const ValueT&>::type value)
	{
		for (IteratorT iter = first; iter != last; ++iter)
			if (*iter == value)
				return iter;
		return last;
	}

}}

#endif
