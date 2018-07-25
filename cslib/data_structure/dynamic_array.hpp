#ifndef CSLIB_DATA_STRUCTURE_DYNAMIC_ARRAY_HPP
#define CSLIB_DATA_STRUCTURE_DYNAMIC_ARRAY_HPP

#include <cmath>
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
	 * TODO: insert(), remove()
	 */

	template < typename ValueT >
	class dynamic_array
	{
	public:
		using value_type			= ValueT;
		using pointer				= ValueT*;
		using const_pointer			= const ValueT*;
		using reference				= ValueT&;
		using const_reference		= const ValueT&;
		using iterator				= pointer;
		using const_iterator		= const_pointer;
		using size_type				= size_t;

	private:
		using PassingValueT = typename std::conditional<std::is_fundamental<ValueT>::value, ValueT, const ValueT&>::type;
		using StorageT = void*;

	private:
		StorageT		_storage;
		size_type		_capacity;
		size_type		_size;

	public:
		dynamic_array()
			:	_storage(std::nullptr),
				_capacity(),
				_size()
		{ }

		~dynamic_array()
		{ delete _storage; }

		explicit dynamic_array(size_t initialSize)
			:	_storage(new ValueT[initialSize]),
				_capacity(initialSize),
				_size(initialSize)
		{ }

		void push_back(PassingValueT value)
		{
			ensure_capacity(_size + 1);
			new(_storage[size() * sizeof(ValueT)]) ValueT(value);
		}

		void pop_back()
		{
			reinterpret_cast<pointer>(_storage[size() - 1 * sizeof(ValueT)])->~ValueT();
			--_size;
		}

		reference at(size_type index)			{ return _storage[index]; }
		reference operator[](size_type index)	{ return at(index); }

		iterator begin() const			{ return _storage; }
		iterator end() const			{ return _storage + size(); }
		const_iterator cbegin() const	{ return begin(); }
		const_iterator cend() const		{ return end(); }

		void clear()			{ _size = 0; }
		size_type size() const	{ return _size; }

	private:
		void ensure_capacity(size_t newSize)
		{
			if (newSize >= _capacity)
			{
				const size_type newCapacity = _capacity * static_cast<size_type>(std::ceil(std::log2(newSize / _capacity)));
				StorageT newStorage = ::operator new(newCapacity);
				std::move(_storage, _storage + _size * sizeof(ValueT), newStorage);
				delete [] _storage;

				_storage = newStorage;
				_capacity = newCapacity;
				_size = newSize;
			}
		}
	};

}}

#endif
