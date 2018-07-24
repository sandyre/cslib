#ifndef CSLIB_DATA_STRUCTURE_STACK_HPP
#define CSLIB_DATA_STRUCTURE_STACK_HPP

#include <cslib/data_structure/dynamic_array.hpp>

namespace cslib {
namespace data_structure
{

	/* Name: Stack
	 * Runtime operations complexity:
	 * - Access: O(n)
	 * - Search: O(n)
	 * - Insertion: O(1), assuming underlying container to be Dynamic array, which has insertion of first element complexity as amortized constant O(1)
	 * - Deletion: O(1), assuming underlying container to be Dynamic array, which has deletion of last element complexity as amortized constant O(1)
	 *
	 * Space complexity: O(n)
	 */

	template < typename ValueT >
	class stack
	{
		using PassingValueT = typename std::conditional<std::is_fundamental<ValueT>::value, ValueT, const ValueT&>::type;

	private:
		dynamic_array<ValueT>	_container;
		size_t					_currentIndex;

	public:
		stack()
			:	_currentIndex()
		{ }

		ValueT& top()
		{ return _container[_currentIndex]; }

		void push(PassingValueT value)
		{
			_container.push_back(value);
			++_currentIndex;
		}

		void pop()
		{
			_container.pop_back();
			--_currentIndex;
		}

		size_t size() const
		{ return _currentIndex; }

		bool empty() const
		{ return _currentIndex; }
	};

}}

#endif
