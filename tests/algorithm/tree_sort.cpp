#include <gtest/gtest.h>

#include <cslib/algorithm/sort/tree_sort.hpp>

#include <vector>

template <typename T>
using DefaultContainer = std::vector<T>;

TEST(tree_sort, one_element)
{
	DefaultContainer<int> container { 0 };

	cslib::algorithm::tree_sort(container.begin(), container.end());
	EXPECT_TRUE(container.back() == 0);
}


TEST(tree_sort, ascending_order)
{
	DefaultContainer<int> container { 0, 5, 15, 5, 10, 10 };

	cslib::algorithm::tree_sort(container.begin(), container.end());
	ASSERT_EQ(container, DefaultContainer<int>({ 0, 5, 5, 10, 10, 15}));
}
