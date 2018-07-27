#include <gtest/gtest.h>

#include <cslib/data_structure/stack.hpp>

TEST(stack, empty_construction)
{
	cslib::data_structure::stack<int> container;

	ASSERT_EQ(container.size(), 0);
	EXPECT_TRUE(container.empty());
}


TEST(stack, push)
{
	cslib::data_structure::stack<int> container;

	container.push(5);

	ASSERT_EQ(container.size(), 1);
}


TEST(stack, pop)
{
	cslib::data_structure::stack<int> container;

	container.push(5);
	container.pop();

	ASSERT_EQ(container.size(), 0);
}


TEST(stack, access)
{
	cslib::data_structure::stack<int> container;

	container.push(5);
	container.push(10);

	ASSERT_EQ(container.top(), 10);
	container.pop();
	ASSERT_EQ(container.top(), 5);
}
