#ifndef CSLIB_DATA_STRUCTURE_TREE_BINARY_SEARCH_TREE_HPP
#define CSLIB_DATA_STRUCTURE_TREE_BINARY_SEARCH_TREE_HPP

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

#include <type_traits>

namespace cslib {
namespace data_structure
{

	/* Name: Binary search tree
	 * Runtime operations complexity:
	 * - Access: O(log(n))
	 * - Search: O(log(n))
	 * - Insertion: O(log(n))
	 * - Deletion: O(log(n))
	 *
	 * Space complexity: O(n)
	 */

	template < typename KeyT, typename ValueT >
	class binary_search_tree
	{
	public:
		using value_type			= ValueT;
		using key_type				= KeyT;
		using pointer				= value_type*;
		using const_pointer			= const value_type*;
		using reference				= value_type&;

	private:
		using key_passing_type		= typename std::conditional<std::is_fundamental<value_type>::value, key_type, const key_type&>::type;
		using value_passing_type	= typename std::conditional<std::is_fundamental<value_type>::value, value_type, const value_type&>::type;

		struct bst_node
		{
			key_type		_key;
			value_type		_value;

			bst_node*		_left_child;
			bst_node*		_right_child;

		public:
			bst_node(
					key_passing_type key,
					value_passing_type value,
					bst_node* left_child = nullptr,
					bst_node* right_child = nullptr)
				:	_key(key),
					_value(value),
					_left_child(left_child),
					_right_child(right_child)
			{ }
		};

	private:
		bst_node*	_root;

	public:
		binary_search_tree()
			:	_root(nullptr)
		{ }

		reference at(key_passing_type key)
		{
			bst_node* node = find_node(key);
			return node->_value;
		}

		void insert(key_passing_type key, value_passing_type value)
		{
			if (!_root)
			{
				_root = new bst_node(key, value);
				return;
			}

			bst_node* current = _root;

			while (true)
			{
				if (current->_key == key)
				{
					current->_value = value;
					return;
				}

				if (current->_key > key)
				{
					if (!current->_left_child)
					{
						current->_left_child = new bst_node(key, value);
						return;
					}
					else
						current = current->_left_child;
				}
				else
				{
					if (!current->_right_child)
					{
						current->_right_child = new bst_node(key, value);
						return;
					}
					else
						current = current->_right_child;
				}
			}
		}

		void remove(key_passing_type key);

	private:
		bst_node* find_node(key_passing_type key)
		{
			bst_node* current = _root;
			while (current)
			{
				if (current->_key == key)
					break;

				if (current->_key > key)
					current = current->_right_child;
				else
					current = current->_left_child;
			}

			return current;
		}
	};

}}

#endif
