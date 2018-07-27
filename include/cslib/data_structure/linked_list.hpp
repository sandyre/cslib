#ifndef CSLIB_DATA_STRUCTURE_LINKED_LIST_HPP
#define CSLIB_DATA_STRUCTURE_LINKED_LIST_HPP

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

#include <algorithm>

namespace cslib {
namespace data_structure
{

	/* Name: Singly linked list
	 *
	 * TODO:
	 * 1. operations complexity
	 */

	template < typename ValueT >
	class singly_linked_list
	{
		using PassingValueT = typename std::conditional<std::is_fundamental<ValueT>::value, ValueT, const ValueT&>::type;

	private:
		struct list_node
		{
			ValueT		Value;
			list_node*	Next;

		public:
			list_node(PassingValueT value, list_node* next = std::nullptr)
				:	Value(value),
					Next(next)
			{ }
		};

	private:
		list_node*		_root;

	public:
		singly_linked_list()
			:	_root(std::nullptr),
				_size()
		{ }

		~singly_linked_list()
		{ clear(); }

		void push_front(PassingValueT value)
		{ _root = new list_node(value, _root); }

		void pop_front()
		{
			if (!_root)
				return;

			list_node* newRoot = _root->Next;
			delete _root;
			_root = newRoot;
		}

		/* void erase_after(iterator); */
		/* void insert_after(iterator); */
		/* void swap(iterator, iterator); */

		void clear()
		{
			while (_root)
				pop_front();
		}
	};

}}

#endif
