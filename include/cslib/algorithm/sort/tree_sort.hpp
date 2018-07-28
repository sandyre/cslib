#ifndef CSLIB_ALGORITHM_SORT_TREE_SORT_HPP
#define CSLIB_ALGORITHM_SORT_TREE_SORT_HPP

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

#include <cslib/data_structure/tree/binary_search_tree.hpp>

namespace cslib {
namespace algorithm
{

	/* Name: Tree sort
	 * Runtime complexity: O(nlog(n))
	 * Space complexity: O(n)
	 *
	 * Interesting fact: this implementation is actually O(nlog(n)log(n)), since implementation of binary_search_tree does not allow duplicates,
	 * so workaround is used: as value we store count of same nodes.
	 */

	template <
			typename IteratorT,
			typename ValueT = typename std::iterator_traits<IteratorT>::value_type,
			typename = typename std::enable_if<
				std::is_convertible<
						typename std::iterator_traits<IteratorT>::iterator_category,
						typename std::input_iterator_tag
				>::value
			>::type
	>
	void tree_sort(IteratorT first, IteratorT last)
	{
		using tree_type = data_structure::binary_search_tree<ValueT, size_t>;

		tree_type tree;

		for (IteratorT iter = first; iter != last; ++iter)
		{
			typename tree_type::iterator tree_it = tree.find(*iter);
			if (tree_it == tree.end())
				tree.insert(*iter, 1);
			else
				++(*tree_it).second;
		}

		IteratorT output = first;
		for (typename tree_type::iterator iter = tree.begin(); iter != tree.end(); ++iter)
		{
			while ((*iter).second)
			{
				*output = (*iter).first;
				--(*iter).second;
				++output;
			}
		}
	}

}}

#endif
