#include <gtest/gtest.h>

#include <cslib/algorithm/search/binary_search.hpp>

#include <vector>

template <typename T>
using DefaultContainer = std::vector<T>;

TEST(binary_search, empty_input)
{
	DefaultContainer<int> container;

	EXPECT_TRUE(cslib::algorithm::binary_search(container.begin(), container.end(), 5) == container.end());
}

TEST(binary_search, simple_input)
{
	DefaultContainer<int> container { 0, 2, 5, 10, 30, 40 };

	EXPECT_TRUE(cslib::algorithm::binary_search(container.begin(), container.end(), 5) == container.begin() + 2);
	EXPECT_TRUE(cslib::algorithm::binary_search(container.begin(), container.end(), 8) == container.end());
}
