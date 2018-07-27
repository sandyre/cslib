#include <gtest/gtest.h>

#include <cslib/algorithm/search/linear_search.hpp>

#include <vector>

template <typename T>
using DefaultContainer = std::vector<T>;

TEST(linear_search, empty_input)
{
	DefaultContainer<int> container;

	EXPECT_TRUE(cslib::algorithm::linear_search(container.begin(), container.end(), 5) == container.end());
}

TEST(linear_search, simple_input)
{
	DefaultContainer<int> container { 0, 10, 5, 4, 3 };

	EXPECT_TRUE(cslib::algorithm::linear_search(container.begin(), container.end(), 5) == container.begin() + 2);
	EXPECT_TRUE(cslib::algorithm::linear_search(container.begin(), container.end(), 8) == container.end());
}
