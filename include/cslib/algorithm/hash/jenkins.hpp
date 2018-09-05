#ifndef CSLIB_ALGORITHM_HASH_JENKINS_HPP
#define CSLIB_ALGORITHM_HASH_JENKINS_HPP

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

#include <cstdint>
#include <type_traits>

namespace cslib {
namespace algorithm
{

	namespace Detail
	{

		uint32_t jenkins_hash_impl(const char* data, size_t size)
		{
			uint32_t hash = 0;

			for (size_t idx = 0; idx < size; ++idx)
			{
				hash += data[idx];
				hash += hash << 10;
				hash ^= hash >> 6;
			}

			hash += hash << 3;
			hash ^= hash >> 11;
			hash += hash << 15;

			return hash;
		}

	}


	template <typename ValueT>
	uint32_t jenkins_hash(ValueT data)
	{ return Detail::jenkins_hash_impl(reinterpret_cast<char*>(&data), sizeof(ValueT)); }

}}

#endif
