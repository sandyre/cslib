#include <gtest/gtest.h>

#include <cslib/data_structure/dynamic_array.hpp>

TEST(dynamic_array, empty_construction)
{
	cslib::data_structure::dynamic_array<int> container;

	ASSERT_EQ(container.size(), 0);
	ASSERT_EQ(container.capacity(), 4);
	EXPECT_TRUE(container.empty());
}


TEST(dynamic_array, nonempty_construction)
{
	cslib::data_structure::dynamic_array<int> container(5);

	ASSERT_EQ(container.size(), 5);
	ASSERT_EQ(container.capacity(), 5);
}


TEST(dynamic_array, push_back)
{
	cslib::data_structure::dynamic_array<int> container;

	container.push_back(5);

	ASSERT_EQ(container.size(), 1);
	ASSERT_EQ(container.capacity(), 4);
}


TEST(dynamic_array, pop_back)
{
	cslib::data_structure::dynamic_array<int> container;

	container.push_back(5);
	container.pop_back();

	ASSERT_EQ(container.size(), 0);
	ASSERT_EQ(container.capacity(), 4);
}


TEST(dynamic_array, access)
{
	cslib::data_structure::dynamic_array<int> container;

	container.push_back(5);
	container.push_back(10);

	ASSERT_EQ(container[0], 5);
	ASSERT_EQ(container[1], 10);

	ASSERT_EQ(container.front(), 5);
	ASSERT_EQ(container.back(), 10);
}


TEST(dynamic_array, comparison)
{
	cslib::data_structure::dynamic_array<int> containerA, containerB;

	containerA.push_back(5);
	containerA.push_back(15);
	containerA.push_back(20);

	containerB.push_back(7);
	containerB.push_back(30);

	ASSERT_NE(containerA, containerB);
}
