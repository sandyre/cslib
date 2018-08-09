#include <gtest/gtest.h>

#include <cslib/algorithm/maximum_subarray.hpp>

#include <vector>

template <typename T>
using DefaultContainer = std::vector<T>;

TEST(maximum_subarray, empty_input)
{
	DefaultContainer<int> container;

	EXPECT_ANY_THROW(cslib::algorithm::maximum_subarray(container.begin(), container.end()));
}


TEST(maximum_subarray, simple_input)
{
	DefaultContainer<int> container { 0, 10, 5, -4, 3 };

	auto result = cslib::algorithm::maximum_subarray(container.begin(), container.end());
	ASSERT_EQ(result.first, 15);
	ASSERT_EQ(result.second, std::make_pair(container.begin(), container.begin() + 2));
}
