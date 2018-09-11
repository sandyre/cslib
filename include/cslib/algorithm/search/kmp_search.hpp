#ifndef CSLIB_ALGORITHM_SEARCH_KMP_SEARCH_HPP
#define CSLIB_ALGORITHM_SEARCH_KMP_SEARCH_HPP

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

#include <cslib/data_structure/dynamic_array.hpp>

#include <iterator>

namespace cslib {
namespace algorithm
{

	/* Name: Knuth-Morris-Pratt searching algorithm
	 * Runtime complexity: O(n)
	 * Space complexity: O(m), where m is pattern
	 *
	 * Interesting fact: it's widely used with strings, but implementation is generic and can work with basically all containers and types (contained type must have operator==)
	 */

	template < typename IteratorT >
	IteratorT kmp_search(IteratorT begin, IteratorT end, IteratorT pattern_begin, IteratorT pattern_end)
	{
		using iterator_traits = std::iterator_traits<IteratorT>;

		const typename iterator_traits::difference_type source_length = std::distance(begin, end), pattern_length = std::distance(pattern_begin, pattern_end);
		data_structure::dynamic_array<uint32_t> prefix_func(pattern_length, 0);

		uint32_t k;
		IteratorT pattern_iter;
		for (k = 0, pattern_iter = pattern_begin; pattern_iter != pattern_end; ++pattern_iter)
		{
			while ((k > 0) && (*pattern_iter != *(pattern_begin + k)))
				k = prefix_func[k - 1];

			if (*pattern_iter == *(pattern_begin + k))
				++k;

			prefix_func[std::distance(pattern_begin, pattern_iter)] = k;
		}

		IteratorT source_iter;
		for (k = 0, source_iter = begin; source_iter != end; ++source_iter)
		{
			while ((k > 0) && (*(pattern_begin + k) != *source_iter))
				k = prefix_func[k - 1];

			if (*(pattern_begin + k) == *source_iter)
				++k;

			if (k == pattern_length)
				return source_iter - pattern_length + 1;
		}

		return end;
	}

}}

#endif
