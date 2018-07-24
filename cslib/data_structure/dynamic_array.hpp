#ifndef CSLIB_DATA_STRUCTURE_DYNAMIC_ARRAY_HPP
#define CSLIB_DATA_STRUCTURE_DYNAMIC_ARRAY_HPP

#include <stdexcept>

namespace cslib {
namespace data_structure
{

	/* Name: Dynamic array
	 * Runtime operations complexity:
	 * - Access: O(1)
	 * - Search: O(n)
	 * - Insertion: O(n), at the end - amortized constant O(1)
	 * - Deletion: O(n), at the end - constant O(1)
	 *
	 * Space complexity: O(n)
	 *
	 * TODO: push_back(), push_front(), insert(), remove()
	 */

	template < typename ValueT >
	class dynamic_array
	{
		using PassingValueT = typename std::conditional<std::is_fundamental<ValueT>::value, ValueT, const ValueT&>::type;

	private:
		ValueT*		_storage;
		size_t		_size;

	public:
		dynamic_array()
			:	_storage(std::nullptr),
				_size()
		{ }

		explicit dynamic_array(size_t initialSize)
			:	_storage(new ValueT[initialSize]),
				_size(initialSize)
		{ }

		ValueT& at(size_t index)
		{ return _storage[index]; }
	};

}}

#endif
