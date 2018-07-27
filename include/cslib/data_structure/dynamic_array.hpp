#ifndef CSLIB_DATA_STRUCTURE_DYNAMIC_ARRAY_HPP
#define CSLIB_DATA_STRUCTURE_DYNAMIC_ARRAY_HPP

// MIT License
//
// Copyright (c) 2018 Alexandr Borzykh
//
// Permission is hereby granted, free of charge, to any person obtaining a copy
// of this software and associated documentation files (the "Software"), to deal
// in the Software without restriction, including without limitation the rights
// to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
// copies of the Software, and to permit persons to whom the Software is
// furnished to do so, subject to the following conditions:
//
// The above copyright notice and this permission notice shall be included in all
// copies or substantial portions of the Software.
//
// THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
// IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
// FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
// AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
// LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
// OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
// SOFTWARE.

#include <cmath>
#include <functional>
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
		using PassingValueT = typename std::conditional<std::is_fundamental<value_type>::value, value_type, const value_type&>::type;
		using StorageT = char;
		using StoragePointerT = StorageT*;

	private:
		StoragePointerT	_storage;
		size_type		_capacity;
		size_type		_size;

	public:
		dynamic_array()
			:	_storage(new StorageT(4 * sizeof(value_type))),
				_capacity(4),
				_size()
		{ }

		explicit dynamic_array(size_t initialSize, PassingValueT filler = value_type())
			:	_storage(new StorageT[initialSize * sizeof(value_type)]),
				_capacity(initialSize),
				_size(initialSize)
		{ std::fill(begin(), end(), filler); }

		~dynamic_array()
		{ clear(); }

		void push_back(PassingValueT value)
		{
			ensure_capacity(_size + 1);
			new(_storage + size() * sizeof(value_type)) value_type(value);
			++_size;
		}

		void pop_back()
		{
			reinterpret_cast<pointer>(_storage[size() - 1 * sizeof(value_type)])->~value_type();
			--_size;
		}

		reference front()	{ return at(0); }
		reference back()	{ return at(size() - 1); }

		reference at(size_type index)			{ return *reinterpret_cast<pointer>(_storage + index * sizeof(value_type)); }
		reference operator[](size_type index)	{ return at(index); }

		iterator begin() const			{ return reinterpret_cast<iterator>(_storage); }
		iterator end() const			{ return reinterpret_cast<iterator>(_storage + size() * sizeof(value_type)); }
		const_iterator cbegin() const	{ return begin(); }
		const_iterator cend() const		{ return end(); }

		void clear()
		{
			_size = 0;
			std::for_each(begin(), end(), std::bind(&dynamic_array::destructor_caller, this, std::placeholders::_1));
		}

		size_type size() const		{ return _size; }
		size_type capacity() const	{ return _capacity; }
		bool empty() const			{ return !size(); }

	private:
		void ensure_capacity(size_t newSize)
		{
			if (newSize >= _capacity)
			{
				const size_type newCapacity = _capacity * static_cast<size_type>(std::ceil(std::log2(newSize / _capacity)));
				StoragePointerT newStorage = new StorageT[newCapacity];
				std::move(_storage, _storage + _size * sizeof(value_type), newStorage);
				delete [] _storage;

				_storage = newStorage;
				_capacity = newCapacity;
				_size = newSize;
			}
		}

		void destructor_caller(value_type& element)
		{ element.~value_type(); }
	};

}}

#endif
