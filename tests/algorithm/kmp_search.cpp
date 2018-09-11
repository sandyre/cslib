#include <gtest/gtest.h>

#include <cslib/algorithm/search/kmp_search.hpp>

#include <vector>

template <typename T>
using DefaultContainer = std::vector<T>;

TEST(kmp_search, empty_input)
{
	DefaultContainer<int> container;
	DefaultContainer<int> pattern { 5 };

	ASSERT_EQ(cslib::algorithm::kmp_search(container.begin(), container.end(), pattern.begin(), pattern.end()), container.end());
}


TEST(kmp_search, simple_input)
{
	DefaultContainer<int> container { 0, 10, 5, 4, 3 };
	DefaultContainer<int> pattern { 5, 4, 3 };

	ASSERT_EQ(cslib::algorithm::kmp_search(container.begin(), container.end(), pattern.begin(), pattern.end()), container.begin() + 2);
}
