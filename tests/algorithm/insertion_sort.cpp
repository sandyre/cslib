#include <gtest/gtest.h>

#include <cslib/algorithm/sort/insertion_sort.hpp>

#include <vector>

template <typename T>
using DefaultContainer = std::vector<T>;

TEST(insertion_sort, one_element)
{
	DefaultContainer<int> container { 0 };

	cslib::algorithm::insertion_sort(container.begin(), container.end());
	EXPECT_TRUE(container.back() == 0);
}


TEST(insertion_sort, ascending_order)
{
	DefaultContainer<int> container { 0, 5, 15, 5, 10, 10 };

	cslib::algorithm::insertion_sort(container.begin(), container.end());
	ASSERT_EQ(container.back(), 15);
}


TEST(insertion_sort, descending_order)
{
	DefaultContainer<int> container { 0, 5, 15, 5, 10, 10 };

	cslib::algorithm::insertion_sort(container.begin(), container.end(), std::greater<int>());
	ASSERT_EQ(container.back(), 0);
}
