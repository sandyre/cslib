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

#include <cslib/algorithm/for_each.hpp>

#include <algorithm>
#include <cmath>
#include <functional>
#include <initializer_list>
#include <memory>
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
		using allocator				= std::allocator<value_type>;
		using pointer				= ValueT*;
		using const_pointer			= const ValueT*;
		using reference				= ValueT&;
		using const_reference		= const ValueT&;
		using iterator				= pointer;
		using const_iterator		= const_pointer;
		using size_type				= size_t;

	private:
		allocator						_allocator;
		typename allocator::pointer		_data;
		size_type						_capacity;
		size_type						_size;

	public:
		dynamic_array();
		explicit dynamic_array(size_type initial_size);
		dynamic_array(size_type initial_size, const value_type& filler);
		dynamic_array(const dynamic_array& other);
		dynamic_array(dynamic_array&& other);
		dynamic_array(std::initializer_list<value_type> value);

		~dynamic_array() noexcept;

		void push_back(const value_type& value);
		void pop_back() noexcept;

		reference front() noexcept;
		reference back() noexcept;

		reference at(size_type index) noexcept;
		reference operator[](size_type index) noexcept;

		iterator begin() const noexcept;
		iterator end() const noexcept;
		const_iterator cbegin() const noexcept;
		const_iterator cend() const noexcept;

		void clear() noexcept;

		size_type size() const noexcept;
		size_type capacity() const noexcept;
		bool empty() const noexcept;

	private:
		void ensure_capacity(size_type new_size)
		{
			if (new_size >= _capacity)
			{
				size_type new_capacity = 1;
				if (new_size && !(new_size & (new_size - 1)))
					new_capacity = new_size;
				else
					while (new_capacity < new_size)
						new_capacity <<= 1;

				typename allocator::pointer new_storage = std::allocator_traits<allocator>::allocate(_allocator, new_capacity);
				std::copy(_data, _data + size(), new_storage);

				algorithm::for_each_iterator(begin(), end(), [&](pointer ptr) { std::allocator_traits<allocator>::destroy(_allocator, ptr); });
				std::allocator_traits<allocator>::deallocate(_allocator, _data, _capacity);

				_data = new_storage;
				_capacity = new_capacity;
				_size = new_size;
			}
		}
	};


	template < typename ValueT >
	dynamic_array<ValueT>::dynamic_array()
		:	_data(std::allocator_traits<dynamic_array::allocator>::allocate(_allocator, 4)),
			_capacity(4),
			_size()
	{ }


	template < typename ValueT >
	dynamic_array<ValueT>::dynamic_array(size_type initial_size)
		:	_data(std::allocator_traits<allocator>::allocate(_allocator, initial_size)),
			_capacity(initial_size),
			_size(initial_size)
	{ algorithm::for_each_iterator(begin(), end(), [&](pointer ptr) { std::allocator_traits<allocator>::construct(_allocator, ptr); }); }


	template < typename ValueT >
	dynamic_array<ValueT>::dynamic_array(size_type initial_size, const value_type& filler)
		:	_data(std::allocator_traits<allocator>::allocate(_allocator, initial_size)),
			_capacity(initial_size),
			_size(initial_size)
	{ algorithm::for_each_iterator(begin(), end(), std::bind(&std::allocator_traits<allocator>::construct, std::ref(_allocator), std::placeholders::_1, filler)); }


	template < typename ValueT >
	dynamic_array<ValueT>::dynamic_array(const dynamic_array& other)
		:	_data(std::allocator_traits<allocator>::allocate(_allocator, other._size)),
			_capacity(other._size),
			_size(other._size)
	{ std::copy(other.begin(), other.end(), begin()); }


	template < typename ValueT >
	dynamic_array<ValueT>::dynamic_array(dynamic_array&& other)
		:	_allocator(other._allocator),
			_data(other._data),
			_capacity(other._capacity),
			_size(other._size)
	{
		other._data = nullptr;
		other._capacity = 0;
		other._size = 0;
	}


	template < typename ValueT >
	dynamic_array<ValueT>::dynamic_array(std::initializer_list<value_type> value)
		:	_data(std::allocator_traits<allocator>::allocate(_allocator, value.size())),
			_capacity(value.size()),
			_size(value.size())
	{ std::copy(value.begin(), value.end(), begin()); }


	template < typename ValueT >
	dynamic_array<ValueT>::~dynamic_array() noexcept
	{
		clear();
		std::allocator_traits<allocator>::deallocate(_allocator, _data, _capacity);
	}


	template < typename ValueT >
	void dynamic_array<ValueT>::push_back(const value_type& value)
	{
		ensure_capacity(_size + 1);
		std::allocator_traits<allocator>::construct(_allocator, end(), value);
		++_size;
	}


	template < typename ValueT >
	void dynamic_array<ValueT>::pop_back() noexcept
	{
		std::allocator_traits<allocator>::destroy(_allocator, end() - 1);
		--_size;
	}

	template < typename ValueT >
	typename dynamic_array<ValueT>::reference dynamic_array<ValueT>::front() noexcept
	{ return at(0); }


	template < typename ValueT >
	typename dynamic_array<ValueT>::reference dynamic_array<ValueT>::back() noexcept
	{ return at(size() - 1); }


	template < typename ValueT >
	typename dynamic_array<ValueT>::reference dynamic_array<ValueT>::at(size_type index) noexcept
	{ return *(_data + index); }


	template < typename ValueT >
	typename dynamic_array<ValueT>::reference dynamic_array<ValueT>::operator[](size_type index) noexcept
	{ return at(index); }


	template < typename ValueT >
	typename dynamic_array<ValueT>::iterator dynamic_array<ValueT>::begin() const noexcept
	{ return _data; }


	template < typename ValueT >
	typename dynamic_array<ValueT>::iterator dynamic_array<ValueT>::end() const noexcept
	{ return _data + size(); }


	template < typename ValueT >
	typename dynamic_array<ValueT>::const_iterator dynamic_array<ValueT>::cbegin() const noexcept
	{ return begin(); }


	template < typename ValueT >
	typename dynamic_array<ValueT>::const_iterator dynamic_array<ValueT>::cend() const noexcept
	{ return end(); }


	template < typename ValueT >
	void dynamic_array<ValueT>::clear() noexcept
	{ algorithm::for_each_iterator(begin(), end(), [&](pointer ptr) { std::allocator_traits<allocator>::destroy(_allocator, ptr); }); }


	template < typename ValueT >
	typename dynamic_array<ValueT>::size_type dynamic_array<ValueT>::size() const noexcept
	{ return _size; }


	template < typename ValueT >
	typename dynamic_array<ValueT>::size_type dynamic_array<ValueT>::capacity() const noexcept
	{ return _capacity; }


	template < typename ValueT >
	bool dynamic_array<ValueT>::empty() const noexcept
	{ return !size(); }


	template < typename ValueT >
	bool operator==(const dynamic_array<ValueT>& lhs, const dynamic_array<ValueT>& rhs)
	{
		if (lhs.size() != rhs.size())
			return false;

		return std::equal(lhs.begin(), lhs.end(), rhs.begin());
	}


	template < typename ValueT >
	bool operator!=(const dynamic_array<ValueT>& lhs, const dynamic_array<ValueT>& rhs)
	{ return !(lhs == rhs); }

}}

#endif
