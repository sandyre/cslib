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

#include <cslib/data_structure/stack.hpp>

#include <utility>

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
		struct inorder_iterator;
		struct preorder_iterator;
		struct postorder_iterator;

	public:
		using value_type			= ValueT;
		using key_type				= KeyT;
		using pointer				= value_type*;
		using const_pointer			= const value_type*;
		using reference				= value_type&;
		using const_reference		= const value_type&;
		using iterator				= inorder_iterator;
		using const_iterator		= const inorder_iterator;

	private:
		using key_passing_type		= typename std::conditional<std::is_fundamental<value_type>::value, key_type, const key_type&>::type;
		using value_passing_type	= typename std::conditional<std::is_fundamental<value_type>::value, value_type, const value_type&>::type;

		struct bst_node
		{
			std::pair<key_type, value_type>		_key_value;
			bst_node*							_parent;
			bst_node*							_left_child;
			bst_node*							_right_child;

		public:
			bst_node(
					key_passing_type key,
					value_passing_type value,
					bst_node* parent = nullptr,
					bst_node* left_child = nullptr,
					bst_node* right_child = nullptr)
				:	_key_value(key, value),
					_parent(parent),
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

		reference at(key_passing_type key) const
		{
			bst_node* node = find_node_in_subtree(_root, key);
			return node->_key_value.second;
		}

		reference operator[](key_passing_type key) const
		{ return at(key); }

		iterator begin() const;
		iterator end() const;

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
				if (current->_key_value.first == key)
				{
					current->_key_value.second = value;
					return;
				}

				if (current->_key_value.first > key)
				{
					if (!current->_left_child)
					{
						current->_left_child = new bst_node(key, value, current);
						return;
					}
					else
						current = current->_left_child;
				}
				else
				{
					if (!current->_right_child)
					{
						current->_right_child = new bst_node(key, value, current);
						return;
					}
					else
						current = current->_right_child;
				}
			}
		}

		void remove(key_passing_type key)
		{ remove_node_from_subtree(_root, key); }

	private:
		bst_node* find_node_in_subtree(bst_node* subtree_root, key_passing_type key) const
		{
			bst_node* current = subtree_root;
			while (current)
			{
				if (current->_key_value.first == key)
					break;

				if (current->_key_value.first > key)
					current = current->_left_child;
				else
					current = current->_right_child;
			}

			return current;
		}

		void remove_node_from_subtree(bst_node* subtree_root, key_passing_type key)
		{
			bst_node* node_to_remove = find_node_in_subtree(subtree_root, key);
			bst_node* parent_node = node_to_remove->_parent;

			switch (const size_t number_of_child = static_cast<bool>(node_to_remove->_left_child) + static_cast<bool>(node_to_remove->_right_child))
			{
			case 0:
			{
				bst_node* node_to_attach = nullptr;
				if (parent_node->_left_child == node_to_remove)
					parent_node->_left_child = node_to_attach;
				else
					parent_node->_right_child = node_to_attach;

				delete node_to_remove;
				break;
			}
			case 1:
			{
				bst_node* node_to_attach = nullptr;
				if (node_to_attach = node_to_remove->_left_child)
					node_to_attach->_parent = parent_node;
				else if (node_to_attach = node_to_remove->_right_child)
					node_to_attach->_parent = parent_node;
				break;

				delete node_to_remove;
			}
			default:
			{
				bst_node* min_node_in_right_subtree = node_to_remove->_right_child;
				while (true)
				{
					if (min_node_in_right_subtree->_left_child)
						min_node_in_right_subtree = min_node_in_right_subtree->_left_child;
					else
						break;
				}

				node_to_remove->_key_value = min_node_in_right_subtree->_key_value;

				remove_node_from_subtree(node_to_remove->_right_child, node_to_remove->_key_value.first);
				break;
			}
			}
		}
	};


	template < typename KeyT, typename ValueT >
	struct binary_search_tree<KeyT, ValueT>::inorder_iterator : public std::iterator<std::forward_iterator_tag, std::pair<KeyT, ValueT> >
	{
	public:
		using value_type	= std::pair<KeyT, ValueT>;
		using reference		= value_type&;

	private:
		stack<bst_node*>	_stack;

	public:
		explicit inorder_iterator(bst_node* root)
		{
			bst_node* current = root;
			while (current)
			{
				_stack.push(current);
				current = current->_left_child;
			}
		}

		inorder_iterator& operator++()
		{
			bst_node* current = _stack.top();
			_stack.pop();

			if (current->_right_child)
			{
				current = current->_right_child;
				while (current)
				{
					_stack.push(current);
					current = current->_left_child;
				}
			}

			return *this;
		}

		inorder_iterator operator++(int)
		{ return ++(*this); }

		bool operator==(inorder_iterator other) const	{ return _stack == other._stack; }
		bool operator!=(inorder_iterator other) const	{ return _stack != other._stack; }
		reference operator*()							{ return _stack.top()->_key_value; }
	};


	template < typename KeyT, typename ValueT >
	typename binary_search_tree<KeyT, ValueT>::iterator binary_search_tree<KeyT, ValueT>::begin() const
	{ return iterator(_root); }


	template < typename KeyT, typename ValueT >
	typename binary_search_tree<KeyT, ValueT>::iterator binary_search_tree<KeyT, ValueT>::end() const
	{ return iterator(nullptr); }

}}

#endif
