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
	 *
	 * Interesting fact: this is implementation of not self-balancing tree.
	 *
	 * TODO: implement
	 */

	template < typename KeyT, typename ValueT >
	class binary_search_tree
	{
	public:
		using value_type			= ValueT;
		using key_type				= KeyT;
		using pointer				= ValueT*;
		using const_pointer			= const ValueT*;
		using reference				= ValueT&;

	private:
		using KeyPassingT	= typename std::conditional<std::is_fundamental<KeyT>::value, KeyT, const KeyT&>::type;
		using ValuePassingT	= typename std::conditional<std::is_fundamental<ValueT>::value, ValueT, const ValueT&>::type;

		struct binary_tree_node
		{
			KeyT	Key;
			ValueT	Value;
		};

	private:
		binary_tree_node*	_root;

	public:
		reference at(KeyPassingT key);
		void insert(KeyPassingT key, ValuePassingT value);
		void remove(KeyPassingT key);
	};

}}

#endif
